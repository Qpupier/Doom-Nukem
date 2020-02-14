/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   checks.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 14:56:01 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 15:30:31 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			handle_action_sound(t_param *p, t_actions *action)
{
	if (action->sound >= 0 && action->sound < p->nb_audio)
	{
		play_sound(p, p->audio[action->sound], 1, 1);
		action->state |= ACT_SOUND_PLAYING;
	}
}

int				is_sound(t_param *p, t_actions *action)
{
	return (action->sound >= 0 && action->sound < p->nb_audio);
}

void			action_set_wait(t_actions *action)
{
	struct timeval		tstart;
	long long int		time;

	if (action->time_to_wait <= 0)
		return ;
	gettimeofday(&tstart, NULL);
	time = tstart.tv_sec * 1000LL + tstart.tv_usec / 1000;
	action->time_on_start = time;
}

int				action_check_wait(t_actions *action)
{
	struct timeval		tstart;
	long long int		time;

	if (action->time_to_wait <= 0)
		return (-1);
	gettimeofday(&tstart, NULL);
	time = tstart.tv_sec * 1000LL + tstart.tv_usec / 1000;
	if (time - action->time_on_start >= action->time_to_wait)
		return (1);
	return (0);
}

int				action_check_item(t_param *p, int item)
{
	int		id;

	id = -1;
	if ((id == -1) && p->player.inventory[0] >= 0
		&& p->lst_polygons[(p->player.inventory[0])]->obj_ptr->item_id == item)
		id = 0;
	if ((id == -1) && p->player.inventory[1] >= 0
		&& p->lst_polygons[(p->player.inventory[1])]->obj_ptr->item_id == item)
		id = 1;
	if ((id == -1) && p->player.inventory[2] >= 0
		&& p->lst_polygons[(p->player.inventory[2])]->obj_ptr->item_id == item)
		id = 2;
	if ((id == -1) && p->player.inventory[3] >= 0
		&& p->lst_polygons[(p->player.inventory[3])]->obj_ptr->item_id == item)
		id = 3;
	if (id >= 0)
	{
		p->player.inventory[id] = -1;
		return (1);
	}
	return (0);
}
