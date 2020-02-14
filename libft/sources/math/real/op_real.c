/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op_real.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 15:44:16 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 13:36:08 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_real	op_real(t_real a, char op, t_real b)
{
	if (op == '+')
		return ((t_real){a.x + b.x, a.y + b.y});
	if (op == '-')
		return ((t_real){a.x - b.x, a.y - b.y});
	if (op == '>')
		return (op_real(b, '-', a));
	return ((t_real){0, 0});
}
