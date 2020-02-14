/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   in_polygon.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 10:17:01 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int				inter_poly_fix(t_polygon *poly, t_vec p)
{
	t_equ_2var_deg1			equ1;
	t_equ_2var_deg1			equ2;
	t_sys_sol_2var_deg1		res;

	p = vec_sub(p, poly->fix_o);
	equ1.a_x = poly->fix_scale_u;
	equ1.a_y = poly->fix_scale_uv;
	equ1.b = -vec_scale_product(p, poly->fix_u);
	equ2.a_x = poly->fix_scale_uv;
	equ2.a_y = poly->fix_scale_v;
	equ2.b = -vec_scale_product(p, poly->fix_v);
	if (!sys_solve_2equ_2var_deg1(equ1, equ2, &res))
		return (0);
	if (poly->nb_points == 3)
		return (res.x >= 0 && res.y >= 0 && res.x + res.y < 1);
	return (res.x >= 0 && res.y >= 0 && res.x < 1 && res.y < 1);
}

t_real			triangulation_get_tex(t_vec pt, t_vec a, t_vec b, t_vec c)
{
	t_equ_2var_deg1			equ1;
	t_equ_2var_deg1			equ2;
	t_sys_sol_2var_deg1		res;
	t_vec					u;
	t_vec					v;

	pt = vec_sub(pt, a);
	u = vec_sub(b, a);
	v = vec_sub(c, a);
	equ1 = (t_equ_2var_deg1)
	{
		.a_x = vec_scale_product(u, u),
		.a_y = vec_scale_product(u, v),
		.b = -vec_scale_product(pt, u)
	};
	equ2 = (t_equ_2var_deg1)
	{
		.a_x = vec_scale_product(u, v),
		.a_y = vec_scale_product(v, v),
		.b = -vec_scale_product(pt, v)
	};
	if (!sys_solve_2equ_2var_deg1(equ1, equ2, &res))
		return ((t_real){-1, -1});
	return ((t_real){res.x, res.y});
}

int				in_triangle_tmp(t_vec pt, t_vec a, t_vec b, t_vec c)
{
	t_equ_2var_deg1			equ1;
	t_equ_2var_deg1			equ2;
	t_sys_sol_2var_deg1		res;
	t_vec					u;
	t_vec					v;

	pt = vec_sub(pt, a);
	u = vec_sub(b, a);
	v = vec_sub(c, a);
	equ1 = (t_equ_2var_deg1)
	{
		.a_x = vec_scale_product(u, u),
		.a_y = vec_scale_product(u, v),
		.b = -vec_scale_product(pt, u)
	};
	equ2 = (t_equ_2var_deg1)
	{
		.a_x = vec_scale_product(u, v),
		.a_y = vec_scale_product(v, v),
		.b = -vec_scale_product(pt, v)
	};
	if (!sys_solve_2equ_2var_deg1(equ1, equ2, &res))
		return (0);
	return (res.x > 0 && res.y > 0 && res.x + res.y < 1);
}

int				inter_poly(t_polygon *poly, t_vec p, t_cplx *result)
{
	t_equ_2var_deg1			equ1;
	t_equ_2var_deg1			equ2;
	t_sys_sol_2var_deg1		res;

	p = vec_sub(p, poly->o);
	equ1 = (t_equ_2var_deg1)
	{
		.a_x = poly->scale_u,
		.a_y = poly->scale_uv,
		.b = -vec_scale_product(p, poly->u)
	};
	equ2 = (t_equ_2var_deg1)
	{
		.a_x = poly->scale_uv,
		.a_y = poly->scale_v,
		.b = -vec_scale_product(p, poly->v)
	};
	if (!sys_solve_2equ_2var_deg1(equ1, equ2, &res))
		return (0);
	*result = (t_cplx){res.x, res.y};
	if (poly->nb_points == 3)
		return (res.x >= 0 && res.y >= 0 && res.x + res.y < 1);
	return (res.x >= 0 && res.y >= 0 && res.x < 1 && res.y < 1);
}
