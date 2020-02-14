/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   act_reset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 14:57:34 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 16:26:48 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		handle_action_rewind_compare(t_actions *action, t_vec *pos,
	t_vec *rot)
{
	if (fabsf(action->pos_curr.x) > 0)
		pos->x = action->pos_curr.x > 0 ? -1 : 1;
	if (fabsf(action->pos_curr.y) > 0)
		pos->y = action->pos_curr.y > 0 ? -1 : 1;
	if (fabsf(action->pos_curr.z) > 0)
		pos->z = action->pos_curr.z > 0 ? -1 : 1;
	if (fabsf(action->rot_curr.x) > 0)
		rot->x = action->rot_curr.x > 0 ? -1 : 1;
	if (fabsf(action->rot_curr.y) > 0)
		rot->y = action->rot_curr.y > 0 ? -1 : 1;
	if (fabsf(action->rot_curr.z) > 0)
		rot->z = action->rot_curr.z > 0 ? -1 : 1;
}

static void		handle_action_rewind_stop(t_actions *action, t_vec *pos)
{
	if ((pos->x > 0 && action->pos_curr.x > 0)
		|| (pos->x < 0 && action->pos_curr.x < 0))
		action->pos_curr.x = 0;
	if ((pos->y > 0 && action->pos_curr.y > 0)
		|| (pos->y < 0 && action->pos_curr.y < 0))
		action->pos_curr.y = 0;
	if ((pos->z > 0 && action->pos_curr.z > 0)
		|| (pos->z < 0 && action->pos_curr.z < 0))
		action->pos_curr.z = 0;
}

void			handle_action_rewind(t_actions *action, t_objects *obj)
{
	t_vec	pos;
	t_vec	rot;

	pos = (t_vec){0, 0, 0};
	rot = (t_vec){0, 0, 0};
	if (action->state & ACT_ACTIVE && action->state & ACT_REPEAT
		&& action->state & ACT_ENDED && !(action->state & ACT_INFINITE_ROT))
	{
		handle_action_rewind_compare(action, &pos, &rot);
		pos = translate_obj_axis(obj->axis, pos);
		action_move_object(obj, (t_vec){pos.x, pos.y, pos.z});
		action_rotate_object(obj, (t_vec){rot.x, rot.y, rot.z});
		action->pos_curr = vec_add(action->pos_curr,
			(t_vec){pos.x, pos.y, pos.z});
		action->rot_curr = vec_add(action->rot_curr,
			(t_vec){rot.x, rot.y, rot.z});
		handle_action_rewind_stop(action, &pos);
		if ((!pos.x && !pos.y && !pos.z && !rot.x && !rot.y && !rot.z))
		{
			action->pos_curr = (t_vec){0, 0, 0};
			action->rot_curr = (t_vec){0, 0, 0};
			action->state ^= ACT_ENDED;
		}
	}
}
