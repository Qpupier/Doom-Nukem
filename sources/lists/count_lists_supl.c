/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   count_lists_supl.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 13:53:25 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:53:17 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

unsigned int	tlist_count_polygon(t_list_polygons *poly)
{
	t_list_polygons	*tmp;
	unsigned int	i;

	i = 0;
	tmp = poly;
	while (tmp)
	{
		if (!(tmp->options & SKIP_CONVERSION))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

unsigned int	tlist_count_points(t_list_points *pt_list)
{
	t_list_points	*tmp;
	unsigned int	i;

	i = 0;
	tmp = pt_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

unsigned int	tlist_count_lights(t_list_room *room)
{
	t_list_lights	*tmp;
	unsigned int	i;

	i = 0;
	tmp = room->lights;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
