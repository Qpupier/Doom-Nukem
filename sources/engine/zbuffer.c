/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zbuffer.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 19:25:30 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 17:51:47 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static inline float			is_inside_poly(t_vec r, t_polygon *w, 			\
	t_buffer *buffer, t_cplx *new)
{
	float			tmp;
	float			t;
	t_vec			pt;

	tmp = w->plane.a * r.x + w->plane.b * r.y + w->plane.c;
	if (!tmp || (t = -w->plane.d / tmp) <= 0)
		return (-1);
	pt = (t_vec) {r.x * t, r.y * t, t};
	tmp = vec_norm(pt);
	if (buffer->dis < tmp || !(inter_poly(w, pt, new)))
		return (-1);
	buffer->pt = pt;
	return (tmp);
}

unsigned short int			prepass_buffer(t_vec r, t_polygon *w,
	t_buffer *buffer)
{
	float			tmp;
	t_cplx			new;
	uint32_t		color;
	int				tex_pos;

	if (w->options & O_INVISIBLE)
		return (0);
	if ((tmp = is_inside_poly(r, w, buffer, &new)) == -1)
		return (0);
	tex_pos = -1;
	if (w->options & IS_BLENDER)
		handle_texture_objects(w, new, &tex_pos, &color);
	else
		handle_texture_walls(w, new, &tex_pos);
	if (tex_pos >= 0)
		color = w->texture->img[tex_pos];
	if (tex_pos == -1 || ((color >> 24) & 0xFF) == 255)
		return (0);
	buffer->dis = tmp;
	buffer->color = color;
	buffer->ptr_poly = w;
	buffer->ptr_room = w->room_ptr;
	return (1);
}
