/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   events.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/20 18:57:19 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

static void		ev_setkey_bis(int key, short int state, t_param *p)
{
	if (key == R)
		p->kevent.r = state;
	if (key == F)
		p->kevent.f = state;
	if (key == MORE)
		p->kevent.add = state;
	if (key == LESS)
		p->kevent.sub = state;
	if (key == SPACE)
		p->kevent.space = state;
	if (key == SUP)
		p->kevent.del = state;
	if (key == NB_1)
		p->kevent.nb_1 = state;
}

static void		ev_setkey(int key, short int state, t_param *p)
{
	if (key == W)
		p->kevent.w = state;
	if (key == S)
		p->kevent.s = state;
	if (key == A)
		p->kevent.a = state;
	if (key == D)
		p->kevent.d = state;
	if (key == Q)
		p->kevent.q = state;
	if (key == E)
		p->kevent.e = state;
	ev_setkey_bis(key, state, p);
}

int				ev_keyrelease(int key, struct s_param *p)
{
	if (key == ESC)
		exit(1);
	ev_setkey(key, 0, p);
	return (1);
}

int				ev_keypress(int key, struct s_param *p)
{
	ev_setkey(key, 1, p);
	return (1);
}
