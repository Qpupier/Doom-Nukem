/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   proj_point.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/01 10:17:15 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 23:58:19 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_vec	proj_point_plane(t_vec point, t_plane plane, float *dist)
{
	float	tmp;
	t_vec	result;

	if (!(tmp = plane.a * plane.a + plane.b * plane.b + plane.c * plane.c))
		ft_error("Plane error");
	result = vec_mult_float((t_vec){plane.a, plane.b, plane.c}, 			\
			(-plane.a * point.x - plane.b * point.y - plane.c * point.z 	\
			- plane.d) / tmp);
	*dist = vec_norm(result);
	return (vec_add(point, result));
}

t_vec	proj_point_seg(t_vec p, t_seg s, float *dist)
{
	t_vec	result;
	float	dist1;
	float	dist2;

	result = proj_point_line(p, line_create_points(s.a, s.b), dist);
	if (!point_line_in_seg(result, s))
	{
		dist1 = vec_norm(vec_sub(s.a, p));
		dist2 = vec_norm(vec_sub(s.b, p));
		if (dist1 < dist2)
		{
			*dist = dist1;
			result = s.a;
		}
		else
		{
			*dist = dist2;
			result = s.b;
		}
	}
	return (result);
}

t_vec	proj_point_line(t_vec p, t_line l, float *dist)
{
	t_vec	o;
	t_vec	u;
	float	t;
	t_vec	result;

	o = (t_vec){l.x.o, l.y.o, l.z.o};
	u = (t_vec){l.x.u, l.y.u, l.z.u};
	t = vec_scale_product(vec_sub(p, o), vec_normalize(u));
	result = vec_add(o, vec_mult_float(u, t));
	*dist = vec_norm(vec_sub(result, p));
	return (result);
}
