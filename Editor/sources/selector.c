/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   selector.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 14:27:48 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		square_fill(t_param *p, int limit_x, int limit_y)
{
	int		i;
	int		j;

	i = p->kevent.mouse_y;
	j = p->kevent.mouse_x;
	if (i >= limit_y)
		ft_swap(&i, &limit_y);
	j += j <= limit_x ? 1 : -1;
	while (i++ <= limit_y - 2)
		trace(p->mlx->render, (t_v){j, i}, (t_v){limit_x, i}, 0x555555);
}

void		selector_point_in(t_param *p, t_v start, t_v end)
{
	t_point		*tmp;

	if (start.x > end.x)
		ft_swap(&start.x, &end.x);
	if (start.y > end.y)
		ft_swap(&start.y, &end.y);
	if (p->p)
	{
		tmp = p->p;
		while (tmp)
		{
			if (tmp->x > start.x && tmp->x < end.x && tmp->y > start.y
			&& tmp->y < end.y && tmp->state != 2 && tmp->lay == p->lay)
				tmp->state = 2;
			else if (tmp->x < start.x && tmp->x > end.x && tmp->y < start.y
			&& tmp->y > end.y && tmp->state != 2 && tmp->lay == p->lay)
				tmp->state = 2;
			tmp = tmp->next;
		}
	}
}

void		selector_obj_in(t_param *p, t_v start, t_v end)
{
	t_obj		*tmp;

	if (start.x > end.x)
		ft_swap(&start.x, &end.x);
	if (start.y > end.y)
		ft_swap(&start.y, &end.y);
	if (p->o)
	{
		tmp = p->o;
		while (tmp)
		{
			if (tmp->pos.x > start.x && tmp->pos.x < end.x &&
			tmp->pos.y > start.y && tmp->pos.y < end.y &&
			tmp->state != 2 && tmp->lay == p->lay)
				tmp->state = 2;
			else if (tmp->pos.x < start.x && tmp->pos.x > end.x
			&& tmp->pos.y < start.y && tmp->pos.y > end.y
			&& tmp->state != 2 && tmp->lay == p->lay)
				tmp->state = 2;
			tmp = tmp->next;
		}
	}
}

void		square(t_param *p)
{
	t_v start;
	t_v mouse;

	if (p->kevent.mouse_1)
	{
		reset_state(p, p->p, p->w, p->o);
		start.x = p->kevent.mouse_last_x;
		start.y = p->kevent.mouse_last_y;
		mouse.x = p->kevent.mouse_x;
		mouse.y = p->kevent.mouse_y;
		trace(p->mlx->render, (t_v){start.x, start.y},
		(t_v){p->kevent.mouse_x, start.y}, 0xFFFFFF);
		trace(p->mlx->render, (t_v){start.x, start.y}, (t_v){start.x,
		p->kevent.mouse_y}, 0xFFFFFF);
		trace(p->mlx->render, (t_v){p->kevent.mouse_x, p->kevent.mouse_y},
		(t_v){p->kevent.mouse_x, start.y}, 0xFFFFFF);
		trace(p->mlx->render, (t_v){p->kevent.mouse_x, p->kevent.mouse_y},
		(t_v){start.x, p->kevent.mouse_y}, 0xFFFFFF);
		square_fill(p, start.x, start.y);
		selector_point_in(p, start, mouse);
		selector_obj_in(p, start, mouse);
	}
}

void		selector_wall(t_param *p)
{
	t_wall		*w;
	t_point		*v;
	int			count;

	if (p->w && p->p)
	{
		w = p->w;
		while (w)
		{
			count = 0;
			v = p->p;
			while (v)
			{
				if (w->p_one.i == v->i && v->state == 2 && v->lay == p->lay)
					count++;
				if (w->p_two.i == v->i && v->state == 2 && v->lay == p->lay)
					count++;
				if (count == 2)
					w->state = 2;
				v = v->next;
			}
			w = w->next;
		}
	}
}
