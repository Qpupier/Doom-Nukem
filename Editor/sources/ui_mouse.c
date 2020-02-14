/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ui_mouse.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 12:15:27 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

static void		delete_func(t_param *p)
{
	point_delete_all(p, &p->p);
	wall_delete_all(p, &p->w);
	room_delete_all(p, &p->r);
	obj_delete_all(&p->o);
	p->walltool.nb = 0;
}

void			selec_mouse(t_param *p)
{
	if (p->kevent.mouse_1)
	{
		if (touch_pixel(p, (t_v){100, HEIGHT - 50}, 100, 50))
			p->pick_tool = 0;
		if (touch_pixel(p, (t_v){25, HEIGHT - 75}, 25, 25))
			p->tool = 0;
		if (touch_pixel(p, (t_v){75, HEIGHT - 75}, 25, 25))
			p->tool = 1;
		if (touch_pixel(p, (t_v){125, HEIGHT - 75}, 25, 25))
			p->tool = 2;
		if (touch_pixel(p, (t_v){175, HEIGHT - 75}, 25, 25))
			p->tool = 3;
		if (touch_pixel(p, (t_v){25, HEIGHT - 25}, 25, 25))
		{
			point_delete(p, &p->p);
			wall_delete(p, &p->w);
			obj_delete(&p->o);
			p->walltool.nb = 0;
		}
		if (touch_pixel(p, (t_v){75, HEIGHT - 25}, 25, 25))
			delete_func(p);
		if (touch_pixel(p, (t_v){125, HEIGHT - 25}, 25, 25))
			create_file(p);
	}
}
