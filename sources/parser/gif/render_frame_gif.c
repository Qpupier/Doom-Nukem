/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render_frame_gif.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 10:28:21 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 18:16:15 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gif.h"

int				read_image_data(t_gd_gif *gif, int interlace)
{
	t_inc			*inc;
	t_img_data		*datas;
	t_key			*keys;

	if (!super_free(&datas, &inc, &keys))
		return (-1);
	keys->gif = gif;
	if (!(set_datas(gif, datas, keys)))
		return (-1);
	while (1)
	{
		if (check_data_table(datas, keys))
			return (-1);
		if (datas->key == datas->clear)
			continue;
		if (datas->key == datas->stop)
			break ;
		if (datas->ret == 1)
			keys->key_size++;
		check_data_entries(gif, datas, inc, interlace);
	}
	read(gif->fd, &datas->sub_len, 1);
	lseek(gif->fd, datas->end, SEEK_SET);
	free_four(inc, keys, datas);
	return (0);
}

int				read_image(t_gd_gif *gif)
{
	uint8_t			fisrz;
	int				interlace;

	gif->fx = read_num(gif->fd);
	gif->fy = read_num(gif->fd);
	gif->fw = read_num(gif->fd);
	gif->fh = read_num(gif->fd);
	read(gif->fd, &fisrz, 1);
	interlace = fisrz & 0x40;
	if (fisrz & 0x80)
	{
		gif->lct.size = 1 << ((fisrz & 0x07) + 1);
		read(gif->fd, gif->lct.colors, 3 * gif->lct.size);
		gif->palette = &gif->lct;
	}
	else
		gif->palette = &gif->gct;
	return (read_image_data(gif, interlace));
}

int				render_frame_rect(t_gd_gif *gif, uint8_t *buffer)
{
	t_inc			inc;
	uint8_t			index;
	uint8_t			*color;

	inc.i = gif->fy * gif->width + gif->fx;
	inc.j = 0;
	while (inc.j < gif->fh && !(inc.k = 0))
	{
		while (inc.k++ < gif->fw)
		{
			index = gif->frame[(gif->fy + inc.j) *
				gif->width + gif->fx + inc.k - 1];
			color = &gif->palette->colors[index * 3];
			if (gif->gce.transparency && index == 0)
			{
				color[0] = (uint8_t)254;
				color[1] = (uint8_t)0;
				color[2] = (uint8_t)252;
			}
			ft_memcpy(&buffer[(inc.i + inc.k - 1) * 3], color, 3);
		}
		inc.i += gif->width;
		inc.j++;
	}
	return (1);
}

int				dispose(t_gd_gif *gif)
{
	t_inc			inc;
	uint8_t			*bgcolor;

	if (gif->gce.disposal == 2 && !(inc.j = 0))
	{
		bgcolor = &gif->palette->colors[gif->bgindex * 3];
		inc.i = gif->fy * gif->width + gif->fx;
		while (inc.j < gif->fh && !(inc.k = 0))
		{
			while (inc.k++ < gif->fw)
				ft_memcpy(&gif->canvas[(inc.i + inc.k - 1) * 3], bgcolor, 3);
			inc.i += gif->width;
			inc.j++;
		}
	}
	else if (gif->gce.disposal == 3)
		return (0);
	else
	{
		if (!(render_frame_rect(gif, gif->canvas)))
			return (0);
	}
	return (1);
}

int				gd_get_frame(t_gd_gif *gif)
{
	char			sep;

	if (!dispose(gif))
		return (0);
	read(gif->fd, &sep, 1);
	while (sep != ',')
	{
		if (sep == ';')
			return (0);
		if (sep == '!')
			read_ext(gif);
		else
			return (0);
		read(gif->fd, &sep, 1);
	}
	if (read_image(gif) == -1)
		return (0);
	return (1);
}
