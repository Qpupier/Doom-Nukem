/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mlx_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/21 12:42:45 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 13:33:32 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

short int		umlx_create_image(void *ptr, t_mlx_img2 *img, int w, int h)
{
	if (!(img->ptr = mlx_new_image(ptr, w, h)))
		return (0);
	if (!(img->img = (unsigned int *)mlx_get_data_addr(img->ptr, &img->bpp,
													&img->s_l, &img->endian)))
		return (0);
	img->width = w;
	img->height = h;
	return (1);
}

short int		umlx_xpm_to_image(void *ptr, t_mlx_img2 *img, char *file)
{
	img->ptr = mlx_xpm_file_to_image(ptr, file, &img->width, &img->height);
	if (!img->ptr)
		return (0);
	img->img = (unsigned int *)mlx_get_data_addr(img->ptr,
										&img->bpp, &img->s_l, &img->endian);
	if (!img->img)
		return (0);
	return (1);
}

void			umlx_putpixel(t_mlx_img2 img, int x, int y, uint32_t color)
{
	if (y * img.width + x > img.width * img.height ||
						x < 0 || y < 0 || x >= img.width || y >= img.height)
		return ;
	img.img[y * img.width + x] = color;
}

uint32_t		umlx_getpixel2(t_mlx_img2 img, int x, int y)
{
	if (x < 0 || y < 0 || x >= img.width || y >= img.height)
		return (0x000000);
	return (img.img[y * img.width + x]);
}

void			display_img(t_mlx_img2 win, t_mlx_img2 texture, t_real pos,
		t_real size)
{
	int			i;
	int			j;
	uint32_t	color;

	j = -1;
	while (++j < size.x)
	{
		i = -1;
		while (++i < size.y)
		{
			color = umlx_getpixel2(texture, j * texture.width / size.x,
				i * texture.height / size.y);
			if ((color >> 24 & 0xFF) != 255)
				umlx_putpixel(win, pos.x + j, pos.y + i, color);
		}
	}
}
