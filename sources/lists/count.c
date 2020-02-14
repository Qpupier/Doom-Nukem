/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   count.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 14:05:17 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:52:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int				count_faces(t_list_line *lst)
{
	t_list_line	*tmp;
	int			count;

	count = 0;
	tmp = lst;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int				count_vertices(t_list_points *points)
{
	t_list_points	*tmp;
	int				c;

	c = 0;
	tmp = NULL;
	while (points)
	{
		c++;
		points = points->next;
	}
	return (c);
}
