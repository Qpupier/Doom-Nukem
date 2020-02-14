/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cplx_turn.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 10:26:51 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/23 10:37:38 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

t_cplx	cplx_turn(t_cplx a, t_cplx o, float angle)
{
	return (cplx_add(cplx_mult(cplx_remove(a, o), 	\
			cplx_make(cos(angle), sin(angle))), o));
}
