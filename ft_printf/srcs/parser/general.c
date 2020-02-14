/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   general.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 15:47:21 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 10:48:15 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_parse_percent(t_env *e, char *str, int start, int end)
{
	int		i;
	int		pospre;

	pf_init_structs(e);
	i = start + 1;
	pospre = -1;
	while (i < end)
	{
		if (str[i - 1])
			if (str[i] == '0' && (!pf_isdigit(str[i - 1]) && str[i - 1] != '.'))
				e->flags |= O_ZERO;
		if (str[i] == '-')
			e->flags |= O_MINUS;
		if (str[i] == '.')
			pospre = i;
		i++;
	}
	pf_extract_width(e, start, (pospre >= 0 ? pospre : i), str);
	if (!(e->flags & O_MINUS))
		printnchar(e, e->flags & O_ZERO ? '0' : ' ', e->width - 1);
	e->nb += write(1, "%", 1);
	if ((e->flags & O_MINUS))
		printnchar(e, ' ', e->width - 1);
	return (start);
}

static int		ft_checks(char *s, int *i, t_parser *p)
{
	if (!ft_isalpha(s[*i]) && s[*i] != '%')
		i++;
	if (ft_isalpha(s[*i]) && !ismodifier(s[*i] && !endofparse(s[*i])))
		p->palpha = *i;
	if (s[*i] == ' ')
		p->space = *i;
	if (ismodifier(s[*i]))
	{
		p->pmodif = *i;
		i++;
	}
	return (1);
}

static int		ft_parse_return(t_parser p, char *s, int start)
{
	if (p.found == 0 && !percent_nextocc(s, start)
		&& p.palpha == 0 && p.pmodif == 0 && p.space == 0)
		return (p.space + 1);
	else if (p.found == 0 && p.pmodif >= 2)
		return (p.pmodif);
	else if (p.found == 0 && p.palpha >= 1 && p.pmodif == 0)
		return (p.palpha - 1);
	else if (p.found == 0 && p.pmodif == 0 && p.palpha == 0)
		return (start + 1);
	return (-1);
}

int				percent_nextocc(char *str, int start)
{
	int		i;
	int		f;

	f = 0;
	i = start;
	while (str[++i] != '\0' && (str[i] != '%' || !endofparse(str[i])))
		if (str[i] == '%' || endofparse(str[i]))
			f = 1;
	return (f);
}

int				ft_parse(t_env *e, char *str, int start)
{
	int			i;
	t_parser	p;

	i = start;
	init_parser_struct(&p);
	while (str[++i] != '\0' && (str[i] != '%' || !endofparse(str[i])))
		if (ft_checks(str, &i, &p) && (str[i] == '%' || endofparse(str[i])))
		{
			if (str[i] == '%')
			{
				if (p.pmodif != 0 || (p.palpha != 0 && percent_nextocc(str, i)))
					break ;
				ft_parse_percent(e, str, start, i);
			}
			else
			{
				if (pf_parse_type(e, str, start, i) == -1)
					return (i - 2);
			}
			p.found = 1;
			break ;
		}
	if (ft_parse_return(p, str, start) != -1)
		return (ft_parse_return(p, str, start));
	return (i);
}
