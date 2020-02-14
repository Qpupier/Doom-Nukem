/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_file.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 14:11:55 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 14:46:43 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			init_reader(t_tmp_obj *tmp)
{
	tmp->file = NULL;
	tmp->vertices = NULL;
	tmp->faces = NULL;
	tmp->normals = NULL;
	tmp->materials = NULL;
	tmp->materials_indexes = NULL;
	tmp->textures = NULL;
	tmp->mtl_file = NULL;
	tmp->materials_list = NULL;
	tmp->nb_faces = 0;
	tmp->nb_v = 0;
	tmp->nb_vt = 0;
	tmp->nb_vn = 0;
}

static void		print_err(t_param *p, const char *file)
{
	logerror(p, "Error in file: ");
	logerror(p, (char *)file);
	logerror(p, "\n");
}

int				open_file(t_param *p, t_tmp_obj *buff, const char *file)
{
	int					fd;
	char				*line;
	int					err;

	err = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (-2);
	while (get_next_line(fd, &line))
	{
		populate_buffer(buff, line, &err);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (err)
	{
		print_err(p, file);
		return (0);
	}
	if (buff->mtl_file)
		if (!open_mtl(p, buff))
			return (0);
	load_obj_texture(p, buff->materials_list);
	reverse_buffer(buff);
	ft_strdel(&buff->mtl_file);
	return (init_array(buff) ? 1 : -1);
}
