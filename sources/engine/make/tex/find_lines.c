/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_lines.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 14:02:26 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

t_line		find_line_supl(int nb_points, t_vec *points, t_vec *per,
	t_vec normal)
{
	int		i;
	int		j;
	t_line	line;
	t_vec	tmp;
	int		state;

	state = 1;
	i = -1;
	while (++i < nb_points && (j = -1) && state)
		while (++j < nb_points && state)
		{
			j = j == nb_points ? 0 : j;
			line = line_create_points(points[i], points[j]);
			if (i != j && ((i == (nb_points - 1) && j != 0) || i + 1 != j)
				&& line_check(line, nb_points, points,
					(tmp = vec_cross_product(normal, line_vec_dir(line)))))
			{
				*per = tmp;
				state = 0;
			}
		}
	if (state)
		ft_error(COLOR_RESET"Wall : First line delimiter error");
	return (state ? line_init() : line);
}

t_line		find_line1(int nb_points, t_vec *points, t_vec *per)
{
	int		i;
	int		j;
	t_line	line;
	t_vec	tmp;
	t_vec	normal;

	normal = vec_cross_product(vec_sub(points[1], points[0]),
		vec_sub(points[2], points[0]));
	i = -1;
	while (++i < nb_points)
	{
		j = i + 1 == nb_points ? 0 : i + 1;
		line = line_create_points(points[i], points[j]);
		if (line_check(line, nb_points, points,
			(tmp = vec_cross_product(normal, line_vec_dir(line)))))
		{
			*per = tmp;
			return (line);
		}
	}
	return (find_line_supl(nb_points, points, per, normal));
}

t_line		find_line2(int nb_points, t_vec *points, t_line l, t_vec per)
{
	t_line	line;
	int		i;

	i = -1;
	while (++i < nb_points)
		if (!line_equal(l, (line = line_parallel_line_point(l, points[i])))
			&& line_check(line, nb_points, points, per))
			return (line);
	ft_error(COLOR_RESET"Wall : Parallel line delimiter error");
	return (line_init());
}

int			is_vec(t_vec v)
{
	return (v.x || v.y || v.z);
}

t_line		find_line3(int nb_points, t_vec *points, t_line l)
{
	t_line	line;
	int		i;
	t_vec	normal;

	i = 0;
	while (!is_vec((normal =
		vec_cross_product(vec_sub(points[1 + i], points[0 + i]),
			vec_sub(points[2 + i], points[0 + i])))))
		if (i + 3 < nb_points)
			i++;
		else
			ft_error("Vector NULL");
	i = -1;
	while (++i < nb_points)
		if (line_check((line =
			line_perpendicular_line_point_plane(l, points[i], normal)),
				nb_points, points, line_vec_dir(l)))
			return (line);
	ft_error(COLOR_RESET"Wall : Perpendicular line delimiter error");
	return (line_init());
}
