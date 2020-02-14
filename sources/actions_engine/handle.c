/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 14:50:48 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 16:06:09 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			handle_action(t_param *p, t_actions *actions_list,
	t_actions *action, t_objects *obj)
{
	if (obj->action.boom_id >= 0 && p->nb_projectiles >= AMMO)
		return ;
	if ((action->state & ACT_ACTIVE) && action->item_id >= 0)
		if (!action_check_item(p, action->item_id))
		{
			action->state ^= ACT_ACTIVE;
			return ;
		}
	if (handle_action_instant(p, action, actions_list, obj))
		return ;
	handle_action_animated(action, obj);
	handle_action_rewind(action, obj);
	if (action->state & ACT_ENDED)
		if (obj->action.end_id >= 0)
		{
			actions_list[obj->action.end_id].state |= ACT_ACTIVE;
		}
	handle_action_infinite_rotation(action, obj);
	if (action->state & ACT_ACTIVE && !(action->state & ACT_SOUND_PLAYING)
		&& !(action->state & ACT_ENDED))
		handle_action_sound(p, action);
}

static void		dispatch(t_param *p, t_objects *obj)
{
	int				action_id;
	int				boom_id;

	action_id = obj->action.action_id;
	boom_id = obj->action.boom_id;
	if (action_id >= 0 && action_id <= (int)p->nb_actions)
		handle_action(p, p->actions, &p->actions[action_id], obj);
	if (p->nb_projectiles < AMMO && boom_id >= 0
		&& p->actions[boom_id].state & ACT_ENDED && !(obj->state & ACT_BOOMED))
		animation_boom(p, obj);
}

void			apply_action(t_param *p)
{
	int				index_room;
	unsigned int	index_object;
	t_rooms			*curr_room;

	index_room = -1;
	while (++index_room < p->nb_rooms)
	{
		curr_room = &p->rooms[index_room];
		index_object = -1;
		while (++index_object < curr_room->nb_objects)
		{
			dispatch(p, &curr_room->objects[index_object]);
		}
	}
}
