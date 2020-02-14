/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   selected_obj.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 13:00:21 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

int			points_selected(t_param *p)
{
	t_point		*tmp;
	int			count;

	if (p->p)
	{
		count = 0;
		tmp = p->p;
		while (tmp)
		{
			if (tmp->state == 2)
				count++;
			tmp = tmp->next;
		}
		return (count);
	}
	return (0);
}

int			walls_selected(t_param *p)
{
	t_wall		*tmp;
	int			count;

	if (p->w)
	{
		count = 0;
		tmp = p->w;
		while (tmp)
		{
			if (tmp->state == 2)
				count++;
			tmp = tmp->next;
		}
		return (count);
	}
	return (0);
}

void		select_obj(t_param *p, t_obj **obj, int s)
{
	t_obj		*tmp;

	tmp = *obj;
	if (p->o)
		while (tmp)
		{
			if (touch_pixel(p, (t_v){tmp->pos.x, tmp->pos.y}, s, s)
			&& tmp->lay == p->lay)
			{
				if (tmp->state != 2)
					tmp->state = 1;
				if (p->kevent.mouse_1)
				{
					if (tmp->state != 2)
						tmp->state = 2;
					else
						tmp->state = 1;
					p->kevent.mouse_1 = 0;
				}
			}
			else if (((!touch_pixel(p, (t_v){tmp->pos.x, tmp->pos.y}, s, s)
			&& tmp->state != 2)))
				tmp->state = 0;
			tmp = tmp->next;
		}
}

void		select_character(t_param *p, int s)
{
	t_point		*tmp;

	tmp = &p->character;
	if (touch_pixel(p, (t_v){tmp->x, tmp->y}, s, s))
	{
		if (tmp->state != 2)
			tmp->state = 1;
		if (p->kevent.mouse_1)
		{
			if (tmp->state != 2)
				tmp->state = 2;
			else
				tmp->state = 1;
			p->kevent.mouse_1 = 0;
		}
	}
	else if (((!touch_pixel(p, (t_v){tmp->x, tmp->y}, s, s)
	&& tmp->state != 2)))
		tmp->state = 0;
}
