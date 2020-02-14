/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   projection.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 10:48:19 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 15:44:31 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static t_vec	proj_near(t_vec u, t_vec v)
{
	t_line	l;
	float	t;

	l = line_create_points(u, v);
	t = (0.1 - l.z.o) / l.z.u;
	return ((t_vec){l.x.o + l.x.u * t, l.y.o + l.y.u * t, 0.1});
}

static t_real	proj_2d(t_vec u, t_engine_settings *settings)
{
	t_real	r;
	float	z;

	z = 1 / u.z;
	r.x = u.x * z * settings->ratio_fov_h + settings->half_width;
	r.y = u.y * z * settings->ratio_fov_v + settings->half_height;
	return (r);
}

static void		store_projection(t_polygon *p, t_engine_settings *settings,
	t_vec u)
{
	t_real	v;

	if (!u.z)
		ft_error("Allo proj erreur\n");
	v = proj_2d(u, settings);
	p->proj.pt[p->proj.nb] = v;
	p->proj.pt_delim[p->proj.nb] = v;
	p->proj.pt_tmp[p->proj.nb] = v;
	p->proj.nb_delim++;
	p->proj.nb++;
	p->proj.nb_tmp++;
	if (v.y < p->ymin)
		p->ymin = v.y;
	if (v.y > p->ymax)
		p->ymax = v.y;
	if (v.x < p->xmin)
		p->xmin = v.x;
	if (v.x > p->xmax)
		p->xmax = v.x;
}

void			proj3d_to_2d_array(t_engine_settings *settings, t_polygon *w)
{
	unsigned int	i;
	t_vec			next;
	t_vec			current;

	w->proj.nb_delim = 0;
	w->proj.nb_tmp = 0;
	w->proj.nb = 0;
	i = -1;
	while (++i < w->nb_points)
	{
		next = (i < w->nb_points - 1) ? w->tmp_points[i + 1] : w->tmp_points[0];
		current = w->tmp_points[i];
		if (current.z <= 0 && next.z > 0)
			store_projection(w, settings, proj_near(current, next));
		else if (current.z > 0)
		{
			store_projection(w, settings, current);
			if (next.z <= 0)
				store_projection(w, settings, proj_near(current, next));
		}
	}
}
