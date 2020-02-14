/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   trace.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/05 13:33:26 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 13:33:34 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			trace_line(t_mlx_img2 img, t_int v1, t_int v2, uint32_t c)
{
	t_bressen	b;

	b.dx = labs(v2.x - v1.x);
	b.dy = labs(v2.y - v1.y);
	b.sx = (v1.x < v2.x ? 1 : -1);
	b.sy = (v1.y < v2.y ? 1 : -1);
	b.err = (b.dx > b.dy ? b.dx : -b.dy) / 2;
	while (!(v1.x == v2.x && v1.y == v2.y))
	{
		umlx_putpixel(img, v1.x, v1.y, c);
		b.e2 = b.err;
		if (b.e2 > -b.dx)
		{
			b.err -= b.dy;
			v1.x += b.sx;
		}
		if (b.e2 < b.dy)
		{
			b.err += b.dx;
			v1.y += b.sy;
		}
	}
}
