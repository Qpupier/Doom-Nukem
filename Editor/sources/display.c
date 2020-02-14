/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 11:29:36 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	trace_walls_bis(t_param *p, t_wall *t)
{
	if (t->state == 0)
		trace(p->mlx->render, (t_v){t->p_one.x, t->p_one.y},
		(t_v){t->p_two.x, t->p_two.y}, t->lay == p->lay ? 0xFFFFFF : 0xaaaaaa);
	if (t->state == 1)
		trace(p->mlx->render, (t_v){t->p_one.x, t->p_one.y},
		(t_v){t->p_two.x, t->p_two.y}, t->lay == p->lay ? 0x9ec0d0 : 0x9ec0d0);
	else if (t->co == 1)
		trace(p->mlx->render, (t_v){t->p_one.x, t->p_one.y},
		(t_v){t->p_two.x, t->p_two.y}, t->lay == p->lay ? 0x99ff66 : 0x99ff66);
	if (t->state == 2)
		trace(p->mlx->render, (t_v){t->p_one.x, t->p_one.y},
		(t_v){t->p_two.x, t->p_two.y}, t->lay == p->lay ? 0x50cfcf : 0x50cfcf);
}

void		trace_walls(t_param *p, t_wall *w)
{
	t_wall		*t;

	if (w)
	{
		t = w;
		while (t)
		{
			trace_walls_bis(p, t);
			t = t->next;
		}
	}
}

void		trace_points(t_param *p)
{
	t_point			*tmp;

	if (p->p)
	{
		tmp = p->p;
		while (tmp)
		{
			if (tmp->state == 2)
				fillcircle(p, (t_v){tmp->x, tmp->y}, 5, tmp->lay == p->lay ?
				0xff0066 : 0xff88ff);
			if (tmp->state == 1)
				fillcircle(p, (t_v){tmp->x, tmp->y}, 6, tmp->lay == p->lay ?
				0xff9999 : 0xffdddd);
			if (tmp->state == 0)
				fillcircle(p, (t_v){tmp->x, tmp->y}, 5, tmp->lay == p->lay ?
				0xff6666 : 0xffaaff);
			tmp = tmp->next;
		}
	}
}

void		trace_rooms(t_param *p)
{
	t_room		*tmpr;
	t_wall		*tmpw;

	if (p->r)
	{
		tmpr = p->r;
		while (tmpr)
		{
			tmpw = tmpr->wall;
			while (tmpw)
			{
				trace_walls(p, tmpw);
				fillcircle(p, (t_v){tmpw->p_one.x, tmpw->p_one.y},
				5, 0xff0066);
				fillcircle(p, (t_v){tmpw->p_two.x, tmpw->p_two.y},
				5, 0xff0066);
				tmpw = tmpw->next;
			}
			tmpr = tmpr->next;
		}
	}
}

void		trace_rooms_nb(t_param *p)
{
	t_room		*tmpr;
	char		*tmp;
	int			i;

	i = 0;
	if (p->r)
	{
		tmpr = p->r;
		while (tmpr)
		{
			tmp = ft_itoa(i);
			mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmpr->wall->p_one.x
			+ 20, tmpr->wall->p_one.y + 20, 0xffffff, tmp);
			i++;
			free(tmp);
			tmpr = tmpr->next;
		}
	}
}
