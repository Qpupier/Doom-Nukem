/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   circle.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/09 14:37:10 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	hline(t_param *p, t_v v, int w, uint32_t col)
{
	int		i;

	i = -1;
	while (++i < w)
		umlx_putpixel(p->mlx->render, v.x + i, v.y, col);
}

void		fillcircle(t_param *p, t_v v, int radius, uint32_t col)
{
	t_c		c;

	c.xoff = 0;
	c.yoff = radius;
	c.balance = -radius;
	while (c.xoff <= c.yoff)
	{
		c.p0 = v.x - c.xoff;
		c.p1 = v.x - c.yoff;
		c.w0 = c.xoff + c.xoff;
		c.w1 = c.yoff + c.yoff;
		hline(p, (t_v){c.p0, v.y + c.yoff}, c.w0, col);
		hline(p, (t_v){c.p0, v.y - c.yoff}, c.w0, col);
		hline(p, (t_v){c.p1, v.y + c.xoff}, c.w1, col);
		hline(p, (t_v){c.p1, v.y - c.xoff}, c.w1, col);
		if ((c.balance += c.xoff + c.xoff) >= 0)
		{
			c.balance -= (c.yoff) + c.yoff;
			--c.yoff;
		}
		c.xoff++;
	}
}
