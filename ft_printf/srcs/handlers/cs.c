/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cs.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/22 20:49:15 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 10:31:29 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static int		calcs_field(t_env *e, char *str)
{
	int		count;

	count = pf_strlen(str);
	if (e->precision != -1 && e->precision < count)
		count = e->precision;
	e->calcs.count = count;
	return (count);
}

static void		strcutn(t_env *e, char *s, int n)
{
	int		i;
	char	*nstr;

	if (!(nstr = malloc(sizeof(char) * (n + 1))))
		print_error(e, "malloc error (strcutn)");
	i = -1;
	while (++i < n)
		nstr[i] = s[i];
	nstr[i] = '\0';
	e->nb += write(1, nstr, n);
	free(nstr);
}

void			handle_s(t_env *e)
{
	char	*str;
	int		i;

	str = (char *)va_arg(e->arg, char *);
	if (!str)
		str = "(null)\0";
	i = calcs_field(e, str);
	if (e->width > e->calcs.count && !(e->flags & O_MINUS) &&
		(!(e->flags & O_ZERO) || (e->flags & O_ZERO && e->precision >= 1)))
		printnchar(e, ' ', e->width - e->calcs.count);
	if (e->width > e->calcs.count && e->flags & O_ZERO && e->precision <= 0
			&& !(e->flags & O_MINUS))
		printnchar(e, '0', e->width - e->calcs.count);
	strcutn(e, str, i);
	if ((e->flags & O_MINUS))
		printnchar(e, ' ', e->width - e->calcs.count);
}

void			handle_c(t_env *e)
{
	char	c;

	c = (char)va_arg(e->arg, int);
	if (!(e->flags & O_MINUS) && e->width > 1)
		printnchar(e, ((e->flags & O_ZERO) ? '0' : ' '), e->width - 1);
	e->nb += write(1, &c, 1);
	if ((e->flags & O_MINUS) && !(e->flags & O_ZERO) && e->width >= 1)
		printnchar(e, ' ', e->width - 1);
}
