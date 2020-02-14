/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   polygon_push.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 14:55:17 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:51:17 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void	init(t_list_polygons *new, t_list_polygons data, int count)
{
	new->points = data.points;
	new->texture = data.texture;
	new->nb_points = count;
	new->vn = data.vn;
	new->color = data.color;
	new->vt = data.vt ? data.vt : NULL;
	new->ka = data.ka;
	new->kd = data.kd;
	new->texture2 = data.texture2;
}

int			polygon_push(t_list_polygons **list, t_list_polygons data)
{
	t_list_polygons	*new_poly;
	int				count;
	int				i;

	i = 0;
	count = tlist_count_points(data.points);
	if (!count || count < 3)
		return (6);
	if (!(new_poly = (t_list_polygons *)malloc(sizeof(t_list_polygons))))
		return (E_ERROR_MALLOC);
	init(new_poly, data, count);
	i = 0;
	while (++i < 4)
		new_poly->tex[i] = data.tex[i];
	new_poly->options = data.options ? data.options : 0;
	make_tex(new_poly);
	new_poly->next = NULL;
	if (*list != NULL)
		new_poly->next = *list;
	*list = new_poly;
	return (E_SUCCESS);
}
