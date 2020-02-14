/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gravity_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/01 12:42:03 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int					ray_inter_plane(t_vec o, t_vec d, t_plane p, t_vec *result)
{
	float	d_l;
	float	tmp;
	float	t;

	tmp = p.a * d.x + p.b * d.y + p.c * d.z;
	if (!tmp)
		return (0);
	t = -(p.a * o.x + p.b * o.y + p.c * o.z + p.d) / tmp;
	if (t < 0)
		return (0);
	*result = vec_add((t_vec){o.x, o.y, o.z},
		vec_mult_float((t_vec){d.x, d.y, d.z}, t));
	d_l = vec_scale_product(vec_sub(*result, o), d);
	if (d_l < 0)
		return (0);
	if (!d_l)
		return (2);
	return (1);
}

int					check_under(t_polygon *poly)
{
	t_vec		d;
	t_vec		result;
	float		dis;

	d = (t_vec){0, 1, 0};
	dis = INFINITY;
	make_fixed(poly);
	if (poly->fix_n.y
		&& ((ray_inter_plane((t_vec){0, 0, 0}, d, poly->fix_plane, &result)
			&& inter_poly_fix(poly, result))
		|| (ray_inter_plane((t_vec){1, 0, 0}, d, poly->fix_plane, &result)
			&& inter_poly_fix(poly, result))
		|| (ray_inter_plane((t_vec){0, 0, 1}, d, poly->fix_plane, &result)
			&& inter_poly_fix(poly, result))
		|| (ray_inter_plane((t_vec){1, 0, 1}, d, poly->fix_plane, &result)
			&& inter_poly_fix(poly, result))))
		return (1);
	return (0);
}
