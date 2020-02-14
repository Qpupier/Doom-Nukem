/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   movements_rotate.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/01 12:57:32 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 20:08:13 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

inline static void	rotate_axis(t_axis *axis,
	t_vec (*fct)(t_vec vec, float vsin, float vcos), float vsin, float vcos)
{
	axis->x = fct(axis->x, vsin, vcos);
	axis->y = fct(axis->y, vsin, vcos);
	axis->z = fct(axis->z, vsin, vcos);
}

inline static void	rotate_polygons(t_polygon *poly,
	t_vec (*fct)(t_vec vec, float vsin, float vcos), float vsin, float vcos)
{
	register unsigned int	index_point;

	index_point = -1;
	while (++index_point < poly->nb_points)
		poly->points[index_point] = fct(poly->points[index_point], vsin, vcos);
	index_point = -1;
	while (!(poly->options & HAS_BEEN_TRIANGULATED) && ++index_point < 4)
		poly->tex[index_point] = fct(poly->tex[index_point], vsin, vcos);
	if (poly->options & IS_SPRITE)
	{
		poly->vn = fct(poly->vn, vsin, vcos);
		rotate_axis(&poly->axis, fct, vsin, vcos);
	}
}

inline static void	rotate_objects(t_rooms *room,
	t_vec (*fct)(t_vec vec, float vsin, float vcos), float vsin, float vcos)
{
	register unsigned int	index_object;
	register unsigned int	index_point;
	t_objects				*curr_obj;
	t_polygon				*curr_poly;
	unsigned int			index_poly;

	index_object = -1;
	while (++index_object < room->nb_objects)
	{
		curr_obj = &room->objects[index_object];
		if (curr_obj->state & OBJ_DISABLE)
			continue ;
		curr_obj->action.teleport_position =
			fct(curr_obj->action.teleport_position, vsin, vcos);
		rotate_axis(&curr_obj->axis, fct, vsin, vcos);
		index_poly = -1;
		while (++index_poly < curr_obj->nb_polygons && (index_point = -1))
		{
			curr_poly = &curr_obj->poly[index_poly];
			while (++index_point < curr_poly->nb_points)
				curr_poly->points[index_point] =
					fct(curr_poly->points[index_point], vsin, vcos);
			curr_poly->vn = fct(curr_poly->vn, vsin, vcos);
		}
	}
}

void				doom_rotate(t_param *p,
	t_vec (*fct)(t_vec vec, float vsin, float vcos), float vsin, float vcos)
{
	int				index_room;
	unsigned int	index_poly;
	unsigned int	index_lights;
	t_rooms			*curr_room;

	rotate_actions(p, fct, vsin, vcos);
	index_room = -1;
	while (++index_room < p->nb_rooms)
	{
		curr_room = &p->rooms[index_room];
		index_poly = -1;
		while (++index_poly < curr_room->nb_walls)
			rotate_polygons(&curr_room->walls[index_poly], fct, vsin, vcos);
		rotate_objects(curr_room, fct, vsin, vcos);
		index_lights = -1;
		while (++index_lights < curr_room->nb_lights)
			curr_room->lights[index_lights].pos =
				fct(curr_room->lights[index_lights].pos, vsin, vcos);
	}
	rotate_projectiles(p, fct, vsin, vcos);
	p->player.current_position = fct(p->player.current_position, vsin, vcos);
	p->player.position = fct(p->player.position, vsin, vcos);
}
