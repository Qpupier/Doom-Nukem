/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   inventory.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 15:16:47 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		trace_item(t_param *p, t_vec pt0, t_vec pt1, t_int param)
{
	t_int		a;
	t_int		b;
	int			offset_x;

	offset_x = p->engine_settings->win_width - (param.y * 150);
	a.x = pt0.x + offset_x;
	a.y = pt0.z + 50;
	b.x = pt1.x + offset_x;
	b.y = pt1.z + 50;
	trace_line(p->mlx->render, a, b, 0xffffff);
}

static void		print_item(t_param *p, t_objects *obj, t_vec rot, t_int param)
{
	t_vec				pt0;
	t_vec				pt1;
	t_vec				pt2;
	float				f;

	if ((f = (1 / obj->scale)) - 0.5 >= 0.1)
		f = f - .5;
	pt0 = vec_mult_float(vec_sub(obj->poly[param.x].points[0],
		obj->boundingbox.center), f);
	pt1 = vec_mult_float(vec_sub(obj->poly[param.x].points[1],
		obj->boundingbox.center), f);
	pt2 = vec_mult_float(vec_sub(obj->poly[param.x].points[2],
		obj->boundingbox.center), f);
	pt0 = vec_rot_x(pt0, rot.x);
	pt0 = vec_rot_y(pt0, rot.y);
	pt0 = vec_rot_z(pt0, rot.z);
	pt1 = vec_rot_x(pt1, rot.x);
	pt1 = vec_rot_y(pt1, rot.y);
	pt1 = vec_rot_z(pt1, rot.z);
	pt2 = vec_rot_x(pt2, rot.x);
	pt2 = vec_rot_y(pt2, rot.y);
	pt2 = vec_rot_z(pt2, rot.z);
	trace_item(p, pt0, pt1, param);
	trace_item(p, pt1, pt2, param);
	trace_item(p, pt1, pt0, param);
}

static void		print_inventory_id(t_param *p, t_objects *obj, int o)
{
	unsigned int		i;
	t_int				param;
	static t_vec		rot = (t_vec){0, 0, 0};

	i = 0;
	while (i < obj->nb_polygons)
	{
		param.x = i;
		param.y = o;
		print_item(p, obj, rot, param);
		i++;
	}
	rot.x += .01;
	rot.y += .01;
	rot.z += .01;
}

void			hud_show_inventory(t_param *p)
{
	if (p->player.inventory[3] != -1)
		print_inventory_id(p,
			p->lst_polygons[p->player.inventory[3]]->obj_ptr, 1);
	if (p->player.inventory[2] != -1)
		print_inventory_id(p,
			p->lst_polygons[p->player.inventory[2]]->obj_ptr, 2);
	if (p->player.inventory[1] != -1)
		print_inventory_id(p,
			p->lst_polygons[p->player.inventory[1]]->obj_ptr, 3);
	if (p->player.inventory[0] != -1)
		print_inventory_id(p,
			p->lst_polygons[p->player.inventory[0]]->obj_ptr, 4);
}
