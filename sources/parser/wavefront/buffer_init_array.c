/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   buffer_init_array.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 13:05:12 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 12:48:53 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static int		allocate_arrays(t_tmp_obj *buff)
{
	if (!(buff->tab_vertices = malloc(sizeof(t_vec) * buff->nb_v)))
		return (0);
	if (!(buff->tab_normals = malloc(sizeof(t_vec) * buff->nb_vn)))
	{
		free(buff->tab_vertices);
		return (0);
	}
	if (!(buff->tab_textures = malloc(sizeof(t_vec) * buff->nb_vt)))
	{
		free(buff->tab_vertices);
		free(buff->tab_textures);
		return (0);
	}
	return (1);
}

static void		init_vertices(t_tmp_obj *buff)
{
	unsigned int	i;
	t_list_line		*tmp;
	char			**data;

	i = 0;
	tmp = buff->vertices;
	while (tmp)
	{
		if ((data = ft_strsplit(tmp->line, ' ')))
		{
			buff->tab_vertices[i] = (t_vec)
			{
				.x = ft_atof(data[1]) * 20,
				.y = ft_atof(data[2]) * -20,
				.z = ft_atof(data[3]) * -20
			};
			ft_splitdel(&data);
			i++;
		}
		tmp = tmp->next;
	}
}

static void		init_normals(t_tmp_obj *buff)
{
	unsigned int	i;
	t_list_line		*tmp;
	char			**data;

	i = 0;
	tmp = buff->normals;
	while (tmp)
	{
		if ((data = ft_strsplit(tmp->line, ' ')))
		{
			buff->tab_normals[i] = (t_vec)
			{
				.x = ft_atof(data[1]),
				.y = ft_atof(data[2]) * -1,
				.z = ft_atof(data[3]) * -1
			};
			ft_splitdel(&data);
			i++;
		}
		tmp = tmp->next;
	}
}

static void		init_vt(t_tmp_obj *buff)
{
	unsigned int	i;
	t_list_line		*tmp;
	char			**data;

	i = 0;
	tmp = buff->textures;
	while (tmp)
	{
		if ((data = ft_strsplit(tmp->line, ' ')))
		{
			buff->tab_textures[i] = (t_vec)
			{
				.x = ft_atof(data[1]),
				.y = ft_atof(data[2]),
				.z = 0
			};
			ft_splitdel(&data);
			i++;
		}
		tmp = tmp->next;
	}
}

int				init_array(t_tmp_obj *buff)
{
	if (!(allocate_arrays(buff)))
		return (0);
	init_vertices(buff);
	init_normals(buff);
	init_vt(buff);
	return (1);
}
