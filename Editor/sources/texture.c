/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   texture.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 14:29:55 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void		header_map(t_param *p, int f)
{
	ft_putstr_fd("#TEXTURE ./assets/comp.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/brick.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/nuke.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/wall.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/wall1.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/wall2.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/wall3.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/iron.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/skulls.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/octopus.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/menu_back.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/menu_play.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/menu_editor.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/menu_quit.xpm\n", f);
	ft_putstr_fd("#TEXTURE ./assets/death.xpm\n", f);
	put_player(p, f);
}

void		modif_tex(t_param *p, int tex)
{
	t_wall		*tmp;

	if (p->w)
	{
		tmp = p->w;
		while (tmp)
		{
			if (tmp->state == 2)
			{
				tmp->co = 0;
				tmp->tex = tex;
			}
			tmp = tmp->next;
		}
	}
}

void		pick_tex(t_param *p)
{
	if (p->kevent.mouse_1)
	{
		if (touch_pixel(p, (t_v){550, HEIGHT - 50}, 50, 50))
			modif_tex(p, 0);
		if (touch_pixel(p, (t_v){650, HEIGHT - 50}, 50, 50))
			modif_tex(p, 1);
		if (touch_pixel(p, (t_v){750, HEIGHT - 50}, 50, 50))
			modif_tex(p, 2);
		if (touch_pixel(p, (t_v){850, HEIGHT - 50}, 50, 50))
			modif_tex(p, 3);
		if (touch_pixel(p, (t_v){950, HEIGHT - 50}, 50, 50))
			modif_tex(p, 4);
		if (touch_pixel(p, (t_v){1050, HEIGHT - 50}, 50, 50))
			modif_tex(p, 5);
		if (touch_pixel(p, (t_v){1150, HEIGHT - 50}, 50, 50))
			modif_tex(p, 6);
		if (touch_pixel(p, (t_v){1250, HEIGHT - 50}, 50, 50))
			modif_tex(p, 7);
		if (touch_pixel(p, (t_v){1350, HEIGHT - 50}, 50, 50))
			modif_tex(p, 8);
		if (touch_pixel(p, (t_v){1450, HEIGHT - 50}, 50, 50))
			modif_tex(p, 9);
	}
}

void		display_tex(t_param *p)
{
	if (walls_selected(p))
	{
		display_img(p->mlx->win2, p->tex[11], (t_fvec2d){500, HEIGHT - 100},
		(t_fvec2d){100, 100});
		display_img(p->mlx->win2, p->tex[12], (t_fvec2d){600, HEIGHT - 100},
		(t_fvec2d){100, 100});
		display_img(p->mlx->win2, p->tex[13], (t_fvec2d){700, HEIGHT - 100},
		(t_fvec2d){100, 100});
		display_img(p->mlx->win2, p->tex[14], (t_fvec2d){800, HEIGHT - 100},
		(t_fvec2d){100, 100});
		display_img(p->mlx->win2, p->tex[15], (t_fvec2d){900, HEIGHT - 100},
		(t_fvec2d){100, 100});
		display_img(p->mlx->win2, p->tex[16], (t_fvec2d){1000, HEIGHT - 100},
		(t_fvec2d){100, 100});
		display_img(p->mlx->win2, p->tex[17], (t_fvec2d){1100, HEIGHT - 100},
		(t_fvec2d){100, 100});
		display_img(p->mlx->win2, p->tex[23], (t_fvec2d){1200, HEIGHT - 100},
		(t_fvec2d){100, 100});
		display_img(p->mlx->win2, p->tex[24], (t_fvec2d){1300, HEIGHT - 100},
		(t_fvec2d){100, 100});
		display_img(p->mlx->win2, p->tex[25], (t_fvec2d){1400, HEIGHT - 100},
		(t_fvec2d){100, 100});
		pick_tex(p);
	}
}
