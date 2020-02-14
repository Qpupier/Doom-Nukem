/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   picktool.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 12:31:46 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		pick_img(t_param *p)
{
	if (p->pick_tool == 0)
		return ;
	if (p->pick_tool == 1)
		square_ui(p, (t_v){200, HEIGHT - 100}, (t_v){50, 99});
	if (p->pick_tool == 2)
		square_ui(p, (t_v){250, HEIGHT - 100}, (t_v){50, 99});
	if (p->pick_tool == 3)
		square_ui(p, (t_v){300, HEIGHT - 100}, (t_v){50, 99});
	if (p->pick_tool == 4)
		square_ui(p, (t_v){400, HEIGHT - 100}, (t_v){70, 99});
	if (p->pick_tool == 5)
		square_ui(p, (t_v){480, HEIGHT - 100}, (t_v){160, 99});
	if (p->pick_tool == 6)
		square_ui(p, (t_v){650, HEIGHT - 100}, (t_v){70, 99});
}

void		display_enemies(t_param *p)
{
	if (!walls_selected(p))
	{
		display_img(p->mlx->win2, p->tex[8], (t_fvec2d){200, HEIGHT - 100},
		(t_fvec2d){100, 50});
		display_img(p->mlx->win2, p->tex[9], (t_fvec2d){250, HEIGHT - 100},
		(t_fvec2d){100, 50});
		display_img(p->mlx->win2, p->tex[10], (t_fvec2d){300, HEIGHT - 100},
		(t_fvec2d){100, 50});
		display_img(p->mlx->win2, p->tex[19], (t_fvec2d){400, HEIGHT - 100},
		(t_fvec2d){100, 70});
		display_img(p->mlx->win2, p->tex[18], (t_fvec2d){480, HEIGHT - 100},
		(t_fvec2d){100, 160});
		display_img(p->mlx->win2, p->tex[20], (t_fvec2d){650, HEIGHT - 100},
		(t_fvec2d){100, 70});
	}
}

void		pick_mouse(t_param *p)
{
	if (p->kevent.mouse_1)
	{
		if (!walls_selected(p))
		{
			if (touch_pixel(p, (t_v){225, HEIGHT - 50}, 25, 50))
				p->pick_tool = 1;
			if (touch_pixel(p, (t_v){275, HEIGHT - 50}, 25, 50))
				p->pick_tool = 2;
			if (touch_pixel(p, (t_v){325, HEIGHT - 50}, 25, 50))
				p->pick_tool = 3;
			if (touch_pixel(p, (t_v){435, HEIGHT - 50}, 35, 50))
				p->pick_tool = 4;
			if (touch_pixel(p, (t_v){560, HEIGHT - 50}, 80, 50))
				p->pick_tool = 5;
			if (touch_pixel(p, (t_v){685, HEIGHT - 50}, 35, 50))
				p->pick_tool = 6;
		}
		else
		{
			p->pick_tool = 0;
		}
	}
}

void		place_obj(t_param *p)
{
	t_obj		o;

	if (p->kevent.mouse_1)
	{
		if (p->pick_tool >= 1 && p->pick_tool <= 3)
			o.type = 1;
		if (p->pick_tool >= 4 && p->pick_tool <= 5)
			o.type = 2;
		if (p->pick_tool == 6)
			o.type = 3;
		o.obj = p->pick_tool;
		o.pos = (t_vec3d){p->kevent.mouse_x, p->kevent.mouse_y, 15};
		o.lay = p->lay;
		o.room = -1;
		obj_pushback(&p->o, &o);
		p->kevent.mouse_1 = 0;
	}
}

void		display_obj(t_param *p)
{
	t_obj		*tmp;

	if (p->o)
	{
		tmp = p->o;
		while (tmp)
		{
			if (tmp->state == 0)
				fillcircle(p, (t_v){tmp->pos.x, tmp->pos.y}, 5, 0xAAFFFA);
			if (tmp->state == 1)
				fillcircle(p, (t_v){tmp->pos.x, tmp->pos.y}, 5, 0xCCFFFF);
			if (tmp->state == 2)
				fillcircle(p, (t_v){tmp->pos.x, tmp->pos.y}, 5, 0x11FFFF);
			tmp = tmp->next;
		}
	}
}
