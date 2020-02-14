/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   textured.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 15:22:55 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 16:17:58 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static t_vec				getnormal(t_vec n, t_vec d)
{
	if (vec_scale_product(d, n) > 0)
		return (n);
	return (vec_mult_float(n, -1));
}

float						get_lights(t_vec intersect, t_polygon *poly,
	float maxdis)
{
	float					intensity;
	register unsigned int	i;
	t_vec					lpt;
	float					dis;
	float					f;

	i = -1;
	intensity = 0;
	while (++i < poly->room_ptr->nb_lights)
	{
		lpt = vec_sub(intersect, poly->room_ptr->lights[i].pos_tmp);
		dis = vec_norm(lpt);
		lpt = vec_normalize(lpt);
		f = vec_scale_product(lpt, vec_normalize(getnormal(poly->n, poly->o)));
		if (f < 0)
			continue ;
		dis = ((dis * maxdis) - 1) * -1;
		if (dis < 0)
			dis = 0;
		intensity += f * dis * poly->room_ptr->lights[i].intensity;
	}
	if (intensity >= .8)
		intensity = .8;
	return (intensity);
}

unsigned int				display(t_param *p, t_buffer buffer)
{
	t_rgb			colrgb;
	t_rgb			final_color;
	float			intensity;
	float			divide;

	if (!buffer.ptr_poly || (!(buffer.ptr_poly->options & O_PROJECTILE)
		&& !buffer.ptr_room))
		return (0x000000);
	if (buffer.ptr_room && buffer.ptr_room->nb_lights >= 1)
	{
		divide = 1 / 255.0;
		colrgb = hex_to_rgb(buffer.color);
		final_color = (t_rgb){0, 0, 0, 0};
		intensity = get_lights(buffer.pt, buffer.ptr_poly, 1 / 5000.0);
		final_color.r = ((.2 + intensity) * (colrgb.r * divide)) * 255;
		final_color.g = ((.2 + intensity) * (colrgb.g * divide)) * 255;
		final_color.b = ((.2 + intensity) * (colrgb.b * divide)) * 255;
		return (rgb_to_hex(final_color));
	}
	return (color_avg(buffer.color, 0x000000, 0.4));
	(void)p;
}
