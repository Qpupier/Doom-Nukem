/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wavefront.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 09:54:16 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:06:15 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int			get_ext(char *line)
{
	int		c;

	if (!fileexists(line))
		return (0);
	c = ft_strlen(line) - 1;
	if (line[c] == 'f' && line[c - 1] == 'i' && line[c - 2] == 'g')
		return (1);
	else if (line[c] == 'm' && line[c - 1] == 'p' && line[c - 2] == 'x')
		return (2);
	else
		return (0);
}

static int	dispatch_parser(t_param *p, t_textures_obj *new, char *file)
{
	int		ext;

	ext = get_ext(file);
	if (ext == 1)
	{
		new->t.ptr = NULL;
		new->t.endian = 0;
		new->t.bpp = 0;
		new->t.s_l = 0;
		if (!(new->t.img = (unsigned int *)gif_to_image(file, &new->t.width,
			&new->t.height)))
			return (0);
	}
	else if (ext == 2)
	{
		if (!(new->t.ptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr, file,
										&new->t.width, &new->t.height)))
			return (0);
		if (!(new->t.img = (unsigned int *)mlx_get_data_addr(new->t.ptr,
				&new->t.bpp, &new->t.s_l, &new->t.endian)))
			return (0);
	}
	else
		return (0);
	return (1);
}

void		*push_obj_textures(t_param *p, t_textures_obj **lst, char *file)
{
	t_textures_obj	*new;
	int				err;

	err = 0;
	if (!fileexists(file))
		return (NULL);
	if (!(new = malloc(sizeof(t_textures_obj))))
		handle_error(p, E_ERROR_MALLOC);
	if (!(dispatch_parser(p, new, file)))
	{
		free(new);
		return (NULL);
	}
	ft_bzero(new->file, NAME_MAX);
	ft_strcpy(new->file, file);
	new->next = *lst ? *lst : NULL;
	*lst = new;
	return (err ? NULL : &new->t);
}

int			push_material(t_parse_mtl **lst, int i, char *name)
{
	t_parse_mtl		*new;
	t_parse_mtl		*tmp;

	if (!(new = malloc(sizeof(t_parse_mtl))))
		return (-1);
	new->index = i;
	if (!(new->name = ft_strdup(name)))
		return (E_ERROR_MALLOC);
	new->ka = NULL;
	new->kd = NULL;
	new->map_kd = NULL;
	new->ptr_tex = NULL;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (E_SUCCESS);
}

void		reverse_buffer(t_tmp_obj *tmp)
{
	reverse_t_list_line(&tmp->faces);
	reverse_t_list_line(&tmp->vertices);
	reverse_t_list_line(&tmp->normals);
	reverse_t_list_line(&tmp->textures);
	reverse_t_list_line(&tmp->materials);
	reverse_t_list_line(&tmp->file);
}
