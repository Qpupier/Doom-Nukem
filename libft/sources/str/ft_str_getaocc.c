/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_getaocc.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 18:59:25 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 18:59:48 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*str_getaocc(char *str, char c)
{
	unsigned int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (str + i + 1);
	}
	return (NULL);
}
