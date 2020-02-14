/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   digitbase_tools.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/24 11:33:52 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/19 20:07:00 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		convert_base(t_env *e, uintmax_t nb, short int base, int i)
{
	char	c;
	int		n;

	c = '\0';
	if (nb)
	{
		i = convert_base(e, nb / base, base, i + 1);
		n = nb % base;
		c = (n < 10 ? n + 48 : n + 87);
		if ((c >= 'a' && c <= 'z') && e->type == 'X')
			c -= 32;
		e->nb += write(1, &c, 1);
	}
	return (i);
}

void	field_right(t_env *e, short int nb)
{
	if (nb == 0 && e->calcs.wdiff >= 1 && e->precision < 1)
		e->calcs.wdiff -= 1;
	if (nb == 0 && e->calcs.wdiff >= 1 && e->precision == 0)
		e->calcs.wdiff += 1;
	if (!(e->flags & O_MINUS))
		printnchar(e, (e->precision == -1 && (e->flags & O_ZERO) ? '0' : ' '),
					e->calcs.wdiff);
}

void	field_left(t_env *e)
{
	if ((e->flags & O_MINUS))
		printnchar(e, ' ', e->calcs.wdiff);
}
