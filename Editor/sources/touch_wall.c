/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   touch_wall.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/02 11:57:57 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	init_all_touch_wall(t_v *one, t_v *two, t_bressen *b, t_wall *tmp)
{
	one->x = tmp->p_one.x;
	two->x = tmp->p_two.x;
	one->y = tmp->p_one.y;
	two->y = tmp->p_two.y;
	b->dx = abs(two->x - one->x);
	b->dy = abs(two->y - one->y);
	b->sx = (one->x < two->x ? 1 : -1);
	b->sy = (one->y < two->y ? 1 : -1);
	b->err = (b->dx > b->dy ? b->dx : -b->dy) / 2;
}

static void	all_touch_wall_calc_one(t_v *one, t_bressen *b)
{
	b->err -= b->dy;
	one->x += b->sx;
}

static void	all_touch_wall_calc_two(t_v *one, t_bressen *b)
{
	b->err += b->dx;
	one->y += b->sy;
}

int			all_touch_wall(t_param *p, int size)
{
	t_wall		*tmp;
	t_bressen	b;
	t_v			one;
	t_v			two;

	tmp = p->w;
	while (tmp)
	{
		init_all_touch_wall(&one, &two, &b, tmp);
		while (!(one.x == two.x && one.y == two.y) && tmp->lay == p->lay)
		{
			if (touch_pixel(p, (t_v){one.x, one.y}, size, size))
				return (1);
			b.e2 = b.err;
			if (b.e2 > -b.dx)
				all_touch_wall_calc_one(&one, &b);
			if (b.e2 < b.dy)
				all_touch_wall_calc_two(&one, &b);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			touch_wall(t_param *p, t_wall w, int size)
{
	t_bressen	b;

	b.dx = abs(w.p_two.x - w.p_one.x);
	b.dy = abs(w.p_two.y - w.p_one.y);
	b.sx = (w.p_one.x < w.p_two.x ? 1 : -1);
	b.sy = (w.p_one.y < w.p_two.y ? 1 : -1);
	b.err = (b.dx > b.dy ? b.dx : -b.dy) / 2;
	while (!(w.p_one.x == w.p_two.x && w.p_one.y == w.p_two.y))
	{
		if (touch_pixel(p, (t_v){w.p_one.x, w.p_one.y}, size, size))
			return (1);
		b.e2 = b.err;
		if (b.e2 > -b.dx)
		{
			b.err -= b.dy;
			w.p_one.x += b.sx;
		}
		if (b.e2 < b.dy)
		{
			b.err += b.dx;
			w.p_one.y += b.sy;
		}
	}
	return (0);
}
