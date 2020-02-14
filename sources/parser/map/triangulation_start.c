/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   triangulation_start.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 12:26:18 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 13:13:57 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		copy_old_data(t_list_polygons *data, t_list_polygons *o)
{
	data->texture = o->texture;
	data->color = o->color;
	data->options = o->options;
	data->options |= HAS_TEXTURE;
	data->options |= HAS_BEEN_TRIANGULATED;
}

int				gen_new_polygon(t_list_polygons **head, t_list_polygons *o,
	t_list_tri *n)
{
	t_real			res;
	t_list_polygons	data;

	data.points = NULL;
	data.vt = NULL;
	if (points_pushback(&data.points, n->tri[0])
		|| points_pushback(&data.points, n->tri[1])
		|| points_pushback(&data.points, n->tri[2]))
		return (1);
	res = triangulation_get_tex(n->tri[0], o->tex[0], o->tex[1], o->tex[3]);
	if (points_pushback(&data.vt, (t_vec){res.x, res.y, 1}))
		return (1);
	res = triangulation_get_tex(n->tri[1], o->tex[0], o->tex[1], o->tex[3]);
	if (points_pushback(&data.vt, (t_vec){res.x, res.y, 1}))
		return (1);
	res = triangulation_get_tex(n->tri[2], o->tex[0], o->tex[1], o->tex[3]);
	if (points_pushback(&data.vt, (t_vec){res.x, res.y, 1}))
		return (1);
	copy_old_data(&data, o);
	return (!push_triangulated_polygon(head, data));
}

static int		init_copy_points(t_list_polygons *poly, t_pt_tri_tmp **copy)
{
	t_list_points	*tmp;

	tmp = poly->points;
	while (tmp)
	{
		if (!lst_tri_addpoints(copy, tmp->point))
		{
			free_lst_tri_points(copy);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void			triangulate_polygon(t_list_polygons **head,
	t_list_polygons *poly)
{
	t_pt_tri_tmp	*copy;
	t_list_tri		*tri;
	t_list_tri		*tmp_list;
	int				ret;

	ret = 0;
	tri = NULL;
	copy = NULL;
	if (!init_copy_points(poly, &copy))
		return ;
	start_triangulation(poly, copy, &tri, 0);
	free_lst_tri_points(&copy);
	tmp_list = tri;
	while (tmp_list)
	{
		ret += gen_new_polygon(head, poly, tmp_list);
		tmp_list = tmp_list->next;
	}
	free_lst_tri(&tri);
	if (ret)
		return ;
	poly->options |= SKIP_CONVERSION;
}
