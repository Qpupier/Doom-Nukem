/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   inter_2d_line_seg.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 15:50:51 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 15:51:32 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	inter_2d_line_seg(t_2d_line l, t_2d_seg s, t_real *result)
{
	float	d_s;
	float	d_s1;
	float	d_s2;

	if (!inter_2d_line_line(l, create_2d_line_points(s.a, s.b), result))
		return (0);
	d_s = real_norm(op_real(s.b, '-', s.a));
	d_s1 = real_norm(op_real(*result, '-', s.b));
	d_s2 = real_norm(op_real(*result, '-', s.a));
	if (d_s1 > d_s || d_s2 > d_s)
		return (0);
	if (d_s1 == d_s)
		return (2);
	if (d_s2 == d_s)
		return (3);
	return (1);
}
