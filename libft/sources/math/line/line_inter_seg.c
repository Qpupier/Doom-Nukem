/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_inter_seg.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 23:19:17 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	line_inter_seg(t_line l, t_seg s, t_vec *result)
{
	float	distance;

	if (!line_inter_line(l, line_create_points(s.a, s.b), result) 	\
			|| vec_norm(vec_sub(*result, s.a)) 					\
			> (distance = vec_norm(vec_sub(s.b, s.a))) 			\
			|| vec_norm(vec_sub(*result, s.b)) > distance)
		return (0);
	return (vec_equal(*result, s.a) || vec_equal(*result, s.b) ? 2 : 1);
}
