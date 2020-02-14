/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_inter_line.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 23:08:29 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/23 10:38:20 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	line_inter_line__2(t_line l1, t_line l2, t_vec *result)
{
	t_sys_sol_2var_deg1	s;
	int					stop;

	stop = 0;
	if (!stop && l1.y.u && l2.z.u)
		stop = sys_solve_2equ_2var_deg1(\
				(t_equ_2var_deg1){l1.y.u, -l2.y.u, l1.y.o - l2.y.o}, 	\
				(t_equ_2var_deg1){l1.z.u, -l2.z.u, l1.z.o - l2.z.o}, &s);
	if (!stop && l1.z.u && l2.x.u)
		stop = sys_solve_2equ_2var_deg1(\
				(t_equ_2var_deg1){l1.z.u, -l2.z.u, l1.z.o - l2.z.o}, 	\
				(t_equ_2var_deg1){l1.x.u, -l2.x.u, l1.x.o - l2.x.o}, &s);
	if (!stop && l1.z.u && l2.y.u)
		stop = sys_solve_2equ_2var_deg1(\
				(t_equ_2var_deg1){l1.z.u, -l2.z.u, l1.z.o - l2.z.o}, 	\
				(t_equ_2var_deg1){l1.y.u, -l2.y.u, l1.y.o - l2.y.o}, &s);
	if (stop)
		*result = vec_create(l1.x.o + l1.x.u * s.x, 				\
				l1.y.o + l1.y.u * s.x, l1.z.o + l1.z.u * s.x);
	return (stop);
}

int			line_inter_line(t_line l1, t_line l2, t_vec *result)
{
	t_sys_sol_2var_deg1	s;
	int					stop;

	stop = 0;
	if (l1.x.u && l2.y.u)
		stop = sys_solve_2equ_2var_deg1(\
				(t_equ_2var_deg1){l1.x.u, -l2.x.u, l1.x.o - l2.x.o}, 	\
				(t_equ_2var_deg1){l1.y.u, -l2.y.u, l1.y.o - l2.y.o}, &s);
	if (!stop && l1.x.u && l2.z.u)
		stop = sys_solve_2equ_2var_deg1(\
				(t_equ_2var_deg1){l1.x.u, -l2.x.u, l1.x.o - l2.x.o}, 	\
				(t_equ_2var_deg1){l1.z.u, -l2.z.u, l1.z.o - l2.z.o}, &s);
	if (!stop && l1.y.u && l2.x.u)
		stop = sys_solve_2equ_2var_deg1(\
				(t_equ_2var_deg1){l1.y.u, -l2.y.u, l1.y.o - l2.y.o}, 	\
				(t_equ_2var_deg1){l1.x.u, -l2.x.u, l1.x.o - l2.x.o}, &s);
	if (stop)
		*result = vec_create(l1.x.o + l1.x.u * s.x, 				\
				l1.y.o + l1.y.u * s.x, l1.z.o + l1.z.u * s.x);
	else
		stop = line_inter_line__2(l1, l2, result);
	return (stop);
}
