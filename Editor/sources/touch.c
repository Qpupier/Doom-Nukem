/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   touch.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:56:57 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

int			touch_point(t_param *p, t_point *point, int size)
{
	if (p->kevent.mouse_x < point->x + size &&
	p->kevent.mouse_x > point->x - size &&
	p->kevent.mouse_y < point->y + size &&
	p->kevent.mouse_y > point->y - size)
		return (1);
	return (0);
}

int			touch_pixel(t_param *p, t_v v, int sizex, int sizey)
{
	if (p->kevent.mouse_x < v.x + sizex &&
	p->kevent.mouse_x > v.x - sizex &&
	p->kevent.mouse_y < v.y + sizey &&
	p->kevent.mouse_y > v.y - sizey)
		return (1);
	return (0);
}

int			all_t_p(t_param *p, t_point **point, int size)
{
	t_point		*tmp;

	if (point)
	{
		tmp = *point;
		while (tmp)
		{
			if (p->kevent.mouse_x < tmp->x + size &&
			p->kevent.mouse_x > tmp->x - size &&
			p->kevent.mouse_y < tmp->y + size &&
			p->kevent.mouse_y > tmp->y - size && tmp->lay == p->lay)
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

t_point		*which_mouse_point(t_param *p, int size)
{
	t_point		*tmp;

	if (p->p)
	{
		tmp = p->p;
		while (tmp)
		{
			if (p->kevent.mouse_x < tmp->x + size &&
			p->kevent.mouse_x > tmp->x - size &&
			p->kevent.mouse_y < tmp->y + size &&
			p->kevent.mouse_y > tmp->y - size)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}
