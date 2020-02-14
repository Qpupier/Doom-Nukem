/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   type.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 15:01:39 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 10:48:15 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_sendhandler(t_env *e, char f)
{
	if (e->type == 'U')
		e->flags |= L_L;
	if (f == 's')
		handle_s(e);
	if (f == 'c')
		handle_c(e);
	if (f == 'p')
		handle_p(e);
	if (f == 'd' || f == 'i' || f == 'D')
		handle_d(e);
	if (f == 'u' || f == 'U')
		handle_xou(e);
	if (f == 'f' || f == 'F')
		handle_floats(e);
	if (f == 'x' || f == 'X' || f == 'o' || f == 'O')
	{
		e->base = (f == 'x' || f == 'X') ? 16 : 8;
		handle_xou(e);
	}
}

static void	pf_parse_options(t_env *e, char *s, int i, int *pospre)
{
	if (s[i] == '-')
		e->flags |= O_MINUS;
	if (s[i] == '+')
		e->flags |= O_PLUS;
	if (s[i] == ' ' && !(e->flags & O_PLUS))
		e->flags |= O_SPACE;
	if (s[i] == '#')
		e->flags |= O_HASH;
	if (s[i] == '.')
		*pospre = i;
	if (s[i - 1])
		if (s[i] == '0' && (!pf_isdigit(s[i - 1]) && s[i - 1] != '.'))
			e->flags |= O_ZERO;
}

static void	pf_parse_modifier(t_env *e, char *s, int start, int end)
{
	while (end-- != start)
	{
		if (s[end] == 'j')
			e->flags |= L_J;
		else if (s[end] == 'z')
			e->flags |= L_Z;
		else if (s[end] == 'L')
			e->flags |= L_LMAJ;
		else if (s[end] == 'l' && s[end - 1] && s[end - 1] == 'l')
			e->flags |= L_LL;
		else if (s[end] == 'l')
			e->flags |= L_L;
		else if (s[end] == 'h' && s[end - 1] && s[end - 1] == 'h')
			e->flags |= L_HH;
		else if (s[end] == 'h')
			e->flags |= L_H;
	}
}

int			pf_parse_type(t_env *e, char *str, int start, int end)
{
	int		i;
	int		pospre;

	if (str[end - 1] && str[end - 1] != '%' && (!ismodifier(str[end - 1])
				&& !isoption(str[end - 1]) && !pf_isdigit(str[end - 1])))
		return (-1);
	pospre = -1;
	i = start + 1;
	pf_init_structs(e);
	while (i < end)
	{
		pf_parse_options(e, str, i, &pospre);
		i++;
	}
	pf_parse_modifier(e, str, start, i);
	pf_extract_precision(e, start, i, str);
	pf_extract_width(e, start + 1, (pospre >= 0 ? pospre : i), str);
	e->type = str[i];
	if (e->precision != -1 && e->flags & O_ZERO && e->type != 'c'
		&& e->type != 's')
		e->flags -= O_ZERO;
	pf_sendhandler(e, str[i]);
	return (i);
}
