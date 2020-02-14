/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   xpm_to_img.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 15:49:56 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 12:38:16 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	xpm_to_img(void *ptr, t_mlx_img *img, char *file)
{
	if (!(img->ptr = 														\
			mlx_xpm_file_to_image(ptr, file, &img->width, &img->height)) 	\
			|| !(img->img = 												\
			mlx_get_data_addr(img->ptr, &img->bpp, &img->s_l, &img->endian)))
		ft_error(ft_strjoin("Fail to load img : ", file));
}
