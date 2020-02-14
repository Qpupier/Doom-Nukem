/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_isnumber.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 18:55:44 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 18:56:14 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		str_isnumber(char *str)
{
	while (*str)
	{
		if (*str == '-' || *str == '.')
			str++;
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int		str_isnumbern(char *str, int n)
{
	int		i;

	i = -1;
	while (*str && (++i < n))
	{
		if (*str == '-')
			str++;
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
