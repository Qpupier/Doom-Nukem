/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sub_bloc_gif.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 10:30:35 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 15:18:57 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "gif.h"
#include <fcntl.h>

uint16_t			read_num(int fd)
{
	uint8_t			bytes[2];

	read(fd, bytes, 2);
	return (bytes[0] + (((uint16_t)bytes[1]) << 8));
}

int8_t				check_invalid(t_gd_set_gif *sgif)
{
	if (sgif->fd == -1)
		return (1);
	read(sgif->fd, sgif->sigver, 3);
	if (ft_memcmp(sgif->sigver, "GIF", 3) != 0)
	{
		ft_putstr("invalid signature\n");
		close(sgif->fd);
		return (1);
	}
	read(sgif->fd, sgif->sigver, 3);
	if (ft_memcmp(sgif->sigver, "89a", 3) != 0)
	{
		ft_putstr("invalid version\n");
		close(sgif->fd);
		return (1);
	}
	sgif->width = read_num(sgif->fd);
	sgif->height = read_num(sgif->fd);
	return (0);
}

int8_t				check_color_table_null(t_gd_set_gif *sgif)
{
	read(sgif->fd, &sgif->fdsz, 1);
	if (!(sgif->fdsz & 0x80))
	{
		ft_putstr("no global color table\n");
		close(sgif->fd);
		return (1);
	}
	sgif->depth = ((sgif->fdsz >> 4) & 7) + 1;
	sgif->gct_sz = 1 << ((sgif->fdsz & 0x07) + 1);
	read(sgif->fd, &sgif->bgidx, 1);
	read(sgif->fd, &sgif->aspect, 1);
	sgif->gif = ft_calloc(1, sizeof(*sgif->gif) +
		4 * sgif->width * sgif->height);
	if (!sgif->gif)
	{
		close(sgif->fd);
		return (1);
	}
	return (0);
}

t_gd_set_gif		*gd_open_gif(const char *fname)
{
	t_gd_set_gif	*sgif;
	int				error;

	if (!(sgif = malloc(sizeof(t_gd_set_gif))))
		return (NULL);
	sgif->fd = open(fname, O_RDONLY);
	if ((error = check_invalid(sgif)))
		return (NULL);
	if ((error = check_color_table_null(sgif)))
		return (NULL);
	sgif->gif->fd = sgif->fd;
	sgif->gif->width = sgif->width;
	sgif->gif->height = sgif->height;
	sgif->gif->depth = sgif->depth;
	sgif->gif->gct.size = sgif->gct_sz;
	read(sgif->fd, sgif->gif->gct.colors, 3 * sgif->gif->gct.size);
	sgif->gif->palette = &sgif->gif->gct;
	sgif->gif->bgindex = sgif->bgidx;
	sgif->gif->canvas = (uint8_t *)&sgif->gif[1];
	sgif->gif->frame = &sgif->gif->canvas[3 * sgif->width * sgif->height];
	if (sgif->gif->bgindex)
		ft_memset(sgif->gif->frame, sgif->gif->bgindex,
			sgif->gif->width * sgif->gif->height);
	sgif->gif->anim_start = lseek(sgif->fd, 0, SEEK_CUR);
	return (sgif);
}

void				discard_sub_blocks(t_gd_gif *gif)
{
	uint8_t				size;

	read(gif->fd, &size, 1);
	lseek(gif->fd, size, SEEK_CUR);
	while (size)
	{
		read(gif->fd, &size, 1);
		lseek(gif->fd, size, SEEK_CUR);
	}
}
