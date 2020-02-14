/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   collisions.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 14:02:30 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 16:56:04 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static int			collision_intersection_slide(t_param *p, t_vec *vec,
	int feets)
{
	register int			index_room;
	register unsigned int	index_poly;
	register unsigned int	index_obj;
	t_rooms					*room;

	index_room = -1;
	while (++index_room < p->nb_rooms && (index_poly = -1))
	{
		room = &p->rooms[index_room];
		while (++index_poly < room->nb_walls)
			if (collision_intersection(p, vec, &room->walls[index_poly], feets))
				return (1);
		index_obj = -1;
		while (++index_obj < room->nb_objects && (index_poly = -1))
		{
			if (room->objects[index_obj].state & OBJ_DISABLE)
				continue ;
			while (++index_poly < room->objects[index_obj].nb_polygons)
				if (collision_intersection(p, vec,
					&room->objects[index_obj].poly[index_poly], feets))
					return (1);
		}
	}
	return (0);
}

int					collision_intersection(t_param *p, t_vec *vec,
	t_polygon *poly, int feets)
{
	float		dist;
	t_vec		result;
	int			inter;
	int			feet;
	t_vec		o;

	o = (t_vec){0, 0, 0};
	proj_point_poly(*vec, poly, &dist);
	inter = dist <= CIRCLE_DETECTION
			|| inter_seg_poly((t_seg){o, *vec}, poly, &result);
	o.y = CIRCLE_DETECTION;
	result = proj_point_poly(vec_add(*vec, o), poly, &dist);
	feet = dist <= FEETS;
	if (feets && !inter && feet)
	{
		vec->y -= FEETS - dist;
		return (collision_intersection_slide(p, vec, 0));
	}
	return (inter || feet);
}

inline int			collision_conditions(t_param *p, t_polygon *poly,
	t_vec *vec)
{
	t_plane	plane;
	float	dist;

	if (poly->options & O_INVISIBLE)
		return (0);
	plane = poly->fix_plane;
	plane.d = 0;
	if (collision_intersection(p, vec, poly, 1))
	{
		*vec = proj_point_plane(*vec, plane, &dist);
		if (collision_intersection_slide(p, vec, 1))
			return (1);
	}
	return (0);
}

static inline void	prepare_data(t_param *p)
{
	register unsigned int	index_poly;

	index_poly = -1;
	while (++index_poly < p->total_polygons)
		make_fixed(p->lst_polygons[index_poly]);
}

int					collision(t_param *p, t_vec *vec)
{
	register int			index_room;
	register unsigned int	index_poly;
	register unsigned int	index_obj;
	t_rooms					*room;

	prepare_data(p);
	index_room = -1;
	while (++index_room < p->nb_rooms && (index_poly = -1))
	{
		room = &p->rooms[index_room];
		while (++index_poly < room->nb_walls)
			if (collision_conditions(p, &room->walls[index_poly], vec))
				return (1);
		index_obj = -1;
		while (++index_obj < room->nb_objects && (index_poly = -1))
		{
			if (room->objects[index_obj].state & OBJ_DISABLE)
				continue ;
			while (++index_poly < room->objects[index_obj].nb_polygons)
				if (collision_conditions(p,
					&room->objects[index_obj].poly[index_poly], vec))
					return (1);
		}
	}
	return (0);
}
