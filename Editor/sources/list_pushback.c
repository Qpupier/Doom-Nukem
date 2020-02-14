/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_pushback.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/25 14:36:09 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		pushback(t_point **list, t_param *p)
{
	t_point *tmp;
	t_point *new;

	if (!(new = malloc(sizeof(t_point))))
		ft_error("Malloc error");
	new->x = p->kevent.mouse_x;
	new->y = p->kevent.mouse_y;
	new->z = 15;
	new->i = p->i_point;
	new->state = 0;
	new->next = NULL;
	new->lay = p->lay;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		wall_pushback(t_wall **list, t_wall w, t_param *p)
{
	t_wall *tmp;
	t_wall *new;

	if (!(new = malloc(sizeof(t_wall))))
		ft_error("Malloc error");
	new->p_one = w.p_one;
	new->p_two = w.p_two;
	new->p_three = w.p_three;
	new->p_four = w.p_four;
	new->lay = p->lay;
	new->i = w.i;
	new->state = w.state;
	new->co = w.co;
	new->tex = w.tex;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		room_pushback(t_room **list, t_wall *w, t_param *p)
{
	t_room *tmp;
	t_room *new;

	if (!(new = malloc(sizeof(t_room))))
		ft_error("Malloc error");
	new->wall = w;
	new->i = p->i_room;
	new->state = 0;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		obj_pushback(t_obj **list, t_obj *obj)
{
	t_obj *tmp;
	t_obj *new;

	if (!(new = malloc(sizeof(t_obj))))
		ft_error("Malloc error");
	new->obj = obj->obj;
	new->pos = obj->pos;
	new->type = obj->type;
	new->state = 0;
	new->action = 0;
	new->lay = obj->lay;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
