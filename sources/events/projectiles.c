/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   projectiles.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/07 20:17:38 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 15:33:53 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void	rotate_projectile(t_polygon *poly, t_matrix_3_3 rot, t_vec center)
{
	int	index;

	index = -1;
	while (++index < 4)
	{
		poly->points[index] = vec_add(center, matrix_mult_vec(rot, 	\
				vec_sub(poly->points[index], center)));
		poly->tex[index] = vec_add(center, matrix_mult_vec(rot, 	\
				vec_sub(poly->tex[index], center)));
	}
}

void		add_projectile(t_param *p, t_buffer buffer)
{
	t_vec			tmp;
	t_matrix_3_3	rot;

	if (p->nb_textures < 6 												\
			|| (buffer.ptr_poly->obj_ptr 								\
				&& buffer.ptr_poly->obj_ptr->action.boom_id != -1) 		\
			|| buffer.ptr_poly->options & IS_SPRITE 					\
			|| buffer.ptr_poly->fix_n.y < -0.01 						\
			|| buffer.ptr_poly->fix_n.y > 0.01)
		return ;
	tmp = vec_add(buffer.pt, (t_vec){0, p->keys & K_CROUNCH ? 0 : -40, 0});
	tmp = vec_rot_x(tmp, -p->player.rotx_angle);
	translate_polygons(&p->projectiles[p->nb_projectiles], 				\
			vec_mult_float(tmp, -1));
	matrix_rotation(0, real_oriented_angle(real_normalize((t_real){ 	\
			buffer.ptr_poly->fix_n.x, buffer.ptr_poly->fix_n.z}), 		\
			real_normalize((t_real){tmp.x, tmp.z})), 0, rot);
	translate_polygons(&p->projectiles[p->nb_projectiles], 				\
			vec_mult_float(vec_normalize(buffer.ptr_poly->fix_n), 0.1));
	rotate_projectile(&p->projectiles[p->nb_projectiles], rot, tmp);
	p->projectiles[p->nb_projectiles].options ^= O_INVISIBLE;
	p->nb_projectiles++;
}
