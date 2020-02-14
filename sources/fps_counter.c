/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fps_counter.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/07 12:30:35 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 10:52:13 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

long long int			init_fps(void)
{
	struct timeval	tstart;

	gettimeofday(&tstart, NULL);
	return (tstart.tv_sec * 1000LL + tstart.tv_usec / 1000);
}

int						show_fps(t_param *p, long long int mseconds)
{
	struct timeval	tend;
	int				fps;
	char			*tmp;

	gettimeofday(&tend, NULL);
	mseconds = mseconds - (tend.tv_sec * 1000LL + tend.tv_usec / 1000);
	if (llabs(mseconds))
		fps = 1000 / llabs(mseconds);
	else
		fps = 9999;
	p->fps = fps;
	tmp = ft_itoa(fps);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 50, 0, 0xffffff, tmp);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 0, 0, 0xffffff, "FPS:");
	fps = llabs(mseconds);
	ft_strdel(&tmp);
	tmp = ft_itoa(fps);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 50, 20, 0xffffff, tmp);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, 0, 20, 0xffffff, "MS :");
	ft_strdel(&tmp);
	return (llabs(mseconds));
}

int						perf_counter(long long int mseconds)
{
	struct timeval	tend;

	gettimeofday(&tend, NULL);
	mseconds = mseconds - (tend.tv_sec * 1000LL + tend.tv_usec / 1000);
	return (llabs(mseconds));
}
