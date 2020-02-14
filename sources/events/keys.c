/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   keys.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 12:00:49 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 19:30:39 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static inline void	ev_setevt(unsigned int *keys, unsigned int action,
	short int state)
{
	if (state)
		*keys |= action;
	else
		*keys ^= action;
}

inline static void	ev_setkey(int key, short int state, t_param *p)
{
	if (key == W)
		ev_setevt(&p->keys, K_MOVE_FORWARD, state);
	else if (key == S)
		ev_setevt(&p->keys, K_MOVE_BACKWARD, state);
	else if (key == A)
		ev_setevt(&p->keys, K_STRAFE_LEFT, state);
	else if (key == D)
		ev_setevt(&p->keys, K_STRAFE_RIGHT, state);
	else if (key == R)
		ev_setevt(&p->keys, K_MOVE_UP, state);
	else if (key == F)
		ev_setevt(&p->keys, K_MOVE_DOWN, state);
	else if (key == UP)
		ev_setevt(&p->keys, K_LOOK_UP, state);
	else if (key == DOWN)
		ev_setevt(&p->keys, K_LOOK_DOWN, state);
	else if (key == LEFT)
		ev_setevt(&p->keys, K_TILT_LEFT, state);
	else if (key == RIGHT)
		ev_setevt(&p->keys, K_TILT_RIGHT, state);
	else if (key == SHIFT)
		ev_setevt(&p->keys, K_SHIFT, state);
	else if (key == CTRL)
		ev_setevt(&p->keys, K_CROUNCH, state);
}

int					ev_keyrelease(int key, struct s_param *p)
{
	if (key == ESC)
	{
		if (!(p->pstate & M_PAUSE))
		{
			mlx_mouse_show();
			p->pstate |= M_PAUSE;
		}
		else
			free_and_exit(p);
	}
	if (key == H)
	{
		if (p->pstate & FLYING)
			p->pstate ^= FLYING;
		else
			p->pstate |= FLYING;
	}
	ev_setkey(key, 0, p);
	return (1);
}

int					ev_keypress(int key, struct s_param *p)
{
	ev_setkey(key, 1, p);
	if (key == SPACE)
		ev_setevt(&p->keys, K_JUMP, 1);
	else if (key == E)
		ev_setevt(&p->keys, K_E, 1);
	else if (key == 82)
		(p->pstate & RASTER) ? (p->pstate ^= RASTER) : (p->pstate |= RASTER);
	else if (key == 83)
		(p->pstate & WIREFRAME) ? (p->pstate ^= WIREFRAME) :
			(p->pstate |= WIREFRAME);
	return (1);
}
