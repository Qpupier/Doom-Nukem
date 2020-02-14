/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_rotate.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 14:52:03 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 21:16:39 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

t_vec			translate_obj_axis(t_axis axis, t_vec pos)
{
	t_vec	x;
	t_vec	y;
	t_vec	z;
	t_vec	r;

	x = vec_mult_float(axis.x, pos.x);
	y = vec_mult_float(axis.y, pos.y);
	z = vec_mult_float(axis.z, pos.z);
	r = vec_add(vec_add(x, y), z);
	return (r);
}

void			action_move_object(t_objects *obj, t_vec move)
{
	unsigned int	id_poly;
	unsigned int	id_points;

	id_poly = -1;
	while (++id_poly < obj->nb_polygons)
	{
		id_points = -1;
		while (++id_points < obj->poly[id_poly].nb_points)
			obj->poly[id_poly].points[id_points] =
				vec_sub(obj->poly[id_poly].points[id_points], move);
	}
}

void			action_rotate_object(t_objects *obj, t_vec rot)
{
	unsigned int			id_poly;
	unsigned int			id_points;
	t_rotation_axes			rotation;

	id_poly = -1;
	rotation = axes_rotation_init(obj->axis, rot);
	while (++id_poly < obj->nb_polygons)
	{
		id_points = -1;
		while (++id_points < obj->poly[id_poly].nb_points)
			axes_apply_rot_origin(obj->boundingbox.center,
				&obj->poly[id_poly].points[id_points], rotation);
		axes_apply_rot(&obj->poly[id_poly].vn, rotation);
	}
}
