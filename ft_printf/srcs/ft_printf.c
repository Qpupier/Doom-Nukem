/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 15:20:50 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 19:20:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void			init_parser_struct(t_parser *p)
{
	p->found = 0;
	p->pmodif = 0;
	p->palpha = 0;
	p->space = 0;
}

void			pf_init_structs(t_env *env)
{
	env->width = -1;
	env->precision = -1;
	env->base = 10;
	env->flags = 0;
}

static void		ft_start_parsing(t_env *env)
{
	int		i;
	char	*format;

	format = env->format;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1])
		{
			i = ft_parse(env, format, i);
			if (i < 0)
				i = 0;
		}
		else
		{
			if (format[i] != '%')
			{
				write(1, format + i, 1);
				env->nb++;
			}
		}
		i++;
	}
}

int				ft_printf(const char *format, ...)
{
	t_env	*env;
	int		nb;

	if (!(env = malloc(sizeof(t_env))))
		exit(1);
	env->format = (char *)format;
	env->nb = 0;
	pf_init_structs(env);
	va_start(env->arg, format);
	ft_start_parsing(env);
	va_end(env->arg);
	nb = env->nb;
	free(env);
	return (nb);
}
