/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tex.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/14 08:32:38 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static int			is_convex_check_lines(t_list_polygons *poly, t_line line)
{
	t_list_points	*points;
	t_vec			normal;
	int				left;
	int				right;
	float			side;

	normal = vec_normalize(vec_cross_product(line_vec_dir(line),
		vec_cross_product(
			vec_sub(poly->points->next->point, poly->points->point),
			vec_sub(poly->points->next->next->point, poly->points->point))));
	left = 0;
	right = 0;
	points = poly->points;
	while (points)
	{
		if ((side = vec_scale_product(normal,
			vec_sub(points->point, line_point(line)))) < 0.0000001)
			left++;
		else if (side > 0.0000001)
			right++;
		points = points->next;
	}
	return (!left || !right);
}

static int			is_convex(t_list_polygons *poly)
{
	t_list_points	*points;
	int				convex;
	t_line			line;

	points = poly->points;
	convex = 1;
	while (convex && points)
	{
		line = line_create_points(points->point, points->next ?
			points->next->point : poly->points->point);
		convex = is_convex_check_lines(poly, line);
		points = points->next;
	}
	return (convex);
}

void				find_lines(t_list_polygons *poly, t_vec *points)
{
	t_line				line[4];
	t_vec				per;

	line[0] = find_line1(poly->nb_points, points, &per);
	line[1] = find_line2(poly->nb_points, points, line[0],
													vec_mult_float(per, -1));
	line[2] = find_line3(poly->nb_points, points, line[0]);
	line[3] = find_line2(poly->nb_points, points, line[2],
									vec_mult_float(line_vec_dir(line[0]), -1));
	line_inter_line(line[0], line[2], &poly->tex[0]);
	line_inter_line(line[0], line[3], &poly->tex[1]);
	line_inter_line(line[1], line[3], &poly->tex[2]);
	line_inter_line(line[1], line[2], &poly->tex[3]);
	if (is_convex(poly))
		poly->options |= IS_CONVEX;
}

void				make_tex_tri(t_list_polygons *poly)
{
	t_vec		vt[3];
	t_mlx_img2	tex;

	if (!(poly->options & HAS_TEXTURE) || !poly->vt)
		return ;
	vt[0] = poly->vt->point;
	vt[1] = poly->vt->next->point;
	vt[2] = poly->vt->next->next->point;
	tex = (poly->options & HAS_BEEN_TRIANGULATED) ?
		poly->texture : *poly->texture2;
	poly->obj_tex[0] = (t_vec){vt[0].x * tex.width, vt[0].y * tex.height, 0};
	poly->obj_tex[1] = (t_vec){vt[1].x * tex.width, vt[1].y * tex.height, 0};
	poly->obj_tex[2] = (t_vec){vt[2].x * tex.width, vt[2].y * tex.height, 0};
	poly->tex_u = vec_sub(poly->obj_tex[1], poly->obj_tex[0]);
	poly->tex_v = vec_sub(poly->obj_tex[2], poly->obj_tex[0]);
}

void				make_tex(t_list_polygons *poly)
{
	t_list_points		*tmp_points;
	t_vec				points[poly->nb_points];
	int					i;

	if (poly->nb_points < 3)
		ft_error("Something wrong happened\n");
	poly->color = ft_color_rgb_to_int((t_rgb){(30 + rand()) % 255,
		(30 + rand()) % 255, (30 + rand()) % 255, 0});
	i = 0;
	tmp_points = poly->points;
	while (tmp_points)
	{
		points[i] = tmp_points->point;
		i++;
		tmp_points = tmp_points->next;
	}
	if (!(poly->options & IS_BLENDER))
		find_lines(poly, points);
	else
		make_tex_tri(poly);
}
