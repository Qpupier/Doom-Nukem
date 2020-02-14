/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   action_obj.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 13:10:50 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void			add_action(t_param *p)
{
	t_obj		*tmp;

	tmp = p->o;
	if (p->kevent.mouse_1 && touch_pixel(p, (t_v){175, HEIGHT - 25}, 25, 25))
	{
		while (tmp)
		{
			if (tmp->state == 2)
			{
				if (tmp->action == 0)
					tmp->action = 1;
				else
					tmp->action = 0;
			}
			tmp = tmp->next;
		}
		p->kevent.mouse_1 = 0;
	}
}
