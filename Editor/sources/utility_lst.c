/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utility_lst.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/04 22:04:52 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

int			in_ui(t_param *p)
{
	if (p->kevent.mouse_y > HEIGHT - 150)
		return (0);
	return (1);
}

t_point		get_last(t_param *p)
{
	t_point		*tmp;

	if (p->p)
	{
		tmp = p->p;
		while (tmp->next)
			tmp = tmp->next;
		return (*tmp);
	}
	tmp = NULL;
	return (*tmp);
}

void		last_to_first(t_param *p)
{
	t_point			*tmp;
	t_point			*lst;

	if (p->kevent.mouse_2 && p->p)
	{
		tmp = p->p;
		lst = p->p;
		while (tmp->next)
			tmp = tmp->next;
		trace(p->mlx->render, (t_v){lst->x, lst->y},
		(t_v){tmp->x, tmp->y}, 0xFFFFFF);
		p->kevent.mouse_2 = 0;
	}
}

int			count_list(t_wall *w)
{
	t_wall		*tmp;
	int			i;

	i = 0;
	if (w)
	{
		tmp = w;
		while (tmp)
		{
			i++;
			tmp = tmp->next;
		}
	}
	return (i);
}
