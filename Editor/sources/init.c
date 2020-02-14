/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 14:22:33 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		init_input(t_param *p)
{
	p->kevent.w = 0;
	p->kevent.s = 0;
	p->kevent.a = 0;
	p->kevent.d = 0;
	p->kevent.q = 0;
	p->kevent.e = 0;
	p->kevent.r = 0;
	p->kevent.f = 0;
	p->kevent.del = 0;
	p->kevent.ar_down = 0;
	p->kevent.ar_left = 0;
	p->kevent.ar_right = 0;
	p->kevent.ar_up = 0;
	p->kevent.space = 0;
	p->current_frame = 0;
	p->kevent.mouse_1 = 0;
	p->kevent.mouse_2 = 0;
	p->kevent.mouse_3 = 0;
	p->kevent.mouse_x = 0;
	p->kevent.mouse_y = 0;
	p->kevent.mouse_last_x = 0;
	p->kevent.mouse_last_y = 0;
	p->kevent.nb_1 = 0;
}

void		init_tools(t_param *p)
{
	p->i_point = 0;
	p->pick_tool = 0;
	p->i_wall = 0;
	p->i_room = 0;
	p->tool = 0;
	p->walltool.nb = 0;
	p->nb_tex = 2;
	p->lay = 0;
	p->switch_dis = 0;
	p->character.x = WIDTH / 2;
	p->character.y = HEIGHT / 2;
	p->character.z = 0;
	p->character.i = 0;
	p->character.state = 0;
	p->character.lay = 0;
	p->hightool.p1 = (t_point){0, 250, HEIGHT - 90, 0, 0, 0, NULL};
	p->hightool.p2 = (t_point){0, 450, HEIGHT - 90, 0, 0, 0, NULL};
	p->hightool.p3 = (t_point){0, 450, HEIGHT - 10, 0, 0, 0, NULL};
	p->hightool.p4 = (t_point){0, 250, HEIGHT - 10, 0, 0, 0, NULL};
}
