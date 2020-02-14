/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   floats_tools.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 11:51:59 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 10:32:36 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static int		pf_ilen(intmax_t n)
{
	int		count;

	n = n < 0 ? -n : n;
	count = 0;
	while (n > 0 && ++count && (n /= 10))
		;
	return (count);
}

static double	pt_power(double n, int p)
{
	if (p == 0)
		return (1);
	if (p == 1)
		return (n);
	return (n * pt_power(n, p - 1));
}

static void		pf_ftoa_putint(intmax_t n, char *s, int count)
{
	if (n == 0)
		s[count] = '0';
	while (n)
	{
		s[--count] = n % 10 + '0';
		n /= 10;
	}
}

static void		pf_ftoa_putdec(long double d, int *i, int p, char *s)
{
	intmax_t n;

	n = d;
	s[*i] = (p) ? '.' : '\0';
	while (p--)
	{
		d = (d - n) * 10.0;
		n = d;
		s[++*i] = n + '0';
	}
}

char			*pf_ft_ftoa(t_env *e, long double d, int p)
{
	intmax_t	n;
	char		*s;
	int			i;
	short int	isneg;

	p = (p < 0) ? 6 : p;
	isneg = (d < 0 || d == -0.0) ? 1 : 0;
	d = (isneg) ? -d : d;
	d += (p >= 0) ? 5.000001 / pt_power(10, p + 1) : 0;
	n = d;
	i = pf_ilen(n) + isneg;
	if (!(s = malloc(sizeof(char) * (i + p + (p > 0 ? 1 : 0) + 1))))
		print_error(e, "malloc error (pf_ft_ftoa)");
	if (d && !i)
		s[i++] = '0';
	else
	{
		s[0] = (isneg) ? '-' : '\0';
		pf_ftoa_putint(n, s, i);
	}
	i += (n == 0 ? 1 : 0);
	pf_ftoa_putdec(d, &i, p, s);
	s[i + 1] = '\0';
	return (s);
}
