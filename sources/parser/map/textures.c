/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   textures.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/25 18:06:45 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 14:32:50 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int			count_textures(t_list_line *lst)
{
	t_list_line		*tmp;
	int				count;

	count = 0;
	tmp = lst;
	while (tmp)
	{
		if (ft_strnequ("#TEXTURE ", tmp->line, 9))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static void	print_name(t_param *p, char *file)
{
	ft_putstr(COLOR_RED "|");
	logerror(p, "Couldn't parse ");
	logerror(p, file);
	logerror(p, "\n");
}

static int	dispatch_parsing_texture(t_param *p, int i, char *line)
{
	if (get_ext(line) == 1)
	{
		p->textures[i].ptr = NULL;
		p->textures[i].endian = 0;
		p->textures[i].bpp = 0;
		p->textures[i].s_l = 0;
		if (!(p->textures[i].img =
			(unsigned int *)gif_to_image(line, &p->textures[i].width,
				&p->textures[i].height)))
			return (0);
	}
	else if (get_ext(line) == 2)
	{
		if (!(umlx_xpm_to_image(p->mlx->mlx_ptr, &p->textures[i], line)))
			return (0);
	}
	else
		return (0);
	return (1);
}

int			texture_parse(t_param *p, t_list_line *lst)
{
	t_list_line		*tmp;
	int				i;

	p->nb_textures = count_textures(lst);
	if (!(p->textures = malloc(sizeof(t_mlx_img2) * p->nb_textures)))
		return (E_ERROR_MALLOC);
	tmp = lst;
	i = 0;
	while (tmp && i < p->nb_textures)
	{
		if (ft_strnequ("#TEXTURE ", tmp->line, 9) && show_parseprogress(p))
		{
			if (!dispatch_parsing_texture(p, i,
				get_path(p->pstate, tmp->line + 9)))
			{
				print_name(p, tmp->line + 9);
				return (E_ERROR_PARSING_TEXTURE);
			}
			else
				i++;
		}
		tmp = tmp->next;
	}
	return (E_SUCCESS);
}
