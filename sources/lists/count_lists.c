/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   count_lists.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 13:52:05 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 10:08:33 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

unsigned int	tlist_count_rooms(t_param *p)
{
	t_list_room		*tmp;
	int				i;

	i = 0;
	tmp = p->room_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

unsigned int	tlist_count_walls(t_list_room *room)
{
	t_list_polygons	*tmp;
	unsigned int	i;

	i = 0;
	tmp = room->walls;
	while (tmp)
	{
		if (!(tmp->options & SKIP_CONVERSION))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

unsigned int	tlist_count_objects(t_list_room *room)
{
	t_list_objects	*tmp;
	unsigned int	i;

	i = 0;
	tmp = room->objects;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
