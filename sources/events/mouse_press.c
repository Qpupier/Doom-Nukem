/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mouse_press.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 12:11:13 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 15:27:56 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int				inv_add_item(t_param *p, int id_poly)
{
	int		id;

	id = -1;
	if (p->player.inventory[0] == -1)
		id = 0;
	if (p->player.inventory[1] == -1)
		id = 1;
	if (p->player.inventory[2] == -1)
		id = 2;
	if (p->player.inventory[3] == -1)
		id = 3;
	if (id >= 0)
	{
		p->player.inventory[id] = id_poly;
		return (1);
	}
	return (0);
}

void			evt_action_add_inventory(t_param *p, int polyid, t_objects *obj)
{
	if (obj->item_id >= 0)
	{
		if (inv_add_item(p, polyid))
		{
			obj->state |= OBJ_DISABLE;
			if (obj->action.action_id >= 0)
				p->actions[obj->action.action_id].state |= ACT_ENDED;
		}
	}
}

static void		evt_action_obj(t_param *p, t_buffer zbuffer, t_objects *obj)
{
	if (obj->action.teleport_type == 1
		&& zbuffer.dis <= obj->action.teleport_type_option)
		teleport_player(p, obj->action.teleport_position);
	if (obj->action.lift_type == 1
		&& zbuffer.dis <= obj->action.lift_data)
	{
		obj->action.lift_state = 1;
		(!(p->pstate & LIFT)) ? (p->pstate |= LIFT) : 0;
	}
	if (obj->action.end_type == 1
		&& zbuffer.dis <= obj->action.end_data)
		(!(p->pstate & P_ENDED)) ? (p->pstate |= P_ENDED) : 0;
}

int				ev_mousepress(int k, int x, int y, t_param *p)
{
	t_buffer	zbuffer;
	t_objects	*obj;

	hud_menu_event_mouse(p, k, x, y);
	if (p->pstate & M_PAUSE)
		return (1);
	zbuffer = p->buffer[p->engine_settings->zbuffer_center];
	if (!(zbuffer.ptr_poly))
		return (0);
	if (k == 1 && zbuffer.ptr_poly && p->nb_projectiles < AMMO)
	{
		add_projectile(p, zbuffer);
		play_sound(p, p->audio[5], 1, 1);
	}
	if (k == 1 && zbuffer.ptr_poly->obj_ptr)
	{
		obj = zbuffer.ptr_poly->obj_ptr;
		evt_action_add_inventory(p, zbuffer.ptr_poly->index, obj);
		evt_action_obj(p, zbuffer, obj);
		if (obj->action.click_id >= 0
			&& obj->action.touch_min_dis >= zbuffer.dis)
			p->actions[obj->action.click_id].state |= ACT_ACTIVE;
	}
	return (1);
}
