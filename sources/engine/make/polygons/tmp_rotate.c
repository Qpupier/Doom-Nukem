/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tmp_rotate.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 14:37:55 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 21:53:25 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void				translate_points(t_vec *pt, int nb, t_vec move)
{
	pt[0] = vec_sub(pt[0], move);
	pt[1] = vec_sub(pt[1], move);
	pt[2] = vec_sub(pt[2], move);
	if (nb == 4)
		pt[3] = vec_sub(pt[3], move);
}

void				move_lights(t_param *p, t_rooms *room)
{
	unsigned int	index_light;

	index_light = -1;
	while (++index_light < room->nb_lights)
	{
		room->lights[index_light].pos_tmp =
		vec_rotx(room->lights[index_light].pos, p->player.rotx_vsin,
			p->player.rotx_vcos);
		room->lights[index_light].pos_tmp =
				vec_sub(room->lights[index_light].pos_tmp, (t_vec){0, -40, 0});
		if (p->keys & K_CROUNCH)
			room->lights[index_light].pos_tmp =
				vec_sub(room->lights[index_light].pos_tmp, (t_vec){0, 40, 0});
	}
}

void				turn_tmp_points(t_param *p, t_polygon *poly,
	unsigned int *neg)
{
	float		sin;
	float		cos;

	sin = p->player.rotx_vsin;
	cos = p->player.rotx_vcos;
	poly->tmp_points[0] = vec_rotx(poly->points[0], sin, cos);
	if (poly->tmp_points[0].z < 0)
		(*neg)++;
	poly->tmp_points[1] = vec_rotx(poly->points[1], sin, cos);
	if (poly->tmp_points[1].z < 0)
		(*neg)++;
	poly->tmp_points[2] = vec_rotx(poly->points[2], sin, cos);
	if (poly->tmp_points[2].z < 0)
		(*neg)++;
	if (poly->nb_points == 4)
	{
		poly->tmp_points[3] = vec_rotx(poly->points[3], sin, cos);
		if (poly->tmp_points[3].z < 0)
			(*neg)++;
	}
	translate_points(poly->tmp_points, poly->nb_points, (t_vec){0, -40, 0});
	if (p->keys & K_CROUNCH)
		translate_points(poly->tmp_points, poly->nb_points, (t_vec){0, 40, 0});
}

void				turn_tmp_tex(t_param *p, t_polygon *poly)
{
	float		sin;
	float		cos;

	if (poly->options & IS_BLENDER || poly->options & HAS_BEEN_TRIANGULATED)
		return ;
	sin = p->player.rotx_vsin;
	cos = p->player.rotx_vcos;
	poly->tmp_tex[0] = vec_rotx(poly->tex[0], sin, cos);
	poly->tmp_tex[1] = vec_rotx(poly->tex[1], sin, cos);
	poly->tmp_tex[2] = vec_rotx(poly->tex[2], sin, cos);
	poly->tmp_tex[3] = vec_rotx(poly->tex[3], sin, cos);
	translate_points(poly->tmp_tex, poly->nb_points, (t_vec){0, -40, 0});
	if (p->keys & K_CROUNCH)
		translate_points(poly->tmp_tex, poly->nb_points, (t_vec){0, 40, 0});
}
