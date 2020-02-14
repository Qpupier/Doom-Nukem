/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mouse_movements.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 12:03:07 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 21:37:49 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		handle_rotation_x(t_param *p, int y_diff)
{
	if (p->pstate & FLYING)
	{
		p->player.rotx_angle = (y_diff * 0.25);
		p->player.rotx_vcos = cos(ft_deg_to_rad(p->player.rotx_angle));
		p->player.rotx_vsin = sin(ft_deg_to_rad(p->player.rotx_angle));
	}
	else
	{
		p->player.rotx += p->player.roty_angle;
		if (p->angle + y_diff < 70 & p->angle + y_diff > -50)
			p->angle += (y_diff * 0.25);
		p->player.rotx_angle = ft_deg_to_rad(p->angle);
		p->player.rotx_vcos = cos(p->player.rotx_angle);
		p->player.rotx_vsin = sin(p->player.rotx_angle);
	}
}

static void		mouse_vision(int x, int y, struct s_param *p)
{
	int x_diff;
	int y_diff;

	x_diff = (x - (p->engine_settings->win_width * .5)) * .1;
	y_diff = (y - (p->engine_settings->win_height * .5)) * .1;
	if (x_diff == 0 && (x - (p->engine_settings->win_width * .5)) > 0)
		x_diff = 1;
	if (x_diff == 0 && (x - (p->engine_settings->win_width * .5)) < 0)
		x_diff = -1;
	if (y_diff == 0 && (y - (p->engine_settings->win_height * .5)) > 0)
		y_diff = 1;
	if (y_diff == 0 && (y - (p->engine_settings->win_height * .5)) < 0)
		y_diff = -1;
	p->player.roty_angle = -(x_diff * 0.25);
	p->player.roty_vsin = sin(ft_deg_to_rad(-(x_diff * 0.25)));
	p->player.roty_vcos = cos(ft_deg_to_rad(-(x_diff * 0.25)));
	handle_rotation_x(p, y_diff);
}

int				mouse_movement(int x, int y, struct s_param *p)
{
	if (p->player.life <= 0 || p->pstate & M_PAUSE)
		return (0);
	mouse_vision(x, y, p);
	mlx_mouse_move(p->mlx->win_ptr, p->engine_settings->win_width * 0.5,
		p->engine_settings->win_height * 0.5);
	return (0);
}
