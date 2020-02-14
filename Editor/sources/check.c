/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 16:33:30 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

int				wall_check_exist(t_param *p, t_point one, t_point two)
{
	t_wall		*tmp;

	if (p->w)
	{
		tmp = p->w;
		while (tmp)
		{
			if ((tmp->p_one.i == one.i && tmp->p_two.i == two.i) ||
				(tmp->p_two.i == one.i && tmp->p_one.i == two.i) ||
				(one.i == two.i))
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

static int		room_check_exist_bis(t_wall *tmpw, t_wall *tmpw2,
t_room *tmpr, int *count)
{
	while (tmpw && tmpw2)
	{
		if ((tmpw->p_one.i == tmpw2->p_one.i && tmpw->p_two.i ==
		tmpw2->p_two.i) || (tmpw->p_two.i == tmpw2->p_one.i &&
		tmpw->p_one.i == tmpw2->p_two.i))
			(*count)++;
		tmpw = tmpw->next;
		tmpw2 = tmpw2->next;
	}
	if (*count == count_list(tmpr->wall))
		return (0);
	return (1);
}

int				room_check_exist(t_param *p, t_wall *w)
{
	t_room		*tmpr;
	t_wall		*tmpw;
	t_wall		*tmpw2;
	int			count;

	count = 0;
	if (p->r)
	{
		tmpr = p->r;
		while (tmpr)
		{
			tmpw2 = w;
			tmpw = tmpr->wall;
			if (count_list(tmpw) == count_list(tmpw2))
				if (!room_check_exist_bis(tmpw, tmpw2, tmpr, &count))
					return (0);
			count = 0;
			tmpr = tmpr->next;
		}
	}
	return (1);
}

void			check_connection(t_param *p, t_wall *w)
{
	t_wall *tmpw;
	t_room *r;
	t_wall *rw;

	if (w)
	{
		tmpw = w;
		while (tmpw)
		{
			r = p->r;
			while (r)
			{
				rw = r->wall;
				while (rw)
				{
					if (rw->i == tmpw->i && rw->co && tmpw->co)
						wall_fill(p, rw, w);
					rw = rw->next;
				}
				r = r->next;
			}
			tmpw = tmpw->next;
		}
	}
}
