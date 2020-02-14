/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   create_pw.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/04 17:16:39 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void			wall_connect(t_param *p, t_wall w)
{
	if (wall_check_exist(p, w.p_one, w.p_two))
	{
		p->i_wall++;
		w.tex = 0;
		w.p_three = (t_point){w.p_two.i, w.p_two.x, w.p_two.y,
		-25, p->lay, 0, NULL};
		w.p_four = (t_point){w.p_one.i, w.p_one.x, w.p_one.y,
		-25, p->lay, 0, NULL};
		w.i = p->i_wall;
		w.co = 0;
		wall_pushback(&p->w, w, p);
		p->kevent.mouse_3 = 0;
	}
}

void			point_create(t_param *p)
{
	if (!all_t_p(p, &p->p, 25) && !(all_touch_wall(p, 25)))
	{
		pushback(&p->p, p);
		p->i_point++;
	}
}

static void		point_wall_bis(t_param *p)
{
	point_create(p);
	p->walltool.w.p_two = get_last(p);
	wall_connect(p, p->walltool.w);
	p->walltool.w.p_one = p->walltool.w.p_two;
	p->walltool.nb = 1;
	p->kevent.mouse_1 = 0;
}

static void		point_wall_tre(t_param *p)
{
	trace(p->mlx->render, (t_v){p->walltool.w.p_one.x, p->walltool.w.p_one.y},
	(t_v){p->kevent.mouse_x, p->kevent.mouse_y}, 0xCCCCCC);
	fillcircle(p, (t_v){p->kevent.mouse_x, p->kevent.mouse_y}, 5, 0xFFCCFF);
}

void			point_wall(t_param *p)
{
	if (p->kevent.mouse_1 && p->walltool.nb == 0 && !all_t_p(p, &p->p, 5))
	{
		point_create(p);
		p->walltool.w.p_one = get_last(p);
		p->walltool.nb++;
		p->kevent.mouse_1 = 0;
	}
	else if (p->kevent.mouse_1 && p->walltool.nb == 0 && all_t_p(p, &p->p, 5))
	{
		p->walltool.w.p_one = *(which_mouse_point(p, 5));
		p->walltool.nb++;
		p->kevent.mouse_1 = 0;
	}
	else if (p->kevent.mouse_1 && p->walltool.nb == 1 && all_t_p(p, &p->p, 5))
	{
		p->walltool.w.p_two = *(which_mouse_point(p, 5));
		wall_connect(p, p->walltool.w);
		p->walltool.w.p_one = p->walltool.w.p_two;
		p->kevent.mouse_1 = 0;
		p->walltool.nb = 1;
	}
	else if (p->kevent.mouse_1 && p->walltool.nb == 1)
		point_wall_bis(p);
	if (p->kevent.mouse_2 && p->walltool.nb == 1)
		point_wall_tre(p);
}
