/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   polygon.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 11:32:43 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 21:09:52 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		set_data(t_param *p, t_polygon *poly)
{
	poly->proj.nb = poly->nb_points * 3;
	(void)p;
}

static void		set_polygon_data(t_param *p, t_polygon *curr_poly,
	t_rooms *room_ptr, t_objects *obj_ptr)
{
	curr_poly->room_ptr = room_ptr;
	curr_poly->obj_ptr = obj_ptr;
	curr_poly->index = p->total_polygons;
	curr_poly->colle = -1;
	if (obj_ptr)
	{
		if (obj_ptr->action.action_id >= p->nb_actions)
			obj_ptr->action.action_id = -1;
		if (obj_ptr->action.boom_id >= p->nb_actions)
			obj_ptr->action.boom_id = -1;
		if (obj_ptr->action.click_id >= p->nb_actions)
			obj_ptr->action.click_id = -1;
		if (obj_ptr->action.dis_id >= p->nb_actions)
			obj_ptr->action.dis_id = -1;
		if (obj_ptr->action.end_id >= p->nb_actions)
			obj_ptr->action.end_id = -1;
		if (obj_ptr->action.touch_id >= p->nb_actions)
			obj_ptr->action.touch_id = -1;
	}
}

static void		bulk_init(t_param *p, unsigned int index_room,
	t_rooms *curr_room)
{
	unsigned int	index_object;
	unsigned int	index_poly;
	t_objects		*curr_obj;
	t_polygon		*curr_poly;

	index_poly = -1;
	while (++index_poly < curr_room->nb_walls && ++p->total_polygons)
	{
		curr_poly = &curr_room->walls[index_poly];
		set_polygon_data(p, curr_poly, &p->rooms[index_room], NULL);
		set_data(p, curr_poly);
	}
	index_object = -1;
	while (++index_object < curr_room->nb_objects && (index_poly = -1))
	{
		curr_obj = &curr_room->objects[index_object];
		curr_obj->id = p->nb_object++;
		while (++index_poly < curr_obj->nb_polygons && ++p->total_polygons)
		{
			curr_poly = &curr_obj->poly[index_poly];
			set_polygon_data(p, curr_poly, &p->rooms[index_room],
				&p->rooms[index_room].objects[index_object]);
			set_data(p, curr_poly);
		}
	}
}

void			init_polygons(t_param *p)
{
	int			index_room;

	index_room = -1;
	p->total_polygons = 0;
	while (++index_room < p->nb_rooms)
	{
		p->rooms[index_room].index = index_room;
		bulk_init(p, index_room, &p->rooms[index_room]);
	}
	init_polygon_only_array(p);
}
