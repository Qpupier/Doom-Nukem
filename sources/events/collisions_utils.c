/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   collisions_utils.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/01 10:26:20 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 10:26:33 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

t_vec	proj_point_poly(t_vec point, t_polygon *poly, float *dist)
{
	t_vec	result;
	int		i;
	float	tmp_dist;
	t_vec	tmp_result;

	result = proj_point_plane(point, poly->fix_plane, dist);
	if (!inter_poly_fix(poly, result) && (i = -1))
		while (++i < poly->nb_points)
		{
			tmp_result = proj_point_seg(point, (t_seg){poly->points[i], 	\
					poly->points[i + 1 == poly->nb_points ? 0 : i + 1]}, 	\
					&tmp_dist);
			if (!i || tmp_dist < *dist)
			{
				result = tmp_result;
				*dist = tmp_dist;
			}
		}
	return (result);
}

int		inter_seg_poly(t_seg s, t_polygon *poly, t_vec *result)
{
	t_inter_seg_plane	tmp;

	if (inter_seg_plane(s, poly->fix_plane, &tmp) 	\
			&& inter_poly_fix(poly, tmp.result))
	{
		*result = tmp.result;
		return (1);
	}
	return (0);
}
