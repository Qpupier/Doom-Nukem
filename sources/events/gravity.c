/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gravity.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 11:49:34 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 19:31:56 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"
#include "stdio.h"

static void			start_conditions(t_param *p)
{
	t_vec		move;

	move = (t_vec){0, -25.0, 0};
	if (p->keys & K_JUMP && !(p->pstate & IS_JUMPING))
	{
		p->pstate |= IS_JUMPING;
		p->keys ^= K_JUMP;
	}
	if (p->pstate & IS_JUMPING)
	{
		if (!collision(p, &move))
			doom_move(p, move);
		else
			p->pstate ^= IS_JUMPING;
		if (move.y != -25.0)
			p->pstate ^= IS_JUMPING;
	}
}

static float		end_conditions(t_param *p, float dist, float speed,
	t_polygon *poly)
{
	t_vec	move;
	float	next_dist;
	t_vec	mtmp;
	int		col;

	move = (t_vec){0, speed, 0};
	mtmp = move;
	proj_point_plane(move, poly->fix_plane, &next_dist);
	col = collision(p, &mtmp);
	if (dist >= 125 && next_dist >= 115 && !col)
		!(p->pstate & IS_FALLING) ? (p->pstate |= IS_FALLING) : 0;
	else
		(p->pstate & IS_FALLING) ? (p->pstate ^= IS_FALLING) : 0;
	if (p->pstate & IS_FALLING)
	{
		doom_move(p, move);
		return (1);
	}
	else
	{
		(p->pstate & IS_JUMPING && speed) ? (p->pstate ^= IS_JUMPING) : 0;
		return (0);
	}
}

static void			prepare_data(t_param *p, float *dist, t_polygon **polygon)
{
	int			i;

	i = -1;
	p->player.current_room = -1;
	while (++i < (int)p->total_polygons)
	{
		if (p->lst_polygons[i]->options & O_INVISIBLE)
			continue ;
		make_fixed(p->lst_polygons[i]);
		if (check_under(p->lst_polygons[i]) && p->lst_polygons[i]->dist_y >= 0
			&& p->lst_polygons[i]->dist_y <= *dist)
		{
			*dist = p->lst_polygons[i]->dist_y;
			p->player.current_room = p->lst_polygons[i]->room_ptr->index;
			*polygon = p->lst_polygons[i];
		}
	}
}

void				process_gravity(t_param *p)
{
	static int		ratio = 1;
	float			dist;
	float			speed;
	t_polygon		*poly;

	p->player.current_room = -1;
	dist = INFINITY;
	poly = NULL;
	prepare_data(p, &dist, &poly);
	if (!poly || (p->pstate & FLYING))
		return ;
	start_conditions(p);
	speed = sqrt(9.81 * 5 / (30) * ratio);
	speed *= 4.0;
	if (end_conditions(p, dist, speed, poly))
		ratio++;
	else
		ratio = 0;
}
