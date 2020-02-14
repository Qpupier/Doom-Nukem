/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   upscale.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/07 09:45:45 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:48:05 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"
#include "multithread_utils.h"

void		*upscale_gen(void *vdata)
{
	register int			i;
	register int			j;
	t_mt_upscale			*data;
	int						nj;
	int						ni;

	data = vdata;
	j = -1;
	while (++j < data->settings->win_height)
	{
		nj = j * data->settings->quality;
		i = data->min_w;
		while (i < data->max_w)
		{
			ni = i * data->settings->quality;
			data->to.img[j * data->to.width + i] =
									data->from.img[nj * data->from.width + ni];
			i++;
		}
	}
	return (vdata);
}

void		upscale(t_engine_settings *settings, t_mlx_img2 win,
	t_mlx_img2 texture)
{
	pthread_t			thread[2];
	t_mt_upscale		data[2];
	register size_t		i;
	int					w;

	w = settings->win_width * .5;
	i = -1;
	while (++i < 2)
	{
		data[i].from = texture;
		data[i].to = win;
		data[i].min_w = i * w;
		data[i].max_w = (i + 1) * w;
		data[i].settings = settings;
		if (pthread_create(&thread[i], NULL, &upscale_gen, &data[i]))
			return ;
	}
	while (i--)
		if (pthread_join(thread[i], NULL))
			return ;
}
