/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   real_turn.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 15:52:27 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 12:06:32 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_real	real_turn(t_real point, float degree)
{
	t_real	new;

	degree = ft_deg_to_rad(degree);
	new.x = cos(degree) * point.x - sin(degree) * point.y;
	new.y = sin(degree) * point.x + cos(degree) * point.y;
	return (new);
}
