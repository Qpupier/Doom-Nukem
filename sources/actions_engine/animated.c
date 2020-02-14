/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   animated.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 14:58:12 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 15:26:36 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		handle_aninmation(t_actions *action, t_objects *obj,
	t_vec rot, t_vec pos)
{
	action->rot_curr = vec_add(action->rot_curr, (t_vec){rot.x, rot.y, rot.z});
	action->pos_curr = vec_add(action->pos_curr, (t_vec){pos.x, pos.y, pos.z});
	pos = translate_obj_axis(obj->axis, pos);
	action_move_object(obj, (t_vec){pos.x, pos.y, pos.z});
	action_rotate_object(obj, (t_vec){rot.x, rot.y, rot.z});
}

void			handle_action_animated(t_actions *action, t_objects *obj)
{
	t_vec	pos;
	t_vec	rot;

	pos = (t_vec){0, 0, 0};
	rot = (t_vec){0, 0, 0};
	if (!(action->state & ACT_ACTIVE && !(action->state & ACT_ENDED)
		&& !(action->state & ACT_INFINITE_ROT)))
		return ;
	if (fabsf(action->pos.x) > fabsf(action->pos_curr.x))
		pos.x = action->pos.x < 0 ? -.5 : .5;
	if (fabsf(action->pos.y) > fabsf(action->pos_curr.y))
		pos.y = action->pos.y < 0 ? -.5 : .5;
	if (fabsf(action->pos.z) > fabsf(action->pos_curr.z))
		pos.z = action->pos.z < 0 ? -.5 : .5;
	if (fabsf(action->rot.x) > fabsf(action->rot_curr.x))
		rot.x = action->rot.x < 0 ? -1 : 1;
	if (fabsf(action->rot.y) > fabsf(action->rot_curr.y))
		rot.y = action->rot.y < 0 ? -1 : 1;
	if (fabsf(action->rot.z) > fabsf(action->rot_curr.z))
		rot.z = action->rot.z < 0 ? -1 : 1;
	handle_aninmation(action, obj, rot, pos);
	vec_null(pos) && vec_null(rot) ? action->state |= ACT_ENDED : 0;
}

void			handle_action_infinite_rotation(t_actions *action,
	t_objects *obj)
{
	t_vec	rot;

	rot = (t_vec){0, 0, 0};
	if (action->state & ACT_ACTIVE && action->state & ACT_INFINITE_ROT
		&& !(action->state & ACT_ENDED))
	{
		if (fabsf(action->rot.x) && fabsf(action->rot_curr.x) < 360)
			rot.x = action->rot.x < 0 ? -action->rot.x : action->rot.x;
		if (fabsf(action->rot.y) && fabsf(action->rot_curr.y) < 360)
			rot.y = action->rot.y < 0 ? -action->rot.x : action->rot.y;
		if (fabsf(action->rot.z) && fabsf(action->rot_curr.z) < 360)
			rot.z = action->rot.z < 0 ? -action->rot.x : action->rot.z;
		if (action->rot_curr.x >= 359)
			action->rot_curr.x = 0;
		if (action->rot_curr.y >= 359)
			action->rot_curr.y = 0;
		if (action->rot_curr.z >= 359)
			action->rot_curr.z = 0;
		action_rotate_object(obj, (t_vec){rot.x, rot.y, rot.z});
		action->rot_curr = vec_add(action->rot_curr,
			(t_vec){rot.x, rot.y, rot.z});
	}
}
