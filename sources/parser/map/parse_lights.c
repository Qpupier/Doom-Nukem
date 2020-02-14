/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_lights.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 13:43:49 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 12:32:39 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			get_light(char *line, t_list_lights **lights)
{
	char		**data;
	t_vec		pos;
	float		intensity;

	if (!(data = ft_strsplit(line, ',')))
		return ;
	if (!(extract_tvec_from_str(data[0], &pos)))
	{
		ft_splitdel(&data);
		return ;
	}
	intensity = ft_atof(data[1]);
	fclamp(&intensity, 0, 1);
	lights_push(lights, (t_list_lights)
	{
		.pos = pos,
		.pos_rot = (t_vec) {0, 0, 0},
		.intensity = intensity,
		.color = ft_color_rgb_to_int(ft_color_hex_to_rgb(data[2])),
		.next = NULL
	});
	ft_splitdel(&data);
}

t_list_lights	*parse_lights(t_list_line *lst, t_room_index index)
{
	t_list_line		*tmp_lst;
	int				i;
	t_list_lights	*light;

	light = NULL;
	tmp_lst = lst;
	i = 0;
	while (tmp_lst && ++i)
	{
		if (((i > index.start && index.end == -1)
				|| (i > index.start && index.end != -1 && i < index.end))
					&& tmp_lst->line[0] == '#')
			if (ft_strnequ("#LIGHT ", tmp_lst->line, 7))
				get_light(tmp_lst->line + 7, &light);
		tmp_lst = tmp_lst->next;
	}
	return (light);
}
