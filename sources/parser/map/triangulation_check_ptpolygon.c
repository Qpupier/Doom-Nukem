/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   triangulation_check_ptpolygon.c                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 11:02:16 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

t_vec		triangle_getcenter(t_pt_tri_tmp *a, t_pt_tri_tmp *b,
	t_pt_tri_tmp *c)
{
	t_vec	v;

	v = (t_vec)
	{
		.x = (a->point.x + b->point.x + c->point.x) / 3,
		.y = (a->point.y + b->point.y + c->point.y) / 3,
		.z = (a->point.z + b->point.z + c->point.z) / 3
	};
	return (v);
}

static void	inpoly_check(t_list_polygons *w, t_half_line half_line, t_vec new,
	int *nb)
{
	t_list_points	*lst;
	t_list_points	*next;
	short int		tmp;
	t_vec			tmp_vec;

	lst = w->points;
	while (lst)
	{
		if (lst->next)
			next = lst->next;
		else
			next = w->points;
		tmp = line_half_inter_seg(half_line, (t_seg){lst->point, next->point},
																	&tmp_vec);
		tmp_vec = next->next ? next->next->point : w->points->point;
		if (tmp && (tmp < 4 ||
				vec_scale_product(vec_sub(lst->point, next->point), new) * \
				vec_scale_product(vec_sub(next->point, tmp_vec), new) >= 0))
			(*nb)++;
		lst = lst->next;
	}
}

int			t_in_polygon(t_vec pt, t_list_polygons *w, t_vec vec)
{
	t_half_line		half_line;
	int				nb;
	t_vec			new;
	t_vec			u;
	t_vec			v;

	nb = 0;
	half_line = (t_half_line){pt, vec};
	u = vec_sub(w->points->next->point, w->points->point);
	v = vec_sub(w->points->next->next->point, w->points->point);
	new = vec_cross_product(vec, vec_cross_product(u, v));
	inpoly_check(w, half_line, new, &nb);
	return (nb & 1);
}
