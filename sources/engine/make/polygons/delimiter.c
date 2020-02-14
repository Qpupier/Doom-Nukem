/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delimiter.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 11:08:31 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 14:26:38 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void				expand_and_clamp_delimitation(t_engine_settings *settings,
	t_polygon *poly)
{
	poly->xmin -= 2;
	poly->ymin -= 2;
	poly->xmax += 2;
	poly->ymax += 2;
	if (poly->xmin < 0)
		poly->xmin = 0;
	if (poly->ymin < 0)
		poly->ymin = 0;
	if (poly->xmax >= settings->width)
		poly->xmax = settings->width - 1;
	if (poly->ymax >= settings->height)
		poly->ymax = settings->height - 1;
}

void				create_delimitation(t_engine_settings *settings,
	t_polygon *poly)
{
	unsigned int	i;

	if (poly->xmin < 0 || poly->xmax >= settings->width
					|| poly->ymin < 0 || poly->ymax >= settings->height)
	{
		i = -1;
		clamp_to_window(settings, poly);
		poly->ymax = 0;
		poly->ymin = settings->height - 1;
		poly->xmax = 0;
		poly->xmin = settings->width - 1;
		while (++i < poly->proj.nb_tmp)
		{
			if (poly->proj.pt_tmp[i].y < poly->ymin)
				poly->ymin = poly->proj.pt_tmp[i].y;
			if (poly->proj.pt_tmp[i].y > poly->ymax)
				poly->ymax = poly->proj.pt_tmp[i].y;
			if (poly->proj.pt_tmp[i].x < poly->xmin)
				poly->xmin = poly->proj.pt_tmp[i].x;
			if (poly->proj.pt_tmp[i].x > poly->xmax)
				poly->xmax = poly->proj.pt_tmp[i].x;
		}
	}
	poly->is_visible = 1;
	expand_and_clamp_delimitation(settings, poly);
}
