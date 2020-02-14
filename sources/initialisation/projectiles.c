/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   projectiles.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/10 15:29:20 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 15:29:50 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		make_projectiles(t_param *p)
{
	int	i;

	i = -1;
	p->nb_projectiles = 0;
	while (++i < AMMO)
	{
		p->projectiles[i].texture = &p->textures[p->nb_textures - 6];
		p->projectiles[i].options = 0;
		p->projectiles[i].options |= O_INVISIBLE;
		p->projectiles[i].options |= O_PROJECTILE;
		p->projectiles[i].nb_points = 4;
		p->projectiles[i].proj.nb = 4 * 3;
		p->projectiles[i].points[0] = (t_vec){-15, -15, 0};
		p->projectiles[i].points[1] = (t_vec){15, -15, 0};
		p->projectiles[i].points[2] = (t_vec){15, 15, 0};
		p->projectiles[i].points[3] = (t_vec){-15, 15, 0};
		p->projectiles[i].room_ptr = NULL;
		p->projectiles[i].obj_ptr = NULL;
		p->projectiles[i].color = 0x330000;
		p->projectiles[i].tex[0] = p->projectiles[i].points[0];
		p->projectiles[i].tex[1] = p->projectiles[i].points[1];
		p->projectiles[i].tex[2] = p->projectiles[i].points[2];
		p->projectiles[i].tex[3] = p->projectiles[i].points[3];
	}
}
