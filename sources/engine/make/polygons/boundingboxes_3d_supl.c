/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   boundingboxes_3d_supl.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 16:34:45 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static inline void	store_oob_center(t_oob *oob)
{
	t_vec	res;

	res = vec_sub(oob->max, oob->min);
	res = vec_mult_float(res, .5);
	res = vec_add(res, oob->min);
	oob->center = res;
}

static inline void	get_max(t_vec in, t_vec *out)
{
	if (in.x > out->x)
		out->x = in.x;
	if (in.y > out->y)
		out->y = in.y;
	if (in.z > out->z)
		out->z = in.z;
}

static inline void	get_min(t_vec in, t_vec *out)
{
	if (in.x < out->x)
		out->x = in.x;
	if (in.y < out->y)
		out->y = in.y;
	if (in.z < out->z)
		out->z = in.z;
}

void				generate_box_poly(t_vec pt, t_oob *boudingbox)
{
	get_max(pt, &boudingbox->max);
	get_min(pt, &boudingbox->min);
	boudingbox->dis = vec_norm(boudingbox->min);
	store_oob_center(boudingbox);
}

void				generate_box_obj(t_oob poly, t_oob *obj)
{
	float			d;

	get_max(poly.max, &obj->max);
	get_min(poly.min, &obj->min);
	obj->dis = vec_norm(obj->min);
	store_oob_center(obj);
	d = vec_norm(obj->center);
	if (d < obj->dis)
		obj->dis = d;
}
