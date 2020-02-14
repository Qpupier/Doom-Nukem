/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   teleport.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/01 15:44:23 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	teleport_player(t_param *p, t_vec pos)
{
	t_vec	u;

	(!(p->pstate & FADEINOUT)
		&& !(p->pstate & TELEPORTING)) ? p->pstate |= FADEINOUT : 0;
	if (p->pstate & TELEPORTING)
	{
		u = vec_sub(p->player.position, p->player.current_position);
		doom_move(p, vec_sub(pos, u));
		p->player.current_position = (t_vec){0, 0, 0};
		p->player.position = pos;
		p->pstate ^= TELEPORTING;
	}
}
