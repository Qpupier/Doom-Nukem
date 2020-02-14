/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_parser.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 13:09:37 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 13:01:35 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			generate_polygons_with_materials(t_parse_mtl *material,
	t_tmp_obj *buff, t_list_polygons **poly_list, char *line)
{
	t_list_polygons		data;
	char				**vertices;
	unsigned int		nb_vertices;

	if (!(vertices = ft_strsplit(line, ' ')))
		return ;
	nb_vertices = count_dstr(vertices) - 1;
	if (nb_vertices < 3)
	{
		ft_splitdel(&vertices);
		return ;
	}
	init_polygon_structure(&data);
	generate_polygon(buff, &data, vertices, nb_vertices);
	data.ka = str_to_vec3(material->ka);
	data.kd = str_to_vec3(material->kd);
	data.texture2 = (t_mlx_img2 *)material->ptr_tex;
	if (data.texture2)
		data.options ^= HAS_TEXTURE;
	data.options ^= IS_BLENDER;
	ft_splitdel(&vertices);
	polygon_push(poly_list, data);
}

static int		start_gen_polygon(t_tmp_obj *buff, t_list_line *line,
	t_list_polygons **poly_list)
{
	t_list_line		*f;
	t_parse_mtl		*mat;

	if (!line || !line->next)
		return (0);
	if (!(mat = get_material_data(buff, line->line + 7)))
	{
		ft_putstr(COLOR_RED);
		return (-1);
	}
	f = line->next;
	while (f)
	{
		if (f->line[0] == 'f' && f->line[1] == ' ')
		{
			generate_polygons_with_materials(mat, buff, poly_list, f->line);
			f->line[0] = '#';
		}
		if (!f->next || ft_strnequ(f->next->line, "usemtl ", 7))
			break ;
		f = f->next;
	}
	return (1);
}

void			gen_material_polygon(t_param *p, t_tmp_obj *buff,
	t_list_polygons **poly_list)
{
	t_list_line		*f;
	int				state;

	state = 1;
	f = buff->file;
	while (f)
	{
		if (ft_strnequ("usemtl ", f->line, 7))
		{
			state = start_gen_polygon(buff, f, poly_list);
			if (state == -1)
			{
				ft_putstr(f->line + 7);
				ft_putstr(" not found. Skipping.");
			}
		}
		f = f->next;
	}
	(void)p;
}
