/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   movements_rotate_supl.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/07 20:07:18 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 20:16:43 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	rotate_actions(t_param *p,
		t_vec (*fct)(t_vec vec, float vsin, float vcos), float vsin, float vcos)
{
	int			id_actions;
	t_actions	action;

	id_actions = -1;
	while (++id_actions < p->nb_actions)
	{
		action = p->actions[id_actions];
		action.pos = fct(action.pos, vsin, vcos);
		action.pos_curr = fct(action.pos_curr, vsin, vcos);
		action.pos_inc = fct(action.pos_inc, vsin, vcos);
	}
}

void	rotate_projectiles(t_param *p,
		t_vec (*fct)(t_vec vec, float vsin, float vcos), float vsin, float vcos)
{
	int	index;

	index = -1;
	while (++index < p->nb_projectiles)
	{
		p->projectiles[index].points[0] = 	\
				fct(p->projectiles[index].points[0], vsin, vcos);
		p->projectiles[index].points[1] = 	\
				fct(p->projectiles[index].points[1], vsin, vcos);
		p->projectiles[index].points[2] = 	\
				fct(p->projectiles[index].points[2], vsin, vcos);
		p->projectiles[index].points[3] = 	\
				fct(p->projectiles[index].points[3], vsin, vcos);
		p->projectiles[index].tex[0] = 		\
				fct(p->projectiles[index].tex[0], vsin, vcos);
		p->projectiles[index].tex[1] = 		\
				fct(p->projectiles[index].tex[1], vsin, vcos);
		p->projectiles[index].tex[2] = 		\
				fct(p->projectiles[index].tex[2], vsin, vcos);
		p->projectiles[index].tex[3] = 		\
				fct(p->projectiles[index].tex[3], vsin, vcos);
	}
}
