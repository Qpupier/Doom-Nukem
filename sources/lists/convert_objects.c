/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_objects.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 15:40:50 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 15:57:00 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void	copy_data_actions(t_objects *tab, t_list_objects *lst)
{
	tab->action.action_id = lst->action.action_id;
	tab->action.touch_min_dis = lst->action.touch_min_dis;
	tab->action.touch_id = lst->action.touch_id;
	tab->action.click_id = lst->action.click_id;
	tab->action.end_id = lst->action.end_id;
	tab->action.dis_id = lst->action.dis_id;
	tab->action.on_dis = lst->action.on_dis;
	tab->action.boom_id = lst->action.boom_id;
	tab->action.teleport_type_option = lst->action.teleport_type_option;
	tab->action.teleport_type = lst->action.teleport_type;
	tab->action.teleport_position = lst->action.teleport_position;
	tab->action.lift_data = lst->action.lift_data;
	tab->action.lift_type = lst->action.lift_type;
	tab->action.lift_value = lst->action.lift_value;
	tab->action.lift_state = lst->action.lift_state;
	tab->action.end_type = lst->action.end_type;
	tab->action.end_data = lst->action.end_data;
}

void		convert_object_copy_data(t_objects *tab, t_list_objects *lst)
{
	copy_data_actions(tab, lst);
	tab->position = lst->position;
	tab->rotation = lst->rot;
	tab->scale = lst->scale;
	tab->state = 0;
	tab->boom_curr = 1;
	tab->item_id = lst->item_id;
	tab->axis.x = (t_vec){1, 0, 0};
	tab->axis.y = (t_vec){0, 1, 0};
	tab->axis.z = (t_vec){0, 0, 1};
	if (lst->type == OBJ_PROJECTILE)
		tab->state |= OBJ_PROJECTILE;
}
