/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_pow.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/17 15:14:53 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/21 11:29:45 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_pow(float nb, int pow)
{
	float	result;

	result = 1;
	while (pow--)
		result *= nb;
	return (result);
}
