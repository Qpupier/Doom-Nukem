/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   diu.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 19:26:37 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 15:49:27 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void		show_op(t_env *e, intmax_t fint)
{
	if ((e->flags & O_PLUS) && fint >= 0)
		e->nb += write(1, "+", 1);
	if ((e->flags & O_SPACE) && fint >= 0 && !(e->flags & O_PLUS))
		e->nb += write(1, " ", 1);
	if (fint < 0)
		e->nb += write(1, "-", 1);
}

static void		calc_field(t_env *e, intmax_t fint)
{
	int			count;
	intmax_t	tmp;

	tmp = fint;
	count = 0;
	tmp = (tmp < 0) ? -tmp : tmp;
	while (tmp && ++count)
		tmp /= 10;
	count = (fint == 0) ? 1 : count;
	e->calcs.count = count;
	if (e->precision == 0 && fint == 0)
		e->calcs.count = 0;
	e->calcs.wdiff = 0;
	e->calcs.pdiff = 0;
	if (e->precision > e->calcs.count)
		e->calcs.pdiff = e->precision - e->calcs.count;
	if (((e->flags & O_PLUS) && fint >= 0) || ((e->flags & O_SPACE)
		&& fint >= 0 && !(e->flags & O_PLUS)) || fint < 0)
		e->calcs.count += 1;
	if (e->width > e->calcs.count + e->calcs.pdiff)
		e->calcs.wdiff = e->width - (e->calcs.count + e->calcs.pdiff);
	e->calcs.count += e->calcs.pdiff + e->calcs.wdiff;
}

void			handle_d(t_env *e)
{
	intmax_t		fint;

	fint = handle_length(e);
	calc_field(e, fint);
	if ((e->flags & O_ZERO))
		show_op(e, fint);
	field_right(e, 1);
	if (!(e->flags & O_ZERO))
		show_op(e, fint);
	printnchar(e, '0', e->calcs.pdiff);
	if (!(fint == 0 && e->precision == 0))
	{
		if (fint < 0)
			convert_base(e, -fint, 10, 0);
		else
		{
			if (!(convert_base(e, fint, 10, 0)) && fint == 0)
				e->nb += write(1, "0", 1);
		}
	}
	field_left(e);
}
