/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tweak_wall.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 12:48:26 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void			tweak_select_point(t_param *p, t_point *points, int size)
{
	if (touch_point(p, points, size))
	{
		if (points->state != 2)
			points->state = 1;
		if (p->kevent.mouse_1)
		{
			if (points->state != 2)
				points->state = 2;
			else
				points->state = 1;
			p->kevent.mouse_1 = 0;
		}
	}
	else if (((!touch_point(p, points, size)) && points->state != 2))
		points->state = 0;
}

void			tweak_high_modif(t_param *p)
{
	t_wall		*tmp;

	tmp = p->w;
	if (p->kevent.mouse_4 || p->kevent.mouse_5)
	{
		while (tmp)
		{
			if (tmp->state == 2)
			{
				if (p->hightool.p1.state == 2)
					tmp->p_one.z += p->kevent.mouse_4 ? 5 : -5;
				if (p->hightool.p2.state == 2)
					tmp->p_two.z += p->kevent.mouse_4 ? 5 : -5;
				if (p->hightool.p3.state == 2)
					tmp->p_three.z += p->kevent.mouse_4 ? 5 : -5;
				if (p->hightool.p4.state == 2)
					tmp->p_four.z += p->kevent.mouse_4 ? 5 : -5;
			}
			tmp = tmp->next;
		}
		p->kevent.f = 0;
	}
}

static void		tweak_tool_display_bis(t_param *p)
{
	trace(p->mlx->render, (t_v){p->hightool.p1.x, p->hightool.p1.y},
	(t_v){p->hightool.p2.x, p->hightool.p2.y}, 0xFFFFFF);
	trace(p->mlx->render, (t_v){p->hightool.p2.x, p->hightool.p2.y},
	(t_v){p->hightool.p3.x, p->hightool.p3.y}, 0xFFFFFF);
	trace(p->mlx->render, (t_v){p->hightool.p3.x, p->hightool.p3.y},
	(t_v){p->hightool.p4.x, p->hightool.p4.y}, 0xFFFFFF);
	trace(p->mlx->render, (t_v){p->hightool.p4.x, p->hightool.p4.y},
	(t_v){p->hightool.p1.x, p->hightool.p1.y}, 0xFFFFFF);
}

void			tweak_tool_display(t_param *p)
{
	tweak_select_point(p, &p->hightool.p1, 5);
	tweak_select_point(p, &p->hightool.p2, 5);
	tweak_select_point(p, &p->hightool.p3, 5);
	tweak_select_point(p, &p->hightool.p4, 5);
	if (walls_selected(p))
	{
		tweak_tool_display_bis(p);
		fillcircle(p, (t_v){p->hightool.p1.x, p->hightool.p1.y},
		5, p->hightool.p1.state == 2 ? 0xff0066 : 0xffffff);
		fillcircle(p, (t_v){p->hightool.p2.x, p->hightool.p2.y},
		5, p->hightool.p2.state == 2 ? 0xff0066 : 0xffffff);
		fillcircle(p, (t_v){p->hightool.p3.x, p->hightool.p3.y},
		5, p->hightool.p3.state == 2 ? 0xff0066 : 0xffffff);
		fillcircle(p, (t_v){p->hightool.p4.x, p->hightool.p4.y},
		5, p->hightool.p4.state == 2 ? 0xff0066 : 0xffffff);
		tweak_high_modif(p);
	}
}

void			wall_set_connect(t_param *p)
{
	t_wall		*tmp;

	tmp = p->w;
	if (p->kevent.a)
	{
		while (tmp)
		{
			if (tmp->state == 2)
			{
				tmp->co = 1;
				tmp->tex = -2;
			}
			tmp = tmp->next;
		}
		p->kevent.a = 0;
	}
}
