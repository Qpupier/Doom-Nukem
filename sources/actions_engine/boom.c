/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   boom.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 15:00:54 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 16:15:22 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

t_vec			get_center(t_polygon *poly)
{
	t_vec	center;

	center.x = (poly->points[0].x + poly->points[1].x + poly->points[2].x) / 3;
	center.y = (poly->points[0].y + poly->points[1].y + poly->points[2].y) / 3;
	center.z = (poly->points[0].z + poly->points[1].z + poly->points[2].z) / 3;
	return (center);
}

static int		set_state(t_param *p, t_objects *obj)
{
	obj->state |= DISABLE_CULLING;
	if (!(obj->state & ACT_IS_BOOMING) && !(obj->state & ACT_BOOMED))
	{
		play_sound(p, p->audio[3], 1, 1);
		p->nb_projectiles++;
		obj->boom_curr = 1;
		obj->state |= ACT_IS_BOOMING;
	}
	if (obj->boom_curr >= 4 && obj->state & ACT_IS_BOOMING)
	{
		obj->state |= ACT_BOOMED;
		obj->state ^= ACT_IS_BOOMING;
		obj->state |= OBJ_DISABLE;
		if (obj->boundingbox.dis <= 1000)
		{
			p->player.life -= 15;
			!(p->pstate & DAMAGES) ? p->pstate |= DAMAGES : 0;
		}
		return (1);
	}
	else
		obj->boom_curr += .5;
	return (0);
}

void			animation_boom(t_param *p, t_objects *obj)
{
	unsigned int		index_poly;
	t_vec				center;
	t_vec				vcc;
	t_polygon			*poly;

	index_poly = -1;
	center = obj->boundingbox.center;
	if (set_state(p, obj))
		return ;
	while (++index_poly < obj->nb_polygons)
	{
		poly = &obj->poly[index_poly];
		vcc = vec_mult_float(vec_sub(center, get_center(poly)), .5);
		poly->points[0] = vec_sub(poly->points[0], vcc);
		poly->points[1] = vec_sub(poly->points[1], vcc);
		poly->points[2] = vec_sub(poly->points[2], vcc);
	}
}
