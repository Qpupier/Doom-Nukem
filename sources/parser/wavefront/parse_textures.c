/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_textures.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 15:28:15 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 14:47:10 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static t_mlx_img2		*get_texture(t_param *p, char *file)
{
	t_textures_obj	*tmp;
	t_mlx_img2		*img;

	img = NULL;
	tmp = p->tex_objs;
	while (tmp)
	{
		if (ft_strequ(file, tmp->file))
		{
			img = &tmp->t;
			return (img);
		}
		tmp = tmp->next;
	}
	return (img);
}

void					load_obj_texture(t_param *p, t_parse_mtl *lst)
{
	t_parse_mtl			*tmp;
	t_mlx_img2			*ptr;

	tmp = lst;
	while (tmp)
	{
		if (tmp->map_kd)
		{
			tmp->ptr_tex = NULL;
			if (!(ptr = get_texture(p, get_path(p->pstate, tmp->map_kd))))
			{
				ptr = push_obj_textures(p, &p->tex_objs,
					get_path(p->pstate, tmp->map_kd));
				if (!ptr)
				{
					ft_putstr(COLOR_RED "|" COLOR_RESET);
					logerror(p, get_path(p->pstate, tmp->map_kd));
					logerror(p, " could not be loaded.\n");
				}
			}
			tmp->ptr_tex = ptr;
		}
		tmp = tmp->next;
	}
}
