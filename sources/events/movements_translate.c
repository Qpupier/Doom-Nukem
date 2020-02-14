/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   movements_translate.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/01 12:57:59 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 17:29:55 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		translate_polygons(t_polygon *poly, t_vec move)
{
	register unsigned int	index_point;

	index_point = -1;
	while (++index_point < poly->nb_points)
		poly->points[index_point] = vec_sub(poly->points[index_point], move);
	index_point = -1;
	if (poly->options & HAS_BEEN_TRIANGULATED || poly->options & IS_BLENDER)
		return ;
	while (++index_point < 4)
		poly->tex[index_point] = vec_sub(poly->tex[index_point], move);
}

void		translate_objects(t_rooms *room, t_vec move)
{
	register unsigned int	io;
	register unsigned int	ip;
	t_objects				*curr_obj;

	io = -1;
	while (++io < room->nb_objects)
	{
		curr_obj = &room->objects[io];
		if (curr_obj->state & OBJ_DISABLE)
			continue ;
		ip = -1;
		while (++ip < curr_obj->nb_polygons)
			translate_polygons(&curr_obj->poly[ip], move);
	}
}

void		doom_move(t_param *p, t_vec move)
{
	register int				ir;
	register unsigned int		ip;
	t_rooms						*curr_room;

	move = vec_mult_float(move, 1.001);
	ir = -1;
	while (++ir < p->nb_rooms)
	{
		curr_room = &p->rooms[ir];
		ip = -1;
		while (++ip < curr_room->nb_walls)
			translate_polygons(&curr_room->walls[ip], move);
		translate_objects(curr_room, move);
		ip = -1;
		while (++ip < curr_room->nb_lights)
			curr_room->lights[ip].pos =
				vec_sub(curr_room->lights[ip].pos, move);
	}
	ir = -1;
	while (++ir < p->nb_projectiles)
		translate_polygons(&p->projectiles[ir], move);
	p->player.current_position = vec_sub(p->player.current_position, move);
}
