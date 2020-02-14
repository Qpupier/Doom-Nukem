/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   triangulation_recursive.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 12:26:26 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static int		get_next(t_pt_tri_tmp *copy, t_pt_tri_tmp *data,
	t_pt_tri_tmp **res)
{
	return ((*res = find_next(copy, data)) ? 1 : 0);
}

static void		start_recursion(t_list_polygons *poly, t_pt_tri_tmp *copy,
	t_list_tri **tri, int depth)
{
	int				remaining;

	remaining = points_left(copy);
	if (depth >= 10)
	{
		ft_error("An error occured during map triangulation.\n");
		return ;
	}
	if (remaining >= 3)
		depth++;
	if (remaining >= 3)
		start_triangulation(poly, copy, tri, depth);
}

void			start_triangulation(t_list_polygons *poly, t_pt_tri_tmp *copy,
	t_list_tri **tri, int depth)
{
	t_pt_tri_tmp	*tmp;
	t_pt_tri_tmp	*next;
	t_pt_tri_tmp	*nnext;

	tmp = copy;
	while (tmp)
	{
		while (get_next(copy, tmp, &next) && get_next(copy, next, &nnext)
			&& t_in_polygon(triangle_getcenter(tmp, next, nnext), poly, 	\
							vec_sub(poly->tex[1], poly->tex[0])) 		\
			&& !t_intersects(copy, tmp->point, next->point, nnext->point) 	\
			&& !t_check_in_tri(poly, tmp->point, next->point, nnext->point)
			&& points_left(copy) >= 3)
		{
			lst_tri_add(tri, tmp->point, next->point, nnext->point);
			next->deleted = 1;
		}
		tmp = tmp->next;
		while (tmp && tmp->deleted)
			tmp = tmp->next;
	}
	start_recursion(poly, copy, tri, depth);
}
