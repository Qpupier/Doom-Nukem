/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   act_instant.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 14:58:59 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 15:25:37 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		handle_action_instant_stop(t_param *p, t_actions *action,
	t_actions *actions_list, t_objects *obj)
{
	if ((action->sound == -1 || action->sound >= p->nb_audio)
		|| (is_sound(p, action)))
	{
		action->state |= ACT_ENDED;
		if (obj->action.end_id >= 0)
			actions_list[obj->action.end_id].state |= ACT_ACTIVE;
	}
}

static void		move_everything(t_objects *obj, t_actions *action)
{
	action_move_object(obj, action->pos);
	action_rotate_object(obj, action->rot);
}

int				handle_action_instant(t_param *p, t_actions *action,
	t_actions *actions_list, t_objects *obj)
{
	if ((action->state & ACT_ACTIVE) && (action->state & ACT_INSTANT)
		&& !(action->state & ACT_ENDED))
	{
		action->pos = translate_obj_axis(obj->axis, action->pos);
		action->rot_curr = action->rot;
		action->pos_curr = action->pos;
		if (is_sound(p, action))
		{
			handle_action_sound(p, action);
			move_everything(obj, action);
		}
		if (action->sound == -1 || action->sound >= p->nb_audio)
		{
			move_everything(obj, action);
		}
		if ((action->state & ACT_SOUND_PLAYING))
		{
			action->state ^= ACT_SOUND_PLAYING;
			action->state |= ACT_SOUND_STOPPED;
		}
		handle_action_instant_stop(p, action, actions_list, obj);
		return (1);
	}
	return (0);
}
