/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_materials.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 09:29:48 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 14:35:53 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

t_parse_mtl		*find_material(t_tmp_obj *buff, char *str)
{
	t_parse_mtl	*tmp;

	tmp = buff->materials_list;
	while (tmp)
	{
		if (ft_strequ(str, tmp->name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void			iterate_material(t_list_line *lst, t_tmp_obj *buff)
{
	t_list_line	*tmp;
	t_parse_mtl	*ptr;

	if (!(ptr = find_material(buff, lst->line + 7)))
		return ;
	tmp = lst->next;
	if (!tmp || !tmp->next)
		return ;
	while (tmp)
	{
		if (ft_strnequ("map_Kd ", tmp->line, 7)
			|| ft_strnequ("map_kd ", tmp->line, 7))
			ptr->map_kd = ft_strdup(tmp->line + 7);
		if (ft_strnequ("Ka ", tmp->line, 3))
			ptr->ka = ft_strdup(tmp->line + 3);
		if (ft_strnequ("Kd ", tmp->line, 3))
			ptr->kd = ft_strdup(tmp->line + 3);
		if (tmp->next && ft_strnequ("newmtl ", tmp->next->line, 7))
			break ;
		tmp = tmp->next;
	}
	(void)buff;
}

void			iterate_mtl_tmp(t_list_line *lst, t_tmp_obj *buff)
{
	t_list_line		*mtl_tmp;

	mtl_tmp = lst;
	while (mtl_tmp)
	{
		if (ft_strnequ("newmtl ", mtl_tmp->line, 7))
			iterate_material(mtl_tmp, buff);
		mtl_tmp = mtl_tmp->next;
	}
}

int				open_mtl(t_param *p, t_tmp_obj *buff)
{
	char			*line;
	int				fd;
	t_list_line		*mtl_tmp;

	mtl_tmp = NULL;
	if ((fd = open(get_path(p->pstate, buff->mtl_file), O_RDONLY)) < 0)
	{
		ft_putstr(COLOR_RED"|" COLOR_RESET);
		logerror(p, get_path(p->pstate, buff->mtl_file));
		logerror(p, " could not be loaded.\n");
		return (0);
	}
	while (get_next_line(fd, &line))
	{
		if (ft_strnequ("newmtl ", line, 7))
			push_material(&buff->materials_list, 0, line + 7);
		line_pushback(&mtl_tmp, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	iterate_mtl_tmp(mtl_tmp, buff);
	free_t_list_lines(&mtl_tmp);
	return (1);
}
