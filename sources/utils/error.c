/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 14:09:41 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 15:32:07 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		handle_error(t_param *p, unsigned short int type)
{
	ft_putstr(COLOR_RED);
	if (type == E_ERROR_MALLOC)
		ft_printf("An allocation error has occured, please try again.\n");
	ft_printf(COLOR_RESET);
	if (p != NULL)
		free_and_exit(p);
	exit(1);
}

void		logerror(t_param *p, char *str)
{
	if (p->fd_log == -1)
		return ;
	ft_putstr_fd(str, p->fd_log);
}

void		log_error(t_param *p)
{
	if ((p->fd_log = open("./doom-nukem.log",
		O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return ;
	ft_putstr_fd("Starting Doom...\n", p->fd_log);
}

static int	free_everyting(t_param *p)
{
	int					i;
	t_list_room			*ro;
	t_list_objects		*ob;

	i = -1;
	while (++i < p->nb_textures)
	{
		ft_memdel((void **)&p->textures[i].img);
		ft_memdel((void **)&p->textures[i].ptr);
	}
	ft_memdel((void **)&p->lst_polygons);
	ro = p->room_list;
	while (ro)
	{
		free_t_list_polygons(&ro->walls);
		ob = ro->objects;
		while (ob)
		{
			free_t_list_polygons(&ob->poly);
			ob = ob->next;
		}
		free_t_list_objects(&ro->objects);
		ro = ro->next;
	}
	return (-1);
}

int			free_and_exit(t_param *p)
{
	int					i;
	unsigned	int		j;

	i = free_everyting(p);
	while (++i < p->nb_rooms && (j = -1))
	{
		ft_memdel((void **)&p->rooms[i].walls);
		while (++j < p->rooms[i].nb_objects)
			ft_memdel((void **)&p->rooms[i].objects->poly);
	}
	ft_memdel((void **)&p->rooms);
	i = -1;
	while (++i < p->engine_settings->height)
		ft_memdel((void **)&p->rays[i]);
	ft_memdel((void **)&p->rays);
	ft_memdel((void **)&p->textures);
	ft_memdel((void **)&p->mlx);
	ft_memdel((void **)&p->buffer);
	ft_memdel((void **)&p->actions);
	ft_memdel((void **)&p->audio);
	ft_memdel((void **)&p->audio_source);
	ft_memdel((void **)&p->engine_settings);
	ft_memdel((void **)&p);
	exit(1);
	return (1);
}
