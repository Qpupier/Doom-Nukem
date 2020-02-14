/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fadeinout.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 15:39:02 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/03 15:39:23 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	hud_inflict_damages(t_param *p)
{
	static float		frame = 0;
	int					i;

	if (!(p->pstate & DAMAGES))
		return ;
	i = -1;
	while (++i < p->engine_settings->hmultw)
		p->mlx->win2.img[i] = color_avg(0xff0000, p->mlx->win2.img[i], frame);
	if (frame >= 1)
	{
		frame = 0;
		(p->pstate & DAMAGES) ? p->pstate ^= DAMAGES : 0;
	}
	else
		frame += 0.05;
}

void	hud_fadein_fadeout(t_param *p)
{
	static float		frame = 0;
	static int			type = 0;
	int					i;

	if (!(p->pstate & FADEINOUT))
		return ;
	i = -1;
	while (++i < p->engine_settings->hmultw)
		p->mlx->win2.img[i] = color_avg(p->mlx->win2.img[i], 0x000000, frame);
	if (type == 0 && frame <= 1)
		frame += 0.05;
	else if (type == 0)
	{
		type = 1;
		frame = 1;
		!(p->pstate & TELEPORTING) ? p->pstate |= TELEPORTING : 0;
	}
	if (type == 1 && frame >= 0)
		frame -= 0.05;
	else if (type == 1)
	{
		frame = 0;
		type = 0;
		(p->pstate & FADEINOUT) ? p->pstate ^= FADEINOUT : 0;
	}
}
