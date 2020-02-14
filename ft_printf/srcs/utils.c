/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 13:07:37 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 10:31:29 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		pf_strlen(const char *c)
{
	char	*p;

	p = (char *)c;
	if (!c)
		return (0);
	while (*p)
		++p;
	return (p - c);
}

void		printnchar(t_env *e, char c, int n)
{
	int		i;

	if (n <= 0 || !c)
		return ;
	i = -1;
	while (++i < n)
		e->nb += write(1, &c, 1);
}

void		print_error(t_env *e, char *s)
{
	int				slen;
	int				i;

	i = -1;
	slen = pf_strlen(s);
	write(1, "\x1b[1;37m", 7);
	write(1, "\x1b[48;5;88m", 10);
	write(1, "\n ft_printf: ", 13);
	write(1, s, slen);
	write(1, " \033[0;m", 5);
	free(e);
	exit(1);
}
