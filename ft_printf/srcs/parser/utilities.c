/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utilities.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 15:06:38 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 10:48:15 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_isalpha(int c)
{
	if ((c < 97 || c > 122) && (c < 65 || c > 90))
		return (0);
	return (1);
}

int		pf_isdigit(int c)
{
	if ((c < 48 || c > 57))
		return (0);
	return (1);
}

int		isoption(char c)
{
	int i;

	i = -1;
	while (++i < 6)
		if (c == OPTIONS[i])
			return (1);
	return (0);
}

int		endofparse(char c)
{
	int i;

	i = -1;
	while (++i < 14)
		if (c == FLAGS[i])
			return (1);
	return (0);
}

int		ismodifier(char c)
{
	int i;

	i = -1;
	while (++i < 5)
		if (c == MODIFIER[i])
			return (1);
	return (0);
}
