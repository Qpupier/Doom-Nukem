/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   triangulation_check_intersection.c               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 11:19:12 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int			seg_inter_seg(t_seg s1, t_seg s2, t_vec *result)
{
	float	distance;

	if (!line_inter_line(line_create_points(s1.a, s1.b),
			line_create_points(s2.a, s2.b), result) 				\
			|| vec_norm(vec_sub(*result, s1.a)) 					\
			> (distance = vec_norm(vec_sub(s1.b, s1.a))) 		\
			|| vec_norm(vec_sub(*result, s1.b)) > distance 		\
			|| vec_norm(vec_sub(*result, s2.a)) 					\
			> (distance = vec_norm(vec_sub(s2.b, s2.a))) 		\
			|| vec_norm(vec_sub(*result, s2.b)) > distance)
		return (0);
	if (vec_equal_precision(*result, s1.a, .001))
		return (2);
	else if (vec_equal_precision(*result, s1.b, .001))
		return (3);
	else if (vec_equal_precision(*result, s2.a, .001))
		return (4);
	else if (vec_equal_precision(*result, s2.b, .001))
		return (5);
	return (1);
}

int			intersect_check(t_pt_tri_tmp *copy, t_seg a)
{
	t_vec			result;
	t_pt_tri_tmp	*tmp;
	t_vec			next;

	tmp = copy;
	while (tmp)
	{
		next = tmp->next ? tmp->next->point : copy->point;
		if (seg_inter_seg(a, (t_seg){tmp->point, next}, &result) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
