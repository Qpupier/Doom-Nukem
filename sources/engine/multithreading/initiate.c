/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   initiate.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 10:01:33 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 19:56:40 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"
#include "multithread_utils.h"

void			*display_multhreaded(void *d)
{
	t_multi_disp		*data;
	int					i;
	int					j;
	t_zone_mt			zone;
	intmax_t			pos;

	data = d;
	zone.xmin = data->start_width;
	zone.xmax = data->end_width;
	iterate_multithread_rooms(data->p, zone);
	i = -1;
	while (++i < data->p->engine_settings->height)
	{
		j = zone.xmin - 1;
		while (++j < zone.xmax)
		{
			pos = i * data->p->engine_settings->width + j;
			data->p->mlx->win2.img[pos] = (data->p->pstate & RASTER) ?
				display(data->p, data->p->buffer[pos]) : 0x000000;
		}
	}
	return (d);
}

void			multithread_zone(t_param *p)
{
	register int		index_room;
	int					index;

	index_room = -1;
	while (++index_room < p->nb_rooms)
		move_lights(p, &p->rooms[index_room]);
	index = -1;
	while (++index < p->total_polygons)
		make_data(p, p->lst_polygons[index], p->lst_polygons[index]->obj_ptr);
	index = -1;
	while (++index < AMMO)
		make_data(p, &p->projectiles[index], NULL);
}

void			start_multithread(t_param *p)
{
	pthread_t		thread[4];
	t_multi_disp	data[4];
	register int	i;
	int				tw;

	tw = (p->engine_settings->width * .25);
	i = -1;
	while (++i < 4)
	{
		data[i].start_width = (i * tw);
		data[i].end_width = (i + 1) * tw;
		data[i].p = p;
		if (pthread_create(&thread[i], NULL, &display_multhreaded, &data[i]))
			return ;
	}
	while (i--)
		if (pthread_join(thread[i], NULL))
			return ;
}
