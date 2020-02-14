/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gen_walls.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/03 14:37:17 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 13:13:07 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int			generate_walls(t_param *p, t_list_polygons **lst_walls, char *line)
{
	char			**data;
	int				j;
	t_list_points	*lst_points;
	t_list_polygons	poly;

	if (!(data = ft_strsplit(line, ' ')))
		return (E_SPLIT_ERROR);
	lst_points = NULL;
	j = 0;
	while (j < 11)
	{
		if (!str_isnumber(data[j]) || !str_isnumber(data[j + 1])
			|| !str_isnumber(data[j + 2]))
			return (E_ERROR_PARSE_POINTS);
		if (points_pushback(&lst_points, (t_vec){ft_atoi(data[j]),
				ft_atoi(data[j + 1]), ft_atoi(data[j + 2])}) == E_ERROR_MALLOC)
			return (E_ERROR_MALLOC);
		j += 3;
	}
	poly.points = lst_points;
	poly.texture = p->textures[ft_atoi(data[12])];
	poly.options = 0;
	get_wall_options(line, &poly);
	ft_splitdel(&data);
	return (polygon_push(lst_walls, poly));
}

static int	gen_ceil(t_param *p, t_list_polygons **lst_walls,
	t_list_points *pt, int texid)
{
	t_list_polygons		data;

	data.points = pt;
	data.texture = p->textures[texid];
	data.options = 0;
	data.options |= O_CEIL;
	if (polygon_push(lst_walls, data) == E_ERROR_MALLOC)
		return (E_ERROR_MALLOC);
	return (E_SUCCESS);
}

static int	gen_floor(t_param *p, t_list_polygons **lst_walls,
	t_list_points *pt, int texid)
{
	t_list_polygons		data;

	data.points = pt;
	data.texture = p->textures[texid];
	data.options = 0;
	data.options |= O_FLOOR;
	if (polygon_push(lst_walls, data) == E_ERROR_MALLOC)
		return (E_ERROR_MALLOC);
	return (E_SUCCESS);
}

static int	push_points(t_list_polygons *tmp, t_list_points **lst_points_floor,
	t_list_points **lst_points_ceiling)
{
	if (points_pushback(lst_points_ceiling, tmp->points->point)
		== E_ERROR_MALLOC)
		return (E_ERROR_MALLOC);
	if (points_pushback(lst_points_floor, tmp->points->next->next->next->point)
		== E_ERROR_MALLOC)
		return (E_ERROR_MALLOC);
	return (E_SUCCESS);
}

int			generate_ceilandfloor(t_param *p, t_list_polygons **lst_walls, 	\
									int tex_floor, int tex_ceiling)
{
	t_list_polygons		*tmp;
	t_list_points		*lst_points_floor;
	t_list_points		*lst_points_ceiling;

	lst_points_ceiling = NULL;
	lst_points_floor = NULL;
	tmp = *lst_walls;
	if (tlist_count_polygon(tmp) <= 2)
		return (0);
	while (tmp)
	{
		if (!(tmp->options & O_WALLY) && !(tmp->options & IS_SPRITE))
			if (push_points(tmp, &lst_points_floor, &lst_points_ceiling)
				== E_ERROR_MALLOC)
				return (E_ERROR_MALLOC);
		tmp = tmp->next;
	}
	if (gen_ceil(p, lst_walls, lst_points_ceiling, tex_ceiling))
		return (1);
	if (gen_floor(p, lst_walls, lst_points_floor, tex_floor))
		return (1);
	return (E_SUCCESS);
}
