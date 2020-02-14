/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cplx_sinh.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 10:26:51 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/23 10:28:21 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

t_cplx	cplx_sinh(t_cplx z)
{
	t_cplx r;

	r.rl = cos(z.im) * (exp(z.rl) - exp(-z.rl)) / 2;
	r.im = sin(z.im) * (exp(z.rl) + exp(-z.rl)) / 2;
	return (r);
}
