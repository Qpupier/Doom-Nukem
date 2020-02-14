/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   events.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/20 18:57:19 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 21:07:56 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		process(t_param *p, t_vec move)
{
	if (p->keys & K_CROUNCH && (move.x || move.y || move.z > 0))
		move = vec_mult_float(move, 0.35);
	if (p->keys & K_SHIFT && !(p->keys & K_CROUNCH)
		&& (move.x || move.y || move.z > 0))
		move = vec_mult_float(move, 3);
	doom_rotate(p, vec_roty, p->player.roty_vsin, p->player.roty_vcos);
	if (p->pstate & FLYING)
	{
		doom_rotate(p, vec_rotx, p->player.rotx_vsin, p->player.rotx_vcos);
		p->player.rotx_vsin = 0;
		p->player.rotx_vcos = 1;
	}
	p->player.roty_vsin = 0;
	p->player.roty_vcos = 1;
	if ((move.x || move.y || move.z) && !(collision(p, &move)))
		doom_move(p, move);
}

void			process_keys(t_param *p)
{
	t_vec		move;

	move = (t_vec){0, 0, 0};
	if (p->keys & K_MOVE_FORWARD && !(p->keys & K_MOVE_BACKWARD))
		move = vec_add(move, (t_vec){0, 0, 30});
	if (p->keys & K_MOVE_BACKWARD && !(p->keys & K_MOVE_FORWARD))
		move = vec_add(move, (t_vec){0, 0, -15});
	if (p->keys & K_STRAFE_LEFT)
		move = vec_add(move, (t_vec){-10, 0, 0});
	if (p->keys & K_STRAFE_RIGHT)
		move = vec_add(move, (t_vec){10, 0, 0});
	if (p->keys & K_MOVE_UP && (p->pstate & FLYING))
		move = vec_add(move, (t_vec){0, 30, 0});
	if (p->keys & K_MOVE_DOWN && (p->pstate & FLYING))
		move = vec_add(move, (t_vec){0, -30, 0});
	if (p->keys & K_LOOK_UP)
		doom_rotate(p, vec_rotx, sin(-0.0174533), cos(-0.0174533));
	if (p->keys & K_LOOK_DOWN)
		doom_rotate(p, vec_rotx, sin(0.0174533), cos(0.0174533));
	if (p->keys & K_TILT_LEFT)
		doom_rotate(p, vec_rotz, sin(0.0174533), cos(0.0174533));
	if (p->keys & K_TILT_RIGHT)
		doom_rotate(p, vec_rotz, sin(-0.0174533), cos(-0.0174533));
	process(p, move);
}
