/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   iterate.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 11:16:42 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 20:13:52 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void			fill_polygon(t_param *p, t_int max, t_int min,
	t_polygon *poly)
{
	register int	i;
	register int	j;
	int				pos;

	i = min.y - 1;
	while (++i <= max.y)
	{
		j = min.x - 1;
		while (++j <= max.x)
		{
			pos = i * p->engine_settings->width + j;
			prepass_buffer(p->rays[i][j], poly, &p->buffer[pos]);
		}
	}
}

static void			iterate_multithread_polygons(t_param *p, t_polygon *poly,
	unsigned nb_poly, t_zone_mt zone)
{
	unsigned int		index_poly;
	t_polygon			*curr;

	index_poly = -1;
	while (++index_poly < nb_poly)
	{
		curr = &poly[index_poly];
		if (!curr->is_visible || curr->xmin > zone.xmax
			|| curr->xmax <= zone.xmin || curr->xmax == curr->xmin)
			continue ;
		fill_polygon(p, (t_int){curr->xmax >= zone.xmax ?
								zone.xmax : curr->xmax, curr->ymax},
						(t_int){curr->xmin < zone.xmin ?
								zone.xmin : curr->xmin, curr->ymin},
							curr);
	}
}

static void			iterate_multithread_current_room(t_param *p, t_zone_mt zone)
{
	long int		index_object;
	t_rooms			*curr_room;
	t_objects		*curr_obj;

	if (p->player.current_room >= 0)
	{
		curr_room = &p->rooms[p->player.current_room];
		iterate_multithread_polygons(p, curr_room->walls,
				curr_room->nb_walls, zone);
		index_object = -1;
		while (++index_object < curr_room->nb_objects)
		{
			curr_obj = &curr_room->objects[index_object];
			iterate_multithread_polygons(p, curr_obj->poly,
				curr_obj->nb_polygons, zone);
		}
	}
}

static void			iterate_ammo(t_param *p, t_zone_mt zone)
{
	int				i;
	t_polygon		*pro;

	i = -1;
	while (++i < p->nb_projectiles)
	{
		pro = &p->projectiles[i];
		if (!pro->is_visible || pro->xmin > zone.xmax
			|| pro->xmax <= zone.xmin || pro->xmax == pro->xmin)
			continue ;
		fill_polygon(p, (t_int){pro->xmax >= zone.xmax ?
								zone.xmax : pro->xmax, pro->ymax},
						(t_int){pro->xmin < zone.xmin ?
								zone.xmin : pro->xmin, pro->ymin},
							pro);
	}
}

void				iterate_multithread_rooms(t_param *p, t_zone_mt zone)
{
	long int		index_room;
	long int		index_object;
	t_rooms			*curr_room;
	t_objects		*curr_obj;

	iterate_multithread_current_room(p, zone);
	index_room = -1;
	while (++index_room < p->nb_rooms)
	{
		if (index_room == p->player.current_room)
			continue ;
		curr_room = &p->rooms[index_room];
		iterate_multithread_polygons(p, curr_room->walls,
			curr_room->nb_walls, zone);
		index_object = -1;
		while (++index_object < curr_room->nb_objects)
		{
			curr_obj = &curr_room->objects[index_object];
			iterate_multithread_polygons(p, curr_obj->poly,
				curr_obj->nb_polygons, zone);
		}
	}
	iterate_ammo(p, zone);
}
