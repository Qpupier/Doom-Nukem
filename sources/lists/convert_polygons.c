/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_polygons.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 14:04:57 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:52:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		copy_points(t_polygon *curr, t_list_polygons *lst_poly)
{
	convert_t_list_points(lst_poly->points, curr->points);
	free_tlist_point(&lst_poly->points);
	ft_memset(curr->tmp_points, 0, sizeof(t_vec) * curr->nb_points);
	if (curr->options & IS_BLENDER || curr->options & HAS_BEEN_TRIANGULATED)
	{
		convert_vt_tmp(lst_poly->vt, curr->vt);
		free_tlist_point(&lst_poly->vt);
		tvec_array_cpy(lst_poly->obj_tex, curr->obj_tex, 3);
	}
	else
		tvec_array_cpy(lst_poly->tex, curr->tex, 4);
}

static void		handle_convert(t_list_polygons *lst, t_polygon *tab)
{
	if (lst->texture2 && lst->options & IS_BLENDER)
		tab->texture = lst->texture2;
	else
		tab->texture = &lst->texture;
	tab->vn = lst->vn;
	tab->options = lst->options;
	tab->ka = lst->ka;
	tab->kd = lst->kd;
	tab->nb_points = lst->nb_points;
	tab->color = lst->color;
	tab->tex_u = lst->tex_u;
	tab->tex_v = lst->tex_v;
	tab->axis.x = (t_vec){1, 0, 0};
	tab->axis.y = (t_vec){0, 1, 0};
	tab->axis.z = (t_vec){0, 0, 1};
	tab->sprite_angle = 0;
	copy_points(tab, lst);
}

void			copy_polygons(t_list_polygons *lst_poly,
	unsigned int nb_poly, t_polygon *poly)
{
	t_list_polygons	*tmp;
	unsigned int	poly_index;
	t_polygon		*curr;

	poly_index = 0;
	tmp = lst_poly;
	while (lst_poly && poly_index <= nb_poly)
	{
		curr = &poly[poly_index];
		if (!(lst_poly->options & SKIP_CONVERSION))
		{
			handle_convert(lst_poly, curr);
			poly_index++;
		}
		else
		{
			free_tlist_point(&lst_poly->points);
		}
		lst_poly = lst_poly->next;
	}
}
