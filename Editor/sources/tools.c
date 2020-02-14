/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/05 16:28:47 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		display_tools(t_param *p)
{
	mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr,
	p->tex[2].ptr, 100, HEIGHT - 100);
	mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr,
	p->tex[3].ptr, 50, HEIGHT - 100);
	mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr,
	p->tex[4].ptr, 150, HEIGHT - 100);
	mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr,
	p->tex[5].ptr, 0, HEIGHT - 100);
	mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr,
	p->tex[6].ptr, 0, HEIGHT - 50);
	mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr,
	p->tex[7].ptr, 50, HEIGHT - 50);
	display_img(p->mlx->win2, p->tex[21],
	(t_fvec2d){100, HEIGHT - 50}, (t_fvec2d){50, 50});
	display_img(p->mlx->win2, p->tex[22],
	(t_fvec2d){150, HEIGHT - 50}, (t_fvec2d){50, 50});
}

void		square_ui(t_param *p, t_v v, t_v s)
{
	trace(p->mlx->win2, (t_v){v.x, v.y}, (t_v){v.x + s.x, v.y}, 0xFF0000);
	trace(p->mlx->win2, (t_v){v.x, v.y}, (t_v){v.x, v.y + s.y}, 0xFF0000);
	trace(p->mlx->win2, (t_v){v.x, v.y + s.y},
	(t_v){v.x + s.x + 1, v.y + s.y}, 0xFF0000);
	trace(p->mlx->win2, (t_v){v.x + s.x, v.y},
	(t_v){v.x + s.x, v.y + s.y}, 0xFF0000);
}

void		set_transparence(t_param *p)
{
	int		i;
	int		j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			umlx_putpixel(p->mlx->win2, j, i, 0xFF000000);
	}
}

void		selec_tool(t_param *p)
{
	set_transparence(p);
	if (p->tool == 0)
		square_ui(p, (t_v){0, HEIGHT - 100}, (t_v){50, 49});
	else if (p->tool == 1)
		square_ui(p, (t_v){50, HEIGHT - 100}, (t_v){50, 49});
	else if (p->tool == 2)
		square_ui(p, (t_v){100, HEIGHT - 100}, (t_v){50, 49});
	else if (p->tool == 3)
		square_ui(p, (t_v){149, HEIGHT - 100}, (t_v){50, 49});
}
