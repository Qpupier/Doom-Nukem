/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   triangulation.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 17:34:54 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 15:16:28 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static int		check_tex_equiv(t_list_polygons *poly)
{
	t_vec	pt0;
	t_vec	pt1;
	t_vec	pt2;
	t_vec	pt3;

	pt0 = poly->points->point;
	pt1 = poly->points->next->point;
	pt2 = poly->points->next->next->point;
	pt3 = poly->points->next->next->next->point;
	return (!vec_equal_precision(pt0, poly->tex[0], 0.001)
			|| !vec_equal_precision(pt1, poly->tex[1], 0.001)
			|| !vec_equal_precision(pt2, poly->tex[2], 0.001)
			|| !vec_equal_precision(pt3, poly->tex[3], 0.001));
}

void			triangulate_map(t_param *p)
{
	t_list_room		*room;
	t_list_polygons	*walls;

	room = p->room_list;
	while (room)
	{
		walls = room->walls;
		while (walls)
		{
			if (!(walls->options & IS_CONVEX) || walls->nb_points != 4
				|| check_tex_equiv(walls))
				triangulate_polygon(&room->walls, walls);
			walls = walls->next;
		}
		room = room->next;
	}
}
