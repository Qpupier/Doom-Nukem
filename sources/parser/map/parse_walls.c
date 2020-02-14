/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_walls.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/03 15:07:45 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:52:24 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		get_texid(char *line, int *tex_floor, int *tex_ceiling)
{
	char			**data;

	if (!(data = ft_strsplit(line, ' ')))
		return ;
	*tex_floor = ft_atoi(data[1]);
	*tex_ceiling = ft_atoi(data[2]);
	ft_splitdel(&data);
}

t_list_polygons	*parse_walls(t_param *p, t_list_line *lst, t_room_index index)
{
	t_list_line		*tmp_lst;
	int				i;
	int				tex_floor;
	int				tex_ceiling;
	t_list_polygons	*lst_walls;

	tmp_lst = lst;
	lst_walls = NULL;
	i = 0;
	while (tmp_lst && ++i)
	{
		if (i == index.start)
			get_texid(tmp_lst->line, &tex_floor, &tex_ceiling);
		if (((i > index.start && index.end == -1)
				|| (i > index.start && index.end != -1 && i < index.end))
					&& tmp_lst->line[0] != '#' && show_parseprogress(p))
			generate_walls(p, &lst_walls, tmp_lst->line);
		tmp_lst = tmp_lst->next;
	}
	generate_ceilandfloor(p, &lst_walls, tex_floor, tex_ceiling);
	return (lst_walls);
}
