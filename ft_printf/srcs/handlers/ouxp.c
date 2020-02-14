/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ouxp.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 17:04:02 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/19 20:17:55 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void			print_op(t_env *e)
{
	if ((e->flags & O_HASH) &&
		(e->type == 'o' || e->type == 'x' || e->type == 'X'))
	{
		e->nb += write(1, "0", 1);
		if (e->type != 'o')
			e->nb += write(1, &e->type, 1);
	}
}

static void			calc_field_oxp(t_env *e, uintmax_t n)
{
	int			count;

	count = 0;
	while (n && ++count)
		n /= e->base;
	e->calcs.count = count;
	e->calcs.wdiff = 0;
	e->calcs.pdiff = 0;
	if (e->type == 'p' && !count)
		e->calcs.count += 1;
	if ((e->flags & O_HASH) && (e->type == 'o' || e->type == 'O') && count)
		e->calcs.count += 1;
	if (e->precision > e->calcs.count)
		e->calcs.pdiff = e->precision - e->calcs.count;
	if ((e->flags & O_HASH) && count && e->type != 'o' && e->type != 'O')
		e->calcs.count += 2;
	if (e->type == 'p')
		e->calcs.count += 2;
	if (e->width > e->calcs.count + e->calcs.pdiff)
		e->calcs.wdiff = e->width - (e->calcs.count + e->calcs.pdiff);
}

static short int	handle_xou_zero(t_env *e, uintmax_t nb)
{
	if (nb > 0)
		return (0);
	field_right(e, 0);
	if (e->precision == 0)
	{
		if ((e->type == 'o' || e->type == 'O') && (e->flags & O_HASH))
			e->nb += write(1, "0", 1);
	}
	else if (e->precision == -1)
		e->nb += write(1, "0", 1);
	else if (e->precision > 0)
		printnchar(e, '0', e->calcs.pdiff);
	field_left(e);
	return (1);
}

void				handle_xou(t_env *e)
{
	uintmax_t	nb;

	nb = handle_length_unsigned(e);
	calc_field_oxp(e, nb);
	if (handle_xou_zero(e, nb))
		return ;
	if ((e->flags & O_ZERO) && (e->flags & O_HASH) && e->type != 'o' &&
		e->type != 'O' && e->precision == -1)
		print_op(e);
	field_right(e, 1);
	if ((e->flags & O_HASH) && e->type != 'o' && e->type != 'O'
		&& (!((e->flags & O_ZERO)) || e->precision >= 0))
		print_op(e);
	if ((e->flags & O_HASH) && (e->type == 'o' || e->type == 'O'))
		e->nb += write(1, "0", 1);
	printnchar(e, '0', e->calcs.pdiff);
	convert_base(e, nb, e->base, 0);
	field_left(e);
}

void				handle_p(t_env *e)
{
	void	*ptr;

	ptr = (void *)va_arg(e->arg, void *);
	e->base = 16;
	calc_field_oxp(e, (uintmax_t)ptr);
	field_right(e, 1);
	e->nb += write(1, "0x", 2);
	printnchar(e, '0', e->calcs.pdiff);
	if (!convert_base(e, (uintmax_t)ptr, 16, 0) && e->precision != 0)
		e->nb += write(1, "0", 1);
	field_left(e);
}
