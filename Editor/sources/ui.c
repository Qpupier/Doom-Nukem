/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ui.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/10 10:43:31 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		editor_ui(t_param *p)
{
	int i;

	i = -1;
	while (++i < WIDTH)
		trace(p->mlx->render, (t_v){0 + i, HEIGHT - 100},
		(t_v){0 + i, HEIGHT}, 0x333333);
	trace(p->mlx->render, (t_v){200, HEIGHT - 100},
	(t_v){200, HEIGHT}, 0x191919);
	i = -1;
	while (++i < WIDTH)
		trace(p->mlx->render, (t_v){0 + i, HEIGHT - 130},
		(t_v){0 + i, HEIGHT - 100}, 0x191919);
}

void		editor_background(t_param *p)
{
	int i;

	i = -1;
	while (++i < WIDTH)
		trace(p->mlx->render, (t_v){0 + i, 0},
		(t_v){0 + i, HEIGHT}, 0x2f323b);
}

void		editor_nb(t_param *p)
{
	char		*tmp;

	tmp = ft_itoa(p->i_wall);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 10,
	HEIGHT - 100, 0xffffff, "Wall Number:");
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 175,
	HEIGHT - 100, 0xffffff, tmp);
	ft_strdel(&tmp);
	if (p->tool == 0)
		tmp = "Selector";
	else if (p->tool == 1)
		tmp = "Point";
	else if (p->tool == 2)
		tmp = "Wall";
	else if (p->tool == 3)
		tmp = "Square Selec";
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 10,
	HEIGHT - 80, 0xffffff, "Tool:");
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 75,
	HEIGHT - 80, 0xffffff, tmp);
	tmp = ft_itoa(p->lay);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 10,
	HEIGHT - 65, 0xffffff, "Layer:");
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 175,
	HEIGHT - 65, 0xffffff, tmp);
}
