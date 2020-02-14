/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cplx_average.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 10:26:51 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/23 10:27:30 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

t_cplx	cplx_average(t_cplx a, t_cplx z, float b)
{
	return (cplx_make(a.rl + b * (z.rl - a.rl), a.im + b * (z.im - a.im)));
}
