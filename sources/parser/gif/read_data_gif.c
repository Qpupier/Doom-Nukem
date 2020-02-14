/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_data_gif.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 10:27:13 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 15:27:20 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"
#include "gif.h"

unsigned int		rgbtohexgif(int r, int g, int b)
{
	unsigned int a;
	unsigned int hex;

	a = 0;
	if (r == 254 && g == 0 && b == 252)
		return ((255 << 24) | (255 << 16) | (255 << 8) | 255);
	hex = (a << 24) | (r << 16) | (g << 8) | b;
	return (hex);
}

int					gd_render_frame(t_gd_gif *gif, uint8_t *buffer)
{
	ft_memcpy(buffer, gif->canvas, gif->width * gif->height * 3);
	if (!(render_frame_rect(gif, buffer)))
		return (0);
	return (1);
}

void				fill_img_arr(uint32_t *tmp, t_gif_data *d)
{
	d->color = (uint8_t *)d->buffer;
	d->curr_height = 0;
	while (d->curr_height < d->gif->gif->height)
	{
		d->curr_width = 0;
		while (d->curr_width < d->gif->gif->width)
		{
			tmp[d->curr_height * d->gif->gif->width +
				d->curr_width] = rgbtohexgif(d->color[d->f],
				d->color[d->f + 1], d->color[d->f + 2]);
			d->f += 3;
			d->curr_width++;
		}
		d->curr_height++;
	}
}

uint32_t			*malloc_img_arr(t_gif_data *d)
{
	uint32_t		*tmp;

	if (!(tmp = malloc(sizeof(uint32_t)
		* (d->gif->gif->width * d->gif->height))))
		return (NULL);
	if (!(d->buffer = malloc((d->gif->gif->width * d->gif->gif->height) * 3)))
	{
		free(tmp);
		return (NULL);
	}
	if (!gd_get_frame(d->gif->gif))
	{
		free(d->buffer);
		free(tmp);
		return (NULL);
	}
	d->f = 0;
	if (!gd_render_frame(d->gif->gif, (uint8_t *)d->buffer))
	{
		free(d->buffer);
		free(tmp);
		return (NULL);
	}
	fill_img_arr(tmp, d);
	return (tmp);
}

uint32_t			*gif_to_image(char *path, int *width, int *height)
{
	t_gif_data		*d;
	uint32_t		*img;

	if (!(d = (t_gif_data *)malloc(sizeof(*d))))
		return (NULL);
	d->gif = gd_open_gif(path);
	if (!d->gif)
	{
		free(d);
		return (NULL);
	}
	*width = d->gif->gif->width;
	*height = d->gif->gif->height;
	if (!(img = malloc_img_arr(d)))
	{
		gd_close_gif(d->gif);
		free(d);
		return (0);
	}
	gd_rewind(d->gif->gif);
	free(d->buffer);
	gd_close_gif(d->gif);
	free(d);
	return (img);
}
