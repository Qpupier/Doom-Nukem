/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_sprites.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 10:18:59 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 17:21:44 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		gen_poly(t_list_points **lst_points, t_list_polygons poly,
	t_vec pos, float scale)
{
	points_pushback(lst_points, (t_vec) {pos.x, pos.y, pos.z});
	points_pushback(lst_points, (t_vec)
	{
		pos.x,
		pos.y + (poly.texture.height * scale),
		pos.z
	});
	points_pushback(lst_points, (t_vec)
	{
		pos.x + (poly.texture.width * scale),
		pos.y + (poly.texture.height * scale),
		pos.z
	});
	points_pushback(lst_points, (t_vec)
	{
		pos.x + (poly.texture.width * scale),
		pos.y, pos.z
	});
}

char			**get_data(char *line, t_vec *pos, float *scale)
{
	char			**data;

	if (!(data = ft_strsplit(line, ',')) || count_dstr(data) < 3)
		return (NULL);
	if (!(extract_tvec_from_str(data[1], pos)))
	{
		ft_splitdel(&data);
		return (NULL);
	}
	*scale = ft_atof(data[2]);
	fclamp(scale, .1, 30);
	return (data);
}

static int		dispatch_parsing_texture(t_param *p, t_mlx_img2 *tex,
	char *line)
{
	if (get_ext(line) == 1)
	{
		tex->ptr = NULL;
		tex->endian = 0;
		tex->bpp = 0;
		tex->s_l = 0;
		if (!(tex->img = (unsigned int *)gif_to_image(line, &tex->width,
			&tex->height)))
			return (0);
	}
	else if (get_ext(line) == 2)
	{
		if (!(umlx_xpm_to_image(p->mlx->mlx_ptr, tex, line)))
			return (0);
	}
	else
		return (0);
	return (1);
}

static void		extract_info(t_param *p, char *line, t_list_polygons **lst_poly)
{
	char			**data;
	t_vec			pos;
	float			scale;
	t_list_polygons	poly;

	poly.points = NULL;
	if (!(data = get_data(line, &pos, &scale)))
		return ;
	poly.options = 0;
	poly.options |= IS_SPRITE;
	poly.vn = (t_vec){0, 0, -1};
	if (!(dispatch_parsing_texture(p, &poly.texture, get_path(p->pstate,
		data[0]))))
	{
		ft_splitdel(&data);
		return ;
	}
	ft_splitdel(&data);
	gen_poly(&poly.points, poly, pos, scale);
	if (tlist_count_points(poly.points) != 4)
		return ;
	polygon_push(lst_poly, poly);
}

void			parse_sprites(t_param *p, t_list_line *lst,
	t_list_polygons **walls, t_room_index index)
{
	t_list_line		*tmp_lst;
	int				i;
	t_list_objects	*objects;

	objects = NULL;
	tmp_lst = lst;
	i = 0;
	while (tmp_lst && ++i)
	{
		if (((i > index.start && index.end == -1)
				|| (i > index.start && index.end != -1 && i < index.end))
					&& tmp_lst->line[0] == '#')
			if (ft_strnequ("#SPRITE ", tmp_lst->line, 8))
				extract_info(p, tmp_lst->line + 8, walls);
		tmp_lst = tmp_lst->next;
	}
	return ;
}
