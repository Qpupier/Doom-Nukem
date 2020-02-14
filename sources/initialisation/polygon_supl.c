/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   polygon_supl.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:46:49 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 10:09:47 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		poly_scale_rotate_translate(t_objects *obj, t_polygon *poly)
{
	unsigned int	index_pt;

	index_pt = -1;
	while (++index_pt < poly->nb_points)
	{
		poly->points[index_pt] = vec_mult_float(poly->points[index_pt],
			obj->scale);
		poly->points[index_pt] = vec_rot_x(poly->points[index_pt],
			ft_deg_to_rad(obj->rotation.x));
		poly->points[index_pt] = vec_rot_y(poly->points[index_pt],
			ft_deg_to_rad(obj->rotation.y));
		poly->points[index_pt] = vec_rot_z(poly->points[index_pt],
			ft_deg_to_rad(obj->rotation.z));
		poly->points[index_pt] = vec_add(obj->position,
			poly->points[index_pt]);
	}
	poly->vn = vec_rot_x(poly->vn, ft_deg_to_rad(obj->rotation.x));
	poly->vn = vec_rot_y(poly->vn, ft_deg_to_rad(obj->rotation.y));
	poly->vn = vec_rot_z(poly->vn, ft_deg_to_rad(obj->rotation.z));
}

static void		fill_polyonly(t_param *p, t_rooms *curr_room, int *i)
{
	unsigned int	index_object;
	unsigned int	index_poly;
	t_objects		*curr_obj;
	t_polygon		*curr_poly;

	index_poly = -1;
	while (++index_poly < curr_room->nb_walls)
	{
		curr_poly = &curr_room->walls[index_poly];
		p->lst_polygons[(*i)++] = curr_poly;
	}
	index_object = -1;
	while (++index_object < curr_room->nb_objects)
	{
		curr_obj = &curr_room->objects[index_object];
		index_poly = -1;
		while (++index_poly < curr_obj->nb_polygons)
		{
			curr_poly = &curr_obj->poly[index_poly];
			p->lst_polygons[(*i)++] = curr_poly;
			poly_scale_rotate_translate(curr_obj, curr_poly);
		}
	}
}

void			init_polygon_only_array(t_param *p)
{
	int				index_room;
	int				i;

	i = 0;
	if (!(p->lst_polygons = malloc(sizeof(t_polygon *) * p->total_polygons)))
		handle_error(p, E_ERROR_MALLOC);
	index_room = -1;
	while (++index_room < p->nb_rooms)
		fill_polyonly(p, &p->rooms[index_room], &i);
}
