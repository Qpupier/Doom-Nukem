/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   floats.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 11:52:41 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 10:32:33 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void	calc_field(t_env *e, char *s)
{
	e->calcs.count = pf_strlen(s);
	e->calcs.pdiff = 0;
	e->calcs.wdiff = 0;
	if (((e->flags & O_SPACE) || (e->flags & O_PLUS)) && s[0] != '-')
		e->calcs.count += 1;
	if (e->width > e->calcs.count)
		e->calcs.wdiff = e->width - e->calcs.count;
}

void		handle_floats(t_env *e)
{
	char		*ftoa;
	long double	n;

	if (e->flags & L_LMAJ)
		n = (long double)va_arg(e->arg, long double);
	else
		n = (double)va_arg(e->arg, double);
	ftoa = pf_ft_ftoa(e, n, e->precision);
	calc_field(e, ftoa);
	if (!(e->flags & O_MINUS))
		printnchar(e, ((e->flags & O_ZERO) ? '0' : ' '), e->calcs.wdiff);
	if ((e->flags & O_SPACE) && n > 0)
		write(1, " ", 1);
	if ((e->flags & O_PLUS) && n > 0)
		write(1, "+", 1);
	e->nb += write(1, ftoa, pf_strlen(ftoa));
	if ((e->flags & O_MINUS))
		printnchar(e, ' ', e->calcs.wdiff);
	free(ftoa);
}
