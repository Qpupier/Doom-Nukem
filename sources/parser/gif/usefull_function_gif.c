/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   usefull_function_gif.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 10:24:46 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 15:18:59 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gif.h"

int					super_free(t_img_data **datas, t_inc **inc, t_key **keys)
{
	if (!(*datas = malloc(sizeof(t_img_data))))
		return (0);
	if (!(*inc = malloc(sizeof(t_inc))))
	{
		free(datas);
		return (0);
	}
	if (!(*keys = malloc(sizeof(t_key))))
	{
		free(inc);
		free(keys);
		return (0);
	}
	return (1);
}

int					freemem(void **ptr)
{
	free(&ptr);
	return (1);
}

void				free_four(t_inc *inc, t_key *key, t_img_data *data)
{
	free(inc);
	free(key);
	free(data->table);
	free(data);
	return ;
}

void				gd_rewind(t_gd_gif *gif)
{
	lseek(gif->fd, gif->anim_start, SEEK_SET);
}

void				gd_close_gif(t_gd_set_gif *gif)
{
	close(gif->gif->fd);
	free(gif->gif);
	free(gif);
}
