/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_bis.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/27 09:51:38 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		obj_delete(t_obj **obj)
{
	t_obj		*tmp;
	t_obj		*prev;

	tmp = *obj;
	if (*obj)
	{
		if (tmp && tmp->state == 2)
		{
			*obj = tmp->next;
			free(tmp);
			return ;
		}
		while (tmp && tmp->state != 2)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			return ;
		prev->next = tmp->next;
		free(tmp);
	}
}

void		obj_delete_all(t_obj **obj)
{
	t_obj		*current;
	t_obj		*next;

	if (*obj)
	{
		current = *obj;
		while (current)
		{
			next = current->next;
			free(current);
			current = next;
		}
		*obj = NULL;
	}
}

void		delete_events(t_param *p)
{
	if (p->kevent.r)
	{
		point_delete_all(p, &p->p);
		wall_delete_all(p, &p->w);
		room_delete_all(p, &p->r);
		obj_delete_all(&p->o);
		p->kevent.r = 0;
	}
	if (p->kevent.del)
	{
		point_delete(p, &p->p);
		wall_delete(p, &p->w);
		obj_delete(&p->o);
		p->walltool.nb = 0;
		p->kevent.del = 0;
	}
}
