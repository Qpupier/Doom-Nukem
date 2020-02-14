/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 15:46:00 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 23:53:49 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	make_fixed(t_polygon *poly)
{
	if (poly->options & HAS_BEEN_TRIANGULATED || poly->options & IS_BLENDER)
	{
		poly->fix_o = poly->points[0];
		poly->fix_u = vec_sub(poly->points[1], poly->fix_o);
		poly->fix_v = vec_sub(poly->points[2], poly->fix_o);
	}
	else
	{
		poly->fix_o = poly->tex[0];
		poly->fix_u = vec_sub(poly->tex[1], poly->fix_o);
		poly->fix_v = vec_sub(poly->tex[3], poly->fix_o);
	}
	poly->fix_n = (vec_cross_product(poly->fix_u, poly->fix_v));
	poly->fix_plane.a = poly->fix_n.x;
	poly->fix_plane.b = poly->fix_n.y;
	poly->fix_plane.c = poly->fix_n.z;
	poly->fix_plane.d = -poly->fix_plane.a * poly->fix_o.x 	\
			- poly->fix_plane.b * poly->fix_o.y 			\
			- poly->fix_plane.c * poly->fix_o.z;
	poly->fix_scale_u = vec_scale_product(poly->fix_u, poly->fix_u);
	poly->fix_scale_v = vec_scale_product(poly->fix_v, poly->fix_v);
	poly->fix_scale_uv = vec_scale_product(poly->fix_u, poly->fix_v);
	poly->dist_y = (poly->fix_n.y ?
		-poly->fix_plane.d / poly->fix_plane.b : -1);
}

void	make_maths(t_polygon *poly)
{
	poly->n = vec_check(vec_cross_product(poly->u, poly->v));
	poly->plane.a = poly->n.x;
	poly->plane.b = poly->n.y;
	poly->plane.c = poly->n.z;
	poly->plane.d = -poly->plane.a * poly->o.x 	\
			- poly->plane.b * poly->o.y - poly->plane.c * poly->o.z;
	poly->scale_u = vec_scale_product(poly->u, poly->u);
	poly->scale_v = vec_scale_product(poly->v, poly->v);
	poly->scale_uv = vec_scale_product(poly->u, poly->v);
}

void	make_data_obj(t_polygon *poly)
{
	poly->o = poly->tmp_points[0];
	poly->u = vec_check(vec_sub(poly->tmp_points[1], poly->o));
	poly->v = vec_check(vec_sub(poly->tmp_points[2], poly->o));
}

void	make_data_std(t_polygon *poly)
{
	poly->o = poly->tmp_tex[0];
	poly->u = vec_check(vec_sub(poly->tmp_tex[1], poly->tmp_tex[0]));
	poly->v = vec_check(vec_sub(poly->tmp_tex[3], poly->tmp_tex[0]));
	poly->ratio = vec_norm(poly->u) / vec_norm(poly->v);
}

void	make_sprite(t_polygon *poly)
{
	t_vec			new;
	t_matrix_3_3	rot;
	int				index;

	new = vec_sub((t_vec){0, 0, 0}, poly->boudingbox.center);
	matrix_rotation(0, -real_oriented_angle(real_normalize((t_real) 	\
			{poly->fix_n.x, poly->fix_n.z}), 							\
			real_normalize((t_real){new.x, new.z})), 0, rot);
	index = -1;
	while (++index < poly->nb_points)
	{
		poly->points[index] = vec_add(poly->boudingbox.center, 				\
				matrix_mult_vec(rot, 										\
				vec_sub(poly->points[index], poly->boudingbox.center)));
		poly->tex[index] = vec_add(poly->boudingbox.center, 				\
				matrix_mult_vec(rot, 										\
				vec_sub(poly->tex[index], poly->boudingbox.center)));
	}
}
