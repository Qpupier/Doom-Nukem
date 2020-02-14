/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cplx_mult.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 10:26:51 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/23 10:28:10 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

t_cplx	cplx_mult(t_cplx a, t_cplx b)
{
	t_cplx r;

	r.rl = a.rl * b.rl - a.im * b.im;
	r.im = a.rl * b.im + a.im * b.rl;
	return (r);
}
