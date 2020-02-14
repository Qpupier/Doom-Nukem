/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   real_oriented_angle.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/05 23:28:10 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 23:28:22 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

float	real_oriented_angle(t_real u, t_real v)
{
	float	tmp;

	tmp = real_scale_product(u, v);
	if (tmp < -1)
		tmp = -1;
	else if (tmp > 1)
		tmp = 1;
	return (real_scale_product(real_turn(u, 90), v) < 0 	\
			? -acos(tmp) : acos(tmp));
}
