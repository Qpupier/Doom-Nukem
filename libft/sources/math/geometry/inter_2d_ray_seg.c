/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   inter_2d_ray_seg.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 15:47:37 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 15:48:14 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	inter_2d_ray_seg(t_2d_ray r, t_2d_seg s, t_inter_2d_ray_seg *sol)
{
	float	d_r;
	int		d_s;

	if (!inter_2d_line_line(create_2d_line_point_vec(r.p, r.d), 	\
			create_2d_line_points(s.a, s.b), &sol->result))
		return (0);
	d_r = real_scale_product(op_real(sol->result, '-', r.p), r.d);
	d_s = point_2d_line_in_seg(sol->result, s);
	sol->r = !d_r;
	sol->s1 = d_s == 2;
	sol->s2 = d_s == 3;
	return (d_r >= 0 && d_s);
}
