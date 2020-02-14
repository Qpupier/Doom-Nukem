/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   triangulation.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 16:17:12 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 21:20:42 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int				get_point(t_list_polygons *lst, int index, t_vec *result)
{
	t_list_points	*tmp;
	int				i;

	tmp = lst->points;
	i = 0;
	while (tmp)
	{
		if (i == index)
		{
			*result = tmp->point;
			return (1);
		}
		i++;
		tmp = tmp->next;
	}
	return (0);
}

void			copy_old_data(t_list_polygons *save, t_list_polygons *current)
{
	int				i;
	t_list_points	*tmp;

	save->points = NULL;
	save->vt = NULL;
	i = -1;
	while (++i < 4)
		save->tex[i] = current->tex[i];
	save->options = 0;
	save->texture = current->texture;
	save->vn = current->vn;
	save->options = current->options;
	save->color = current->color;
	save->ptr_tex = current->ptr_tex;
	save->kd = current->kd;
	save->ka = current->ka;
	save->texture2 = current->texture2;
	tmp = current->vt;
	while (tmp)
	{
		points_pushback(&save->vt, tmp->point);
		tmp = tmp->next;
	}
}

static t_vec	gen_new_normal(t_list_polygons *current,
	t_vec pt0, t_vec pt1, t_vec pt2)
{
	t_vec			n;
	float			sp;

	n = vec_cross_product(vec_sub(pt1, pt0), vec_sub(pt2, pt0));
	sp = vec_scale_product(n, current->vn);
	if (sp < 0)
		n = vec_mult_float(n, -1);
	return (n);
}

int				start_triangulate(t_list_polygons **lst,
	t_list_polygons *current)
{
	int				i;
	t_vec			pt0;
	t_vec			pt1;
	t_vec			pt2;
	t_list_polygons	new_data;

	i = 0;
	while (i < current->nb_points - 2)
	{
		copy_old_data(&new_data, current);
		if (!get_point(current, 0, &pt0) || !get_point(current, i + 1, &pt1) ||
											!get_point(current, i + 2, &pt2))
		{
			ft_putendl("Error triangulating polygon. Skipping.");
			return (0);
		}
		points_pushback(&new_data.points, pt0);
		points_pushback(&new_data.points, pt1);
		points_pushback(&new_data.points, pt2);
		new_data.vn = gen_new_normal(current, pt0, pt1, pt2);
		polygon_push(lst, new_data);
		i++;
	}
	return (1);
}

void			triangulate_object(t_list_polygons **lst)
{
	t_list_polygons	*tpoly;

	tpoly = *lst;
	while (tpoly)
	{
		if (tpoly->nb_points > 3)
		{
			start_triangulate(lst, tpoly);
			tpoly->options |= SKIP_CONVERSION;
		}
		tpoly = tpoly->next;
	}
}
