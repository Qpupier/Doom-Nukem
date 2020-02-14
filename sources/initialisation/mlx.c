/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mlx.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/12 10:36:19 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 17:36:52 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		umlx_hooks(t_param *p)
{
	mlx_mouse_move(p->mlx->win_ptr, (p->engine_settings->win_width * 0.5),
		(p->engine_settings->win_height * 0.5));
	mlx_mouse_hide();
	mlx_hook(p->mlx->win_ptr, 3, 0, ev_keyrelease, p);
	mlx_hook(p->mlx->win_ptr, 2, 0, ev_keypress, p);
	mlx_hook(p->mlx->win_ptr, 6, 0, mouse_movement, p);
	mlx_hook(p->mlx->win_ptr, 5, 0, ev_mousepress, p);
	mlx_hook(p->mlx->win_ptr, 17, 0, free_and_exit, p);
	mlx_loop_hook(p->mlx->mlx_ptr, &loop, p);
	mlx_loop(p->mlx->mlx_ptr);
}

short int	umlx_init(t_param *p)
{
	if (!(p->mlx = malloc(sizeof(t_mlx))))
		return (0);
	if (!(p->mlx->mlx_ptr = mlx_init()))
		return (0);
	if (!(umlx_create_image(p->mlx->mlx_ptr, &p->mlx->win2,
			p->engine_settings->width, p->engine_settings->height)))
		return (0);
	if (!(umlx_create_image(p->mlx->mlx_ptr, &p->mlx->render,
			p->engine_settings->win_width, p->engine_settings->win_height)))
		return (0);
	return (1);
}
