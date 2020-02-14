/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   death.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 10:44:18 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 12:27:04 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int		hud_player_dead(t_param *p)
{
	int				i;
	int				j;
	int				px;
	int				py;
	t_mlx_img2		img;

	if (p->player.life > 0 || p->nb_textures < 2)
		return (0);
	img = p->textures[p->nb_textures - 1];
	i = -1;
	while (++i < p->engine_settings->win_width && (j = -1))
	{
		while (++j < p->engine_settings->win_height)
		{
			px = i * img.width / p->engine_settings->win_width;
			py = j * img.height / p->engine_settings->win_height;
			p->mlx->render.img[j * p->engine_settings->win_width + i] =
				img.img[py * img.width + px];
		}
	}
	mlx_mouse_show();
	mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr, 			\
		p->mlx->render.ptr, 0, 0);
	return (1);
}
