/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/20 23:41:47 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 21:22:06 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"
#include <stdio.h>
#include <sys/time.h>

void		loop_extend(t_param *p)
{
	editor_background(p);
	editor_ui(p);
	tool_one(p);
	tool_two(p);
	all_touch_wall(p, 5);
	delete_events(p);
	tweak_tool_display(p);
	tweak_high_obj(p);
	place_character(p);
	selec_mouse(p);
	wall_set_connect(p);
	change_display(p);
	change_tool(p);
	change_layer(p);
	if (p->kevent.s && p->r)
		create_file(p);
	display_obj(p);
	selec_tool(p);
	pick_mouse(p);
}

int			loop(t_param *p)
{
	loop_extend(p);
	mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr,
	p->mlx->render.ptr, 0, 0);
	display_tools(p);
	display_enemies(p);
	display_tex(p);
	pick_img(p);
	mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr,
	p->mlx->win2.ptr, 0, 0);
	display_obj_info(p);
	display_chara_info(p);
	trace_rooms_nb(p);
	add_action(p);
	display_point_info(p);
	return (1);
}

int			ev_quit(t_param *p)
{
	mlx_clear_window(p->mlx->mlx_ptr, p->mlx->win_ptr);
	mlx_destroy_window(p->mlx->mlx_ptr, p->mlx->win_ptr);
	exit(1);
}

void		hook_mlx(t_param *p)
{
	mlx_hook(p->mlx->win_ptr, 2, 0, ev_keypress, p);
	mlx_hook(p->mlx->win_ptr, 3, 0, ev_keyrelease, p);
	mlx_hook(p->mlx->win_ptr, 4, 0, ev_mousepress, p);
	mlx_hook(p->mlx->win_ptr, 5, 0, ev_mouserelease, p);
	mlx_hook(p->mlx->win_ptr, 6, 0, ev_mousemove, p);
	mlx_hook(p->mlx->win_ptr, 17, 0, ev_quit, p);
}

int			main(void)
{
	t_param		*p;

	if (!(p = malloc(sizeof(t_param))))
		ft_error("Malloc error");
	if (!(p->mlx = malloc(sizeof(t_mlx))))
		ft_error("Malloc error");
	p->p = NULL;
	p->w = NULL;
	p->r = NULL;
	p->o = NULL;
	p->mlx->mlx_ptr = mlx_init();
	p->mlx->win_ptr = mlx_new_window(p->mlx->mlx_ptr, WIDTH, HEIGHT, "Editor");
	load_textures(p);
	umlx_create_image(p->mlx->mlx_ptr, &p->mlx->render, WIDTH, HEIGHT);
	umlx_create_image(p->mlx->mlx_ptr, &p->mlx->win2, WIDTH, HEIGHT);
	init_input(p);
	init_tools(p);
	hook_mlx(p);
	mlx_loop_hook(p->mlx->mlx_ptr, &loop, p);
	mlx_loop(p->mlx->mlx_ptr);
	return (0);
}
