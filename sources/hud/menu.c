/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   menu.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 14:30:37 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 11:13:17 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		menu_background(t_param *p)
{
	display_img(p->mlx->render, p->textures[p->nb_textures - 5],
		(t_real){0, 0},
		(t_real)
		{
			p->engine_settings->win_width,
			p->engine_settings->win_height
		});
}

static void		menu_play(t_param *p, t_real size)
{
	display_img(p->mlx->render, p->textures[p->nb_textures - 4],
		(t_real)
		{
			(p->engine_settings->win_width * .5) - size.x * .5,
			(p->engine_settings->win_height * .5) - size.y * 1.5
		}, size);
}

static void		menu_editor(t_param *p, t_real size)
{
	display_img(p->mlx->render, p->textures[p->nb_textures - 3],
		(t_real)
		{
			(p->engine_settings->win_width * .5) - size.x * .5,
			(p->engine_settings->win_height * .5) - size.y * .5
		}, size);
}

static void		menu_quit(t_param *p, t_real size)
{
	display_img(p->mlx->render, p->textures[p->nb_textures - 2],
	(t_real)
	{
		(p->engine_settings->win_width * .5) - size.x * .5,
		(p->engine_settings->win_height * .5) + size.y * .5
	}, size);
}

int				hud_menu(t_param *p)
{
	t_real		size;

	if (p->nb_textures < 4)
		return (0);
	size.x = (p->engine_settings->win_width - 700) * .5;
	size.y = size.x / 2.8;
	menu_background(p);
	menu_play(p, size);
	menu_editor(p, size);
	menu_quit(p, size);
	mlx_mouse_show();
	return (1);
}
