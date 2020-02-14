/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_icons.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/12 12:06:43 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

uint32_t	umlx_getpixel2(t_mlx_img2 img, int x, int y)
{
	if (x < 0 || y < 0 || x >= img.width || y >= img.height)
		return (0x000000);
	return (img.img[y * img.width + x]);
}

void		display_img(t_mlx_img2 win, t_mlx_img2 texture, t_fvec2d pos,
							t_fvec2d size)
{
	int	i;
	int	j;

	j = -1;
	while (++j < size.x)
	{
		i = -1;
		while (++i < size.y)
			umlx_putpixel(win, pos.x + i, pos.y + j,
		umlx_getpixel2(texture, i * texture.width / size.y,
		j * texture.height / size.x));
	}
}
