/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   progress_bar.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/26 16:55:31 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:52:24 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		progress_comments(t_param *p, t_list_line *lines)
{
	t_list_line		*tmp;

	tmp = lines;
	while (tmp)
	{
		if (ft_strnequ("##", tmp->line, 2))
		{
			usleep(35000);
			show_parseprogress(p);
		}
		tmp = tmp->next;
	}
}

void		ft_putstr_rgb(char *str, int r, int g, int b)
{
	ft_putstr("\x1b[38;2;");
	ft_putnbr(r);
	ft_putchar(';');
	ft_putnbr(g);
	ft_putchar(';');
	ft_putnbr(b);
	ft_putstr(";m");
	ft_putstr(str);
	ft_putstr("\e[0m");
}

int			show_parseprogress(t_param *p)
{
	int		value;

	value = (p->parse_progress * 100 / p->parse_total_line);
	if (value % 2 == 0 && p->parse_loading_bar != value)
	{
		p->parse_loading_bar = value;
		ft_putstr_rgb("|", 0, 150 + value, 155 - value);
	}
	p->parse_progress++;
	return (1);
}
