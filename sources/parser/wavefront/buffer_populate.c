/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   buffer_populate.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 12:11:05 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 20:02:36 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static int		chk_face(char *str, int *err)
{
	int		e;
	int		c;

	e = 0;
	c = 0;
	while (*str)
	{
		if (*str == ' ')
			c++;
		if (!ft_isnumber(*str) && *str != '/' && *str != ' ')
			e++;
		str++;
	}
	if (c < 2 || e)
	{
		(*err)++;
		return (0);
	}
	return (1);
}

static int		chk_vec(char *str, int *err)
{
	int		e;
	int		c;

	c = 0;
	e = 0;
	while (*str)
	{
		if (*str == ' ')
			c++;
		if (*str != ' ' && !ft_isnumber(*str) && *str != '-' && *str != '.')
			e++;
		str++;
	}
	if (c != 2 || e)
	{
		(*err)++;
		return (0);
	}
	return (1);
}

static int		chk_vt(char *str, int *err)
{
	int		e;
	int		c;

	c = 0;
	e = 0;
	while (*str)
	{
		if (*str == ' ')
			c++;
		if (*str != ' ' && *str != '-' && !ft_isnumber(*str) && *str != '.')
			e++;
		str++;
	}
	if (c != 1 || e)
	{
		(*err)++;
		return (0);
	}
	return (1);
}

void			populate_buffer(t_tmp_obj *buff, char *line, int *e)
{
	line_pushfront(&buff->file, line);
	if (ft_strnequ("v ", line, 2) && chk_vec(line + 2, e))
		line_pushfront(&buff->vertices, line) == E_SUCCESS ? buff->nb_v++ : 0;
	if (ft_strnequ("f ", line, 2) && chk_face(line + 2, e))
		line_pushfront(&buff->faces, line) == E_SUCCESS ? buff->nb_faces++ : 0;
	if (ft_strnequ("vn ", line, 3) && chk_vec(line + 3, e))
		line_pushfront(&buff->normals, line) == E_SUCCESS ? buff->nb_vn++ : 0;
	if (ft_strnequ("vt ", line, 3) && chk_vt(line + 3, e))
		line_pushfront(&buff->textures, line) == E_SUCCESS ? buff->nb_vt++ : 0;
	if ((line[0] == 'v' || line[0] == 'f') && !line[1])
		(*e)++;
	if ((ft_strnequ("vt", line, 2) || ft_strnequ("vn", line, 2)) && !line[2])
		(*e)++;
	(void)e;
	if (ft_strnequ("mtllib ", line, 7))
		buff->mtl_file = ft_strdup(line + 7);
}
