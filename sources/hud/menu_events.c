/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   menu_events.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 15:17:13 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 11:39:10 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static int		touch_pixel(int x, int y, t_real v, t_real size)
{
	return (x < v.x + size.x && x > v.x && y < v.y + size.y && y > v.y);
}

static void		menu_exit(t_param *p, t_real size, int x, int y)
{
	if (touch_pixel(x, y, (t_real)
	{
		(p->engine_settings->win_width * .5) - size.x * .5,
		(p->engine_settings->win_height * .5) + size.y * .5
	}, size))
	{
		free_and_exit(p);
	}
}

static void		menu_play(t_param *p, t_real size, int x, int y)
{
	if (touch_pixel(x, y, (t_real)
	{
		(p->engine_settings->win_width * .5) - size.x * .5,
		(p->engine_settings->win_height * .5) - size.y * 1.5
	}, size))
	{
		p->pstate ^= M_PAUSE;
		mlx_mouse_move(p->mlx->win_ptr,
			p->engine_settings->win_width * 0.5,
			p->engine_settings->win_height * 0.5);
		mlx_mouse_hide();
	}
}

static void		menu_editor(t_param *p, t_real size, int x, int y)
{
	pid_t		pid;
	char		*opt[2];

	if (touch_pixel(x, y, (t_real)
	{
		(p->engine_settings->win_width * .5) - size.x * .5,
		(p->engine_settings->win_height * .5) - size.y * .5
	}, size))
	{
		if (!fileexists("./DoomMapEditor"))
			return ;
		pid = fork();
		if (pid == 0)
		{
			opt[0] = "./DoomMapEditor";
			opt[1] = 0;
			if (execv("./DoomMapEditor", opt) == -1)
				return ;
		}
	}
}

void			hud_menu_event_mouse(t_param *p, int k, int x, int y)
{
	t_real		size;

	if (!(p->pstate & M_PAUSE) || k != 1)
		return ;
	size.x = (p->engine_settings->win_width - 700) * .5;
	size.y = size.x / 2.8;
	menu_play(p, size, x, y);
	menu_exit(p, size, x, y);
	menu_editor(p, size, x, y);
}
