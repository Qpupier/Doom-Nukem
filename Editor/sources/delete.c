/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 08:10:40 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		point_delete_all(t_param *p, t_point **point)
{
	t_point		*current;
	t_point		*next;

	if (*point)
	{
		current = *point;
		while (current)
		{
			p->kevent.r = 1;
			next = current->next;
			free(current);
			current = next;
			p->i_point = 0;
		}
		*point = NULL;
	}
}

void		point_delete(t_param *p, t_point **point)
{
	t_point		*tmp;
	t_point		*prev;

	tmp = *point;
	if (*point)
	{
		if (tmp && tmp->state == 2)
		{
			*point = tmp->next;
			free(tmp);
			p->i_point--;
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

void		wall_delete_all(t_param *p, t_wall **wall)
{
	t_wall		*current;
	t_wall		*next;

	if (*wall)
	{
		current = *wall;
		while (current)
		{
			next = current->next;
			free(current);
			current = next;
			p->i_wall = 0;
			p->walltool.nb = 0;
		}
		*wall = NULL;
	}
}

void		wall_delete(t_param *p, t_wall **wall)
{
	t_wall		*tmp;
	t_wall		*prev;

	tmp = *wall;
	if (*wall)
	{
		if (tmp && tmp->state == 2)
		{
			*wall = tmp->next;
			p->i_wall--;
			p->walltool.nb = 0;
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

void		room_delete_all(t_param *p, t_room **r)
{
	t_room		*current;
	t_room		*next;

	if (*r)
	{
		current = *r;
		while (current)
		{
			next = current->next;
			wall_delete_all(p, &current->wall);
			free(current);
			current = next;
			p->i_room = 0;
			p->walltool.nb = 0;
		}
		*r = NULL;
	}
}
