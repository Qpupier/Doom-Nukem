/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atof.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 18:54:55 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 20:09:20 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

float			ft_atof(const char *str)
{
	float	res;
	char	*c;

	c = (char *)str;
	while (*c && *c != '.')
		c++;
	*c == '.' ? c++ : 0;
	res = (float)ft_atoi(c) / pow(10, ft_strlen(c));
	return ((float)ft_atoi(str) + ((*str == '-') ? -res : res));
}
