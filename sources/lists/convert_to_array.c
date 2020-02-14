/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_to_array.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 08:22:04 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 15:41:26 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			convert_objects(t_param *p, t_list_objects *lst_objects,
									unsigned int nb_objects, t_objects *obj)
{
	t_list_objects	*tmp;
	unsigned int	object_index;
	t_objects		*curr;

	object_index = 0;
	tmp = lst_objects;
	while (lst_objects && object_index <= nb_objects)
	{
		curr = &obj[object_index];
		curr->nb_polygons = tlist_count_polygon(lst_objects->poly);
		if (!(obj[object_index].poly = (t_polygon *)malloc(sizeof(t_polygon)
														* curr->nb_polygons)))
			handle_error(p, E_ERROR_MALLOC);
		convert_object_copy_data(curr, lst_objects);
		copy_polygons(lst_objects->poly, curr->nb_polygons, curr->poly);
		object_index++;
		lst_objects = lst_objects->next;
	}
}

void			allocate_arrays(t_param *p, t_rooms *room)
{
	if (!(room->walls = malloc(sizeof(t_polygon) * room->nb_walls)))
		handle_error(p, E_ERROR_MALLOC);
	if (!(room->objects = malloc(sizeof(t_objects) * room->nb_objects)))
		handle_error(p, E_ERROR_MALLOC);
	if (!(room->lights = malloc(sizeof(t_lights) * room->nb_lights)))
		handle_error(p, E_ERROR_MALLOC);
}

static void		copy_everything(t_param *p)
{
	unsigned int		room_index;
	t_list_room			*lst_room;
	t_rooms				*curr;

	lst_room = p->room_list;
	room_index = 0;
	while (lst_room)
	{
		curr = &p->rooms[room_index];
		convert_lights(lst_room->lights, curr->nb_lights, curr->lights);
		convert_objects(p, lst_room->objects, curr->nb_objects, curr->objects);
		copy_polygons(lst_room->walls, curr->nb_walls, curr->walls);
		room_index++;
		lst_room = lst_room->next;
	}
}

void			list_to_array(t_param *p)
{
	int					room_index;
	t_list_room			*lst_room;
	t_rooms				*curr;

	p->nb_object = 0;
	p->nb_rooms = tlist_count_rooms(p);
	if (!(p->rooms = (t_rooms *)malloc(sizeof(t_rooms) * p->nb_rooms)))
		handle_error(p, E_ERROR_MALLOC);
	room_index = 0;
	lst_room = p->room_list;
	while (lst_room && room_index <= p->nb_rooms)
	{
		curr = &p->rooms[room_index];
		curr->nb_walls = tlist_count_walls(lst_room);
		curr->nb_objects = tlist_count_objects(lst_room);
		curr->nb_lights = tlist_count_lights(lst_room);
		allocate_arrays(p, &p->rooms[room_index]);
		room_index++;
		lst_room = lst_room->next;
	}
	copy_everything(p);
}
