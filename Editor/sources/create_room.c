/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   create_room.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 10:05:29 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

static void		assign_room(t_param *p)
{
	t_obj	*tmp;

	if (p->o)
	{
		tmp = p->o;
		while (tmp)
		{
			if (tmp->state == 2)
				tmp->room = p->i_room;
			tmp = tmp->next;
		}
	}
}

static void		create_room_bis(t_param *p, t_wall *wall)
{
	assign_room(p);
	sort_wall(wall);
	room_pushback(&p->r, wall, p);
	p->i_room++;
}

void			create_room(t_param *p)
{
	t_wall		*tmp;
	t_wall		*wall;

	wall = NULL;
	if (p->kevent.mouse_2)
	{
		if (p->w)
		{
			tmp = p->w;
			while (tmp)
			{
				if (tmp->state == 2)
					wall_pushback(&wall, *tmp, p);
				tmp = tmp->next;
			}
			check_connection(p, wall);
			if (wall && room_check_exist(p, wall))
				create_room_bis(p, wall);
			else
				wall_delete_all(p, &wall);
		}
		p->kevent.mouse_2 = 0;
	}
}

static void		wall_fill_bis(t_wall *cp, t_wall *w, t_wall *new1, t_wall *new2)
{
	*new1 = *w;
	*new2 = *w;
	new1->co = 0;
	new2->co = 0;
	new1->tex = 1;
	new2->tex = 1;
	new1->state = -1;
	new2->state = -1;
	new1->p_one.z = cp->p_one.z;
	new1->p_two.z = cp->p_two.z;
	new1->p_three.z = w->p_one.z;
	new1->p_four.z = w->p_two.z;
	new2->p_one.z = cp->p_three.z;
	new2->p_two.z = cp->p_four.z;
	new2->p_three.z = w->p_three.z;
	new2->p_four.z = w->p_four.z;
}

void			wall_fill(t_param *p, t_wall *w, t_wall *wall)
{
	t_wall		new1;
	t_wall		new2;
	t_wall		*cp;
	t_wall		*tmp;

	tmp = wall;
	while (tmp)
	{
		if (tmp->tex == -2)
			cp = tmp;
		tmp = tmp->next;
	}
	wall_fill_bis(cp, w, &new1, &new2);
	if (new1.p_one.z != new1.p_three.z && new1.p_two.z != new1.p_four.z)
	{
		wall_pushback(&wall, new1, p);
		wall_pushback(&wall, new2, p);
	}
}
