/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   select_algo.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/04 14:43:47 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		select_points(t_param *p, t_point **points, int size)
{
	t_point			*tmp;

	tmp = *points;
	if (points)
		while (tmp)
		{
			if (touch_point(p, tmp, size) && tmp->lay == p->lay)
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
			else if (((!touch_point(p, tmp, size)) && tmp->state != 2))
				tmp->state = 0;
			tmp = tmp->next;
		}
}

void		select_walls(t_param *p, t_wall **wall, int size)
{
	t_wall		*tmp;

	tmp = *wall;
	if (wall)
		while (tmp)
		{
			if (touch_wall(p, *tmp, size) && tmp->lay == p->lay)
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
			else if (((!touch_wall(p, *tmp, size)) && tmp->state != 2))
				tmp->state = 0;
			tmp = tmp->next;
		}
}

void		selected_points(t_param *p)
{
	t_point		*tmp;
	t_wall		w;
	int			nb_selected;

	tmp = p->p;
	nb_selected = 0;
	if (p->p)
	{
		while ((tmp))
		{
			if (tmp->state == 2)
			{
				if (!nb_selected)
					w.p_one = *tmp;
				else if (nb_selected == 1)
					w.p_two = *tmp;
				nb_selected++;
			}
			tmp = tmp->next;
		}
		w.lay = p->lay;
		if (p->kevent.mouse_3 && nb_selected == 2)
			wall_connect(p, w);
	}
}
