/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   make.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 11:02:01 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 17:35:22 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static inline int	projection_2d(t_engine_settings *settings, t_polygon *poly)
{
	float		tmp;

	poly->ymax = 0;
	poly->ymin = settings->height - 1;
	poly->xmax = 0;
	poly->xmin = settings->width - 1;
	proj3d_to_2d_array(settings, poly);
	if (poly->xmax < poly->xmin)
	{
		tmp = poly->xmax;
		poly->xmax = poly->xmin;
		poly->xmin = tmp;
	}
	if (poly->ymax < poly->ymin)
	{
		tmp = poly->ymax;
		poly->ymax = poly->ymin;
		poly->ymin = tmp;
	}
	create_delimitation(settings, poly);
	if (poly->xmin >= settings->width - 1 || poly->ymin >= settings->height - 1
								|| poly->xmax <= 0 || poly->ymax <= 0)
		return (0);
	return (1);
}

static inline int	exclude_non_visible(t_objects *obj, t_polygon *poly,
	int count_neg)
{
	if (count_neg == poly->nb_points)
		return (0);
	if (((obj && !(obj->state & DISABLE_CULLING))
		|| (!obj)) && poly->options & IS_BLENDER && poly->options & HAS_VN)
	{
		if (vec_scale_product(poly->tmp_points[0], poly->vn_rot) > 0
		&& vec_scale_product(poly->tmp_points[1], poly->vn_rot) > 0
		&& vec_scale_product(poly->tmp_points[2], poly->vn_rot) > 0)
			return (0);
	}
	return (1);
}

void				make_data(t_param *p, t_polygon *poly, t_objects *obj)
{
	unsigned int			i;
	unsigned int			count_neg;

	poly->is_visible = 0;
	if (poly->options & O_INVISIBLE || ((obj && obj->state & OBJ_DISABLE)))
		return ;
	i = -1;
	count_neg = 0;
	turn_tmp_points(p, poly, &count_neg);
	poly->vn_rot = vec_rotx(poly->vn, p->player.rotx_vsin,
		p->player.rotx_vcos);
	if (!exclude_non_visible(obj, poly, count_neg))
		return ;
	i = -1;
	turn_tmp_tex(p, poly);
	if (!(projection_2d(p->engine_settings, poly)))
		return ;
	if (poly->options & HAS_BEEN_TRIANGULATED || poly->options & IS_BLENDER)
		make_data_obj(poly);
	else
		make_data_std(poly);
	make_maths(poly);
	if (poly->options & IS_SPRITE)
		make_sprite(poly);
}
