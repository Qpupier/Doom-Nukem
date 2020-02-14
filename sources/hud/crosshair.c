/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   crosshair.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/26 17:47:45 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 11:39:36 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		hud_show_crosshair(t_param *p)
{
	int		i;
	int		size;

	size = 8;
	i = 1;
	while (++i < size)
		umlx_putpixel(p->mlx->render, p->engine_settings->win_width / 2 + i,
			p->engine_settings->win_height / 2, 0xff0000);
	i = 1;
	while (++i < size)
		umlx_putpixel(p->mlx->render, p->engine_settings->win_width / 2 - i,
			p->engine_settings->win_height / 2, 0xff0000);
	i = 1;
	while (++i < size)
		umlx_putpixel(p->mlx->render, p->engine_settings->win_width / 2,
			p->engine_settings->win_height / 2 + i, 0xff0000);
	i = 1;
	while (++i < size)
		umlx_putpixel(p->mlx->render, p->engine_settings->win_width / 2,
			p->engine_settings->win_height / 2 - i, 0xff0000);
}
