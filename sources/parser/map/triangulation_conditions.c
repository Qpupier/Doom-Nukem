/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   triangulation_conditions.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 11:23:48 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:52:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

t_pt_tri_tmp	*find_next(t_pt_tri_tmp *copy, t_pt_tri_tmp *points)
{
	t_pt_tri_tmp	*tmp;

	tmp = points;
	if (!points)
		return (NULL);
	tmp = tmp->next;
	while (tmp && tmp->deleted)
		tmp = tmp->next;
	if (!tmp)
	{
		tmp = copy;
		while (tmp && tmp->deleted)
			tmp = tmp->next;
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

int				points_left(t_pt_tri_tmp *list)
{
	t_pt_tri_tmp	*tmp;
	int				nb;

	nb = 0;
	tmp = list;
	while (tmp)
	{
		if (!tmp->deleted)
			nb++;
		tmp = tmp->next;
	}
	return (nb);
}

int				t_check_in_tri(t_list_polygons *poly, t_vec a, t_vec b, t_vec c)
{
	t_list_points	*pt;
	int				ret;
	t_vec			p;

	ret = 0;
	pt = poly->points;
	while (pt)
	{
		p = pt->point;
		if (!vec_equal(p, a) && !vec_equal(p, b) && !vec_equal(p, c))
			ret = in_triangle_tmp(p, a, b, c);
		pt = pt->next;
	}
	return (ret);
}

int				t_intersects(t_pt_tri_tmp *copy, t_vec a, t_vec b, t_vec c)
{
	return (intersect_check(copy, (t_seg){a, b})
		|| intersect_check(copy, (t_seg){b, c})
		|| intersect_check(copy, (t_seg){c, a}));
}
