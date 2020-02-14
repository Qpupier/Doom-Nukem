/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_event.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 16:03:14 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void	tool_one(t_param *p)
{
	if (in_ui(p) && p->switch_dis == 0)
	{
		if (p->tool == 0)
		{
			select_points(p, &p->p, 7);
			select_walls(p, &p->w, 7);
			select_obj(p, &p->o, 7);
			select_character(p, 7);
			selected_points(p);
			create_room(p);
		}
		if (p->tool == 1)
			if (p->kevent.mouse_1)
			{
				point_create(p);
				p->kevent.mouse_1 = 0;
			}
	}
}

void	tool_two(t_param *p)
{
	if (in_ui(p) && p->switch_dis == 0)
	{
		if (p->tool == 2)
			point_wall(p);
		if (p->tool == 3)
		{
			square(p);
			selected_points(p);
			selector_wall(p);
			create_room(p);
		}
		if (p->tool == 0 && p->pick_tool)
			place_obj(p);
	}
}

void	change_tool(t_param *p)
{
	if (p->kevent.space)
	{
		reset_state(p, p->p, p->w, p->o);
		p->tool = p->tool >= 3 ? 0 : p->tool + 1;
		p->walltool.nb = 0;
		p->kevent.space = 0;
	}
}

void	change_display(t_param *p)
{
	t_room	*room;

	if (p->kevent.e)
	{
		if (p->r && p->switch_dis == 0)
			p->switch_dis = 1;
		else
			p->switch_dis = 0;
		p->kevent.e = 0;
	}
	if (p->switch_dis)
	{
		room = p->r;
		while (room)
		{
			select_walls(p, &room->wall, 7);
			room = room->next;
		}
		trace_rooms(p);
	}
	else
	{
		trace_walls(p, p->w);
		trace_points(p);
	}
}
