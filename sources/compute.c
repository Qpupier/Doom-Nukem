/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compute.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/20 18:20:20 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:31:34 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

short int		ray_precompute(t_param *p)
{
	int		i;
	int		j;
	t_vec	ray;

	if (!(p->rays = malloc(sizeof(t_vec *) * p->engine_settings->height)))
		return (E_ERROR_MALLOC);
	j = -1;
	while (++j < p->engine_settings->height)
	{
		i = -1;
		if (!(p->rays[j] = malloc(sizeof(t_vec) * p->engine_settings->width)))
			return (0);
		while (++i < p->engine_settings->width)
		{
			ray.x = ft_deg_to_rad((i - p->engine_settings->width * 0.5) *
				p->engine_settings->deg_fov_h / p->engine_settings->width);
			ray.y = ft_deg_to_rad((j - p->engine_settings->height * 0.5) *
				p->engine_settings->deg_fov_v / p->engine_settings->height);
			ray.z = 1;
			p->rays[j][i] = ray;
		}
	}
	return (E_SUCCESS);
}
