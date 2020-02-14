/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tex_mapping.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/07 10:07:32 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 13:08:14 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static inline t_vec			get_textures_coordinates(t_polygon *p, t_cplx new)
{
	t_vec	coords;
	t_vec	mu;
	t_vec	mv;

	mu = vec_mult_float(p->tex_u, new.rl);
	mv = vec_mult_float(p->tex_v, new.im);
	coords = vec_add(p->obj_tex[0], vec_add(mu, mv));
	return (coords);
}

static inline int			get_textures_pos(t_polygon *p, t_vec tex_coord)
{
	int				y;
	long int		tex_pos;

	y = p->texture->height - tex_coord.y;
	if (tex_coord.x >= p->texture->width || tex_coord.x < 0
		|| y > p->texture->height || y < 0)
		return (-1);
	tex_pos = y * p->texture->width + tex_coord.x;
	if (tex_pos > p->texture->width * p->texture->height)
		return (-1);
	return (tex_pos);
}

void						handle_texture_objects(t_polygon *poly, t_cplx new,
	int *tex_pos, unsigned int *color)
{
	t_vec			tex_coord;

	if (poly->options & HAS_TEXTURE)
	{
		tex_coord = get_textures_coordinates(poly, new);
		*tex_pos = get_textures_pos(poly, tex_coord);
	}
	else
	{
		*color = rgb_to_hex((t_rgb)
		{
			poly->kd.z * 255,
			poly->kd.x * 255,
			poly->kd.y * 255,
			0
		});
		*tex_pos = -2;
	}
}

void						handle_texture_walls(t_polygon *poly, t_cplx new,
	int *tex_pos)
{
	t_vec			tex_coord;

	if (poly->options & HAS_BEEN_TRIANGULATED)
	{
		tex_coord = get_textures_coordinates(poly, new);
		*tex_pos = get_textures_pos(poly, tex_coord);
	}
	else
	{
		if (poly->options & IS_SPRITE)
			*tex_pos = (int)(new.rl * poly->texture->height)
			* poly->texture->width + new.im * poly->texture->width;
		else
			*tex_pos = (int)(new.im * poly->texture->height)
				* poly->texture->width
				+ ft_mod((new.rl * poly->texture->width * poly->ratio),
					poly->texture->width);
		if (*tex_pos < 0
			|| *tex_pos > poly->texture->width * poly->texture->height)
			*tex_pos = -1;
	}
}
