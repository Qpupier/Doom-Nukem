/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wireframe.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 15:18:38 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 14:19:04 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			show_wireframe(t_param *p, t_polygon *poly)
{
	unsigned int		i;
	unsigned int		j;

	i = -1;
	if (!poly->is_visible)
		return ;
	while (++i < poly->proj.nb_tmp)
	{
		j = i + 1 == poly->proj.nb_tmp ? 0 : i + 1;
		trace_line(p->mlx->win2,
		(t_int)
		{
			poly->proj.pt_tmp[i].x,
			poly->proj.pt_tmp[i].y
		},
		(t_int)
		{
			poly->proj.pt_tmp[j].x,
			poly->proj.pt_tmp[j].y
		}, poly->color);
	}
}

static t_int	pr(t_param *p, float x, float y, float z)
{
	t_int	r;

	z = 1 / z;
	r.x = x * z * p->engine_settings->ratio_fov_h
		+ p->engine_settings->half_width;
	r.y = y * z * p->engine_settings->ratio_fov_v
		+ p->engine_settings->half_height;
	return (r);
}

static void		show_bounding_obj_supl(t_param *p, t_oob b)
{
	trace_line(p->mlx->win2, pr(p, b.max.x, b.max.y, b.max.z),
		pr(p, b.min.x, b.max.y, b.max.z), 0xff0000);
	trace_line(p->mlx->win2, pr(p, b.max.x, b.max.y, b.max.z),
		pr(p, b.max.x, b.max.y, b.min.z), 0xff0000);
	trace_line(p->mlx->win2, pr(p, b.min.x, b.min.y, b.min.z),
		pr(p, b.min.x, b.max.y, b.min.z), 0xff0000);
	trace_line(p->mlx->win2, pr(p, b.max.x, b.min.y, b.min.z),
		pr(p, b.max.x, b.max.y, b.min.z), 0xff0000);
	trace_line(p->mlx->win2, pr(p, b.max.x, b.min.y, b.max.z),
		pr(p, b.max.x, b.max.y, b.max.z), 0xff0000);
	trace_line(p->mlx->win2, pr(p, b.min.x, b.min.y, b.max.z),
		pr(p, b.min.x, b.max.y, b.max.z), 0xff0000);
}

void			show_bounding_obj(t_param *p, t_objects *obj)
{
	t_oob	b;
	t_int	c;

	b = obj->boundingbox;
	if (b.min.z < 0 || b.max.z < 0)
		return ;
	trace_line(p->mlx->win2, pr(p, b.min.x, b.min.y, b.min.z),
		pr(p, b.max.x, b.min.y, b.min.z), 0xff0000);
	trace_line(p->mlx->win2, pr(p, b.min.x, b.min.y, b.min.z),
		pr(p, b.min.x, b.min.y, b.max.z), 0xff0000);
	trace_line(p->mlx->win2, pr(p, b.max.x, b.min.y, b.max.z),
		pr(p, b.min.x, b.min.y, b.max.z), 0xff0000);
	trace_line(p->mlx->win2, pr(p, b.max.x, b.min.y, b.max.z),
		pr(p, b.max.x, b.min.y, b.min.z), 0xff0000);
	trace_line(p->mlx->win2, pr(p, b.min.x, b.max.y, b.min.z),
		pr(p, b.min.x, b.max.y, b.max.z), 0xff0000);
	trace_line(p->mlx->win2, pr(p, b.min.x, b.max.y, b.min.z),
		pr(p, b.max.x, b.max.y, b.min.z), 0xff0000);
	show_bounding_obj_supl(p, b);
	c = pr(p, b.center.x, b.center.y, b.center.z);
	umlx_putpixel(p->mlx->win2, c.x, c.y, 0xff0000);
}

void			show_bounding_box(t_param *p, t_polygon *poly)
{
	if (!poly->is_visible)
		return ;
	trace_line(p->mlx->win2, (t_int){poly->xmin, poly->ymin},
		(t_int){poly->xmax, poly->ymin}, poly->color);
	trace_line(p->mlx->win2, (t_int){poly->xmin, poly->ymin},
		(t_int){poly->xmin, poly->ymax}, poly->color);
	trace_line(p->mlx->win2, (t_int){poly->xmax, poly->ymax},
		(t_int){poly->xmin, poly->ymax}, poly->color);
	trace_line(p->mlx->win2, (t_int){poly->xmax, poly->ymax},
		(t_int){poly->xmax, poly->ymin}, poly->color);
}
