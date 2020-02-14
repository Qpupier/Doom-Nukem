/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   life.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 15:38:33 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 20:03:10 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		background_life(t_param *p, t_int pos)
{
	trace_line(p->mlx->render, (t_int){pos.x - 1, pos.y},
								(t_int){pos.x + 201, pos.y}, 0x6B0000);
	trace_line(p->mlx->render, (t_int){pos.x - 1, pos.y + 1},
								(t_int){pos.x + 201, pos.y + 1}, 0x6B0000);
	trace_line(p->mlx->render, (t_int){pos.x - 1, pos.y + 2},
								(t_int){pos.x + 201, pos.y + 2}, 0x6B0000);
	trace_line(p->mlx->render, (t_int){pos.x - 1, pos.y + 3},
								(t_int){pos.x + 201, pos.y + 3}, 0x6B0000);
	trace_line(p->mlx->render, (t_int){pos.x - 1, pos.y + 4},
								(t_int){pos.x + 201, pos.y + 4}, 0x6B0000);
}

void			hud_show_life(t_param *p)
{
	t_int	pos;

	pos = (t_int){24, p->engine_settings->win_height - 15};
	background_life(p, pos);
	if (p->player.life <= 0)
		return ;
	trace_line(p->mlx->render, (t_int){pos.x - 1, pos.y},
				(t_int){pos.x + (p->player.life * 2), pos.y}, 0xff0000);
	trace_line(p->mlx->render, (t_int){pos.x - 1, pos.y + 1},
				(t_int){pos.x + (p->player.life * 2), pos.y + 1}, 0xff0000);
	trace_line(p->mlx->render, (t_int){pos.x - 1, pos.y + 2},
				(t_int){pos.x + (p->player.life * 2), pos.y + 2}, 0xff0000);
	trace_line(p->mlx->render, (t_int){pos.x - 1, pos.y + 3},
				(t_int){pos.x + (p->player.life * 2), pos.y + 3}, 0xff0000);
	trace_line(p->mlx->render, (t_int){pos.x - 1, pos.y + 4},
				(t_int){pos.x + (p->player.life * 2), pos.y + 4}, 0xff0000);
}

void			hud_show_ammo(t_param *p)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	tmp = ft_itoa(AMMO - p->nb_projectiles);
	tmp1 = ft_strjoin("AMMO : ", tmp);
	ft_strdel(&tmp);
	tmp = ft_strjoin(tmp1, " / ");
	ft_strdel(&tmp1);
	tmp1 = ft_itoa(AMMO);
	tmp2 = ft_strjoin(tmp, tmp1);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 30, 	\
			p->engine_settings->win_height - 50, 0xFFFFFF, tmp2);
	ft_strdel(&tmp2);
}
