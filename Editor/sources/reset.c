/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   reset.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 16:28:23 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

static void		reset_state_bis(t_obj *obj)
{
	t_obj		*tmpo;

	if (obj)
	{
		tmpo = obj;
		while (tmpo)
		{
			tmpo->state = 0;
			tmpo = tmpo->next;
		}
	}
}

void			reset_state(t_param *p, t_point *point, t_wall *w, t_obj *obj)
{
	t_point		*tmpp;
	t_wall		*tmpw;

	p->character.state = 0;
	if (point)
	{
		tmpp = point;
		while (tmpp)
		{
			tmpp->state = 0;
			tmpp = tmpp->next;
		}
	}
	if (w)
	{
		tmpw = w;
		while (tmpw)
		{
			tmpw->state = 0;
			tmpw = tmpw->next;
		}
	}
	reset_state_bis(obj);
}
