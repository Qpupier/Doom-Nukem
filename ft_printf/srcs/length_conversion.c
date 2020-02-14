/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   length_conversion.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 19:21:56 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 20:07:38 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	handle_length_unsigned(t_env *e)
{
	if ((e->flags & L_J))
		return (uintmax_t)va_arg(e->arg, uintmax_t);
	else if ((e->flags & L_Z))
		return (uintmax_t)va_arg(e->arg, ssize_t);
	else if ((e->flags & L_LL) || e->type == 'O')
		return (uintmax_t)va_arg(e->arg, unsigned long long);
	else if ((e->flags & L_L))
		return (uintmax_t)va_arg(e->arg, unsigned long);
	else if ((e->flags & L_HH))
		return (unsigned char)va_arg(e->arg, unsigned int);
	else if ((e->flags & L_H))
		return (unsigned short)va_arg(e->arg, unsigned int);
	else
		return (uintmax_t)va_arg(e->arg, unsigned int);
}

intmax_t	handle_length(t_env *e)
{
	if ((e->flags & L_J))
		return (intmax_t)va_arg(e->arg, intmax_t);
	else if ((e->flags & L_Z))
		return (intmax_t)va_arg(e->arg, size_t);
	else if ((e->flags & L_LL) || e->type == 'D')
		return (intmax_t)va_arg(e->arg, long long);
	else if ((e->flags & L_L))
		return (intmax_t)va_arg(e->arg, long);
	else if ((e->flags & L_HH))
		return (char)va_arg(e->arg, int);
	else if ((e->flags & L_H))
		return (short)va_arg(e->arg, int);
	else
		return (intmax_t)va_arg(e->arg, int);
}
