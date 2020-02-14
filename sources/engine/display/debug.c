/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 15:21:36 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:24:56 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	debug_str(t_param *p)
{
	char			*str;

	str = ft_itoa(p->poly_count);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 0, 40,
												0xffffff, "polygon rendered: ");
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 200, 40, 0xffffff, str);
	ft_strdel(&str);
	str = ft_itoa(p->poly_culled);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 0, 60, 0xffffff,
															"polygon culled: ");
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 200, 60, 0xffffff, str);
	ft_strdel(&str);
	str = ft_itoa(p->total_polygons);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 0, 80, 0xffffff,
															"polygon total: ");
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 200, 80, 0xffffff, str);
	ft_strdel(&str);
}
