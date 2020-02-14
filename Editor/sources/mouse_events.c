/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mouse_events.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/27 14:31:20 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	ev_setmouse(int key, short int state, t_param *p)
{
	if (key == 1)
		p->kevent.mouse_1 = state;
	if (key == 2)
		p->kevent.mouse_2 = state;
	if (key == 3)
		p->kevent.mouse_3 = state;
	if (key == 4)
		p->kevent.mouse_4 = state;
	if (key == 5)
		p->kevent.mouse_5 = state;
}

int			ev_mousepress(int key, int x, int y, struct s_param *p)
{
	p->kevent.mouse_last_x = x;
	p->kevent.mouse_last_y = y;
	ev_setmouse(key, 1, p);
	return (1);
}

int			ev_mouserelease(int key, int x, int y, struct s_param *p)
{
	(void)x;
	(void)y;
	ev_setmouse(key, 0, p);
	return (1);
}

int			ev_mousemove(int x, int y, struct s_param *p)
{
	p->kevent.mouse_x = x;
	p->kevent.mouse_y = y;
	return (1);
}
