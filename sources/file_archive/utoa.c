/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utoa.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/07 11:16:12 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 11:18:41 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

static char	*handle_zero(void)
{
	char *str;

	if (!(str = malloc(sizeof(char) * 2)))
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char		*utoa_base(uintmax_t nb, short int base)
{
	char		*str;
	int			count;
	uintmax_t	n;

	if (base <= 0)
		return (NULL);
	if (nb == 0)
		return (handle_zero());
	n = nb;
	count = 0;
	while (n && ++count)
		n /= base;
	if (!(str = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	str[count] = '\0';
	while (nb)
	{
		n = nb % base;
		str[--count] = (n < 10 ? n + 48 : n + 87);
		nb /= base;
	}
	return (str);
}
