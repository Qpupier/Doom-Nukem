/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_line_straight_vert.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/17 15:05:32 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 17:38:06 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_line_straight_vert(t_mlx_img img, t_cplx a, t_cplx z, t_rgb color)
{
	int	y1;

	y1 = a.im;
	while (ft_abs(z.im - y1) >= 1)
	{
		ft_pixel_put_rgb(img, a.rl, y1, color);
		y1 < z.im ? y1++ : y1--;
	}
	return (1);
}
