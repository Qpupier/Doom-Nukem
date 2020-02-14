/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   layer.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 14:09:52 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		change_layer(t_param *p)
{
	if (p->kevent.add)
	{
		p->lay++;
		p->kevent.add = 0;
		p->walltool.nb = 0;
		reset_state(p, p->p, p->w, p->o);
	}
	else if (p->kevent.sub && p->lay > 0)
	{
		p->lay--;
		p->kevent.sub = 0;
		p->walltool.nb = 0;
		reset_state(p, p->p, p->w, p->o);
	}
}
