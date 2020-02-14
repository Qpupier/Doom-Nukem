/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lift.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/01 16:05:10 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 16:03:29 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void			move_world(t_param *p, int ignore_room, t_objects *object,
	int *sign)
{
	register int				ir;
	register unsigned int		ip;
	t_rooms						*curr_room;
	t_vec						move;

	*sign = object->action.lift_value < 0 ? -1 : 1;
	move = (t_vec){0, 1 * *sign, 0};
	ir = -1;
	while (++ir < p->nb_rooms && (ip = -1))
	{
		curr_room = &p->rooms[ir];
		if (curr_room->index == (unsigned int)ignore_room)
			continue;
		while (++ip < curr_room->nb_walls)
			translate_polygons(&curr_room->walls[ip], move);
		translate_objects(curr_room, move);
		ip = -1;
		while (++ip < curr_room->nb_lights)
			curr_room->lights[ip].pos =
				vec_sub(curr_room->lights[ip].pos, move);
	}
}

static void			handle_lift_supl(t_param *p, int ignore_room,
	t_objects *object)
{
	int		sign;

	if (!object || ignore_room == -1)
	{
		(p->pstate & LIFT) ? (p->pstate ^= LIFT) : 0;
		return ;
	}
	move_world(p, ignore_room, object, &sign);
	object->action.lift_value -= 1 * sign;
	if (fabsf(object->action.lift_value) <= 0)
	{
		(p->pstate & LIFT) ? (p->pstate ^= LIFT) : 0;
		object->action.lift_state = -1;
	}
}

void				handle_lift(t_param *p)
{
	register int			index_room;
	register unsigned int	index_obj;
	int						ignore_room;
	t_objects				*object;

	if (!(p->pstate & LIFT))
		return ;
	ignore_room = -1;
	index_room = -1;
	object = NULL;
	while (++index_room < p->nb_rooms && ignore_room == -1)
	{
		index_obj = -1;
		while (++index_obj < p->rooms[index_room].nb_objects)
		{
			if (p->rooms[index_room].objects[index_obj].action.lift_state == 1)
			{
				ignore_room = p->rooms[index_room].index;
				object = &p->rooms[index_room].objects[index_obj];
				break ;
			}
		}
	}
	handle_lift_supl(p, ignore_room, object);
}
