/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   doom.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 14:01:46 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:53:17 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int		room_push(t_list_room **room, t_list_room data)
{
	t_list_room		*new_room;

	if (!(new_room = malloc(sizeof(t_list_room))))
		return (E_ERROR_MALLOC);
	new_room->objects = data.objects;
	new_room->walls = data.walls;
	new_room->lights = data.lights;
	new_room->next = NULL;
	if (*room != NULL)
		new_room->next = *room;
	*room = new_room;
	return (E_SUCCESS);
}

int		object_push(t_list_objects **object, t_list_polygons *poly)
{
	t_list_objects		*new_object;

	if (!(new_object = malloc(sizeof(t_list_objects))))
		return (E_ERROR_MALLOC);
	new_object->poly = poly;
	new_object->rot = (t_vec){0, 0, 0};
	new_object->next = NULL;
	if (*object != NULL)
		new_object->next = *object;
	*object = new_object;
	return (E_SUCCESS);
}

int		points_pushback(t_list_points **points, t_vec vertex)
{
	t_list_points	*new_point;
	t_list_points	*tmp;

	if (!(new_point = malloc(sizeof(t_list_points))))
		return (E_ERROR_MALLOC);
	new_point->point = vertex;
	new_point->next = NULL;
	if (!*points)
		*points = new_point;
	else
	{
		tmp = *points;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_point;
	}
	return (E_SUCCESS);
}

int		lights_push(t_list_lights **list, t_list_lights data)
{
	t_list_lights	*new;

	if (!(new = malloc(sizeof(t_list_lights))))
		return (E_ERROR_MALLOC);
	new->pos = data.pos;
	new->intensity = data.intensity;
	new->color = data.color;
	new->next = NULL;
	if (*list != NULL)
		new->next = *list;
	*list = new;
	return (E_SUCCESS);
}
