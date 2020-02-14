/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mlx_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/21 12:42:45 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		umlx_create_image(void *ptr, t_mlx_img2 *img, int w, int h)
{
	if (!(img->ptr = mlx_new_image(ptr, w, h)))
		ft_error("Mlx Error");
	img->img = (unsigned int *)mlx_get_data_addr(img->ptr, &img->bpp,
													&img->s_l, &img->endian);
	img->width = w;
	img->height = h;
}

short int	umlx_xpm_to_image(void *ptr, t_mlx_img2 *img, char *file)
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

void		umlx_putpixel(t_mlx_img2 img, int x, int y, uint32_t color)
{
	if (y * img.width + x > img.width * img.height ||
		x < 0 || y < 0 || x >= img.width || y >= img.height)
		return ;
	img.img[y * img.width + x] = color;
}

uint32_t	umlx_getpixel(t_mlx_img2 img, int x, int y)
{
	if (x < 0 || y < 0 || x >= img.width || y >= img.height)
		return (0x000000);
	return (img.img[y * img.width + x]);
}

void		trace(t_mlx_img2 img, t_v v1, t_v v2, uint32_t c)
{
	t_bressen b;

	b.dx = abs(v2.x - v1.x);
	b.dy = abs(v2.y - v1.y);
	b.sx = (v1.x < v2.x ? 1 : -1);
	b.sy = (v1.y < v2.y ? 1 : -1);
	b.err = (b.dx > b.dy ? b.dx : -b.dy) / 2;
	while (!(v1.x == v2.x && v1.y == v2.y))
	{
		umlx_putpixel(img, v1.x, v1.y, c);
		b.e2 = b.err;
		if (b.e2 > -b.dx)
		{
			b.err -= b.dy;
			v1.x += b.sx;
		}
		if (b.e2 < b.dy)
		{
			b.err += b.dx;
			v1.y += b.sy;
		}
	}
}
