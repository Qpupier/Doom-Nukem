/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 17:47:26 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 21:10:29 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			reset_zbuffer(t_param *p)
{
	int	i;

	i = -1;
	while (++i < p->engine_settings->hmultw)
	{
		p->buffer[i].dis = INFINITY;
		p->buffer[i].ptr_poly = NULL;
		p->buffer[i].ptr_room = NULL;
		p->buffer[i].color = 0x000000;
	}
}

static int		menu_and_death(t_param *p)
{
	if ((p->pstate & M_PAUSE))
	{
		hud_menu(p);
		mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr, 	\
				p->mlx->render.ptr, 0, 0);
		return (0);
	}
	if (hud_player_dead(p))
		return (0);
	return (1);
}

static void		process(t_param *p)
{
	reset_zbuffer(p);
	process_gravity(p);
	process_keys(p);
	handle_lift(p);
	make_boundingbox(p);
	apply_action(p);
	multithread_zone(p);
	start_multithread(p);
	hud_inflict_damages(p);
	hud_fadein_fadeout(p);
}

static void		hud_show(t_param *p)
{
	hud_show_inventory(p);
	hud_show_life(p);
	hud_show_crosshair(p);
}

int				loop(t_param *p)
{
	long long int	mseconds;
	int				index;
	static int		init = 0;

	if (!init)
	{
		process(p);
		init = 1;
	}
	mseconds = init_fps();
	p->frame_prev = p->frame_curr;
	p->frame_curr = mseconds;
	if (!(menu_and_death(p)))
		return (0);
	process(p);
	index = -1;
	while ((p->pstate & WIREFRAME) && ++index < p->total_polygons)
		show_wireframe(p, p->lst_polygons[index]);
	upscale(p->engine_settings, p->mlx->render, p->mlx->win2);
	hud_show(p);
	mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr,
		p->mlx->render.ptr, 0, 0);
	show_fps(p, mseconds);
	hud_show_ammo(p);
	return (1);
}
