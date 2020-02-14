/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   generate_polygons.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 14:16:49 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 10:43:38 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		init_data(t_param *p, t_list_polygons *data)
{
	data->points = NULL;
	data->vt = NULL;
	data->vn = (t_vec){0, 0, 0};
	data->options = 0;
	data->options |= IS_BLENDER;
	data->texture = p->textures[0];
}

static int		count_separator_face(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (*str == '/')
			count++;
		str++;
	}
	return (count);
}

static int		get_face_element(int count_separator, int i,
	char **face_vertices, char ***face_elements)
{
	if (count_separator >= 1)
	{
		if (!((*face_elements) = ft_strsplit(face_vertices[i], '/')))
			return (0);
		return (count_dstr(*face_elements) - 1);
	}
	return (0);
}

void			generate_polygon(t_tmp_obj *buffer, t_list_polygons *data,
	char **face_vertices, int nb_vertices)
{
	int				i;
	char			**element;
	int				nb_elem;
	int				nb_separator;

	i = 0;
	nb_elem = 0;
	while (++i <= nb_vertices)
	{
		nb_separator = count_separator_face(face_vertices[i]);
		nb_elem = get_face_element(nb_separator, i, face_vertices, &element);
		points_pushback(&data->points,
			buffer->tab_vertices[ft_atoi(face_vertices[i]) - 1]);
		if (nb_separator == 2)
		{
			data->vn = buffer->tab_normals[ft_atoi(element[nb_elem]) - 1];
			data->options |= HAS_VN;
		}
		if ((nb_separator == 1 || (nb_elem == 2)) && element[1])
			points_pushback(&data->vt,
				buffer->tab_textures[ft_atoi(element[1]) - 1]);
		if (element && nb_separator >= 1)
			ft_splitdel(&element);
	}
}

t_list_polygons	*generate_polygon_no_mats(t_param *p, t_tmp_obj *buffer,
	t_list_polygons **res)
{
	t_list_line		*tmp;
	t_list_polygons	poly_data;
	t_list_polygons	*result;
	char			**face_vertices;
	int				nb_vertices;

	result = NULL;
	tmp = buffer->file;
	while (tmp)
	{
		if (ft_strnequ("f ", tmp->line, 2))
		{
			if (!(face_vertices = ft_strsplit(tmp->line, ' ')))
				return (NULL);
			nb_vertices = count_dstr(face_vertices) - 1;
			init_data(p, &poly_data);
			generate_polygon(buffer, &poly_data, face_vertices, nb_vertices);
			if (face_vertices)
				ft_splitdel(&face_vertices);
			polygon_push(res, poly_data);
		}
		tmp = tmp->next;
	}
	return (result);
}
