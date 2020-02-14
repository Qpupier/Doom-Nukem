/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   load_textures.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/02 11:46:59 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	load_texture_from_file(t_param *p, int i, char *file)
{
	if (!(umlx_xpm_to_image(p->mlx->mlx_ptr, &p->tex[i], file)))
		ft_error("Texture not found");
}

static void	load_textures_bis(t_param *p)
{
	load_texture_from_file(p, 10, "./assets/enemy3.xpm");
	load_texture_from_file(p, 11, "./assets/comp.xpm");
	load_texture_from_file(p, 12, "./assets/brick.xpm");
	load_texture_from_file(p, 13, "./assets/nuke.xpm");
	load_texture_from_file(p, 14, "./assets/wall.xpm");
	load_texture_from_file(p, 15, "./assets/wall1.xpm");
	load_texture_from_file(p, 16, "./assets/wall2.xpm");
	load_texture_from_file(p, 17, "./assets/wall3.xpm");
	load_texture_from_file(p, 18, "./assets/ammo.xpm");
	load_texture_from_file(p, 19, "./assets/medikit.xpm");
	load_texture_from_file(p, 20, "./assets/bulb.xpm");
	load_texture_from_file(p, 21, "./assets/save.xpm");
	load_texture_from_file(p, 22, "./assets/action.xpm");
	load_texture_from_file(p, 23, "./assets/iron.xpm");
	load_texture_from_file(p, 24, "./assets/skulls.xpm");
	load_texture_from_file(p, 25, "./assets/octopus.xpm");
}

void		load_textures(t_param *p)
{
	int		nbtex;

	nbtex = 26;
	if (!(p->tex = (t_mlx_img2 *)malloc(sizeof(t_mlx_img2) * nbtex)))
		ft_error("Malloc Error");
	load_texture_from_file(p, 2, "./assets/iconwall.xpm");
	load_texture_from_file(p, 3, "./assets/icondot.xpm");
	load_texture_from_file(p, 4, "./assets/iconsquare.xpm");
	load_texture_from_file(p, 5, "./assets/iconmouse.xpm");
	load_texture_from_file(p, 6, "./assets/iconeraser.xpm");
	load_texture_from_file(p, 7, "./assets/icondelete.xpm");
	load_texture_from_file(p, 8, "./assets/enemy1.xpm");
	load_texture_from_file(p, 9, "./assets/enemy2.xpm");
	load_textures_bis(p);
}
