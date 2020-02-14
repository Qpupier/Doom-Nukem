/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_default.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/05 13:35:21 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 22:03:50 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void	init_struct_supl(t_param *p)
{
	p->fps = 60;
	p->player.inventory[0] = -1;
	p->player.inventory[1] = -1;
	p->player.inventory[2] = -1;
	p->player.inventory[3] = -1;
	p->parse_loading_bar = -1;
	p->parse_total_line = 0;
	p->parse_progress = 1;
	p->pstate |= RASTER;
	p->pstate |= M_PAUSE;
}

void		init_struct(t_param *p)
{
	p->player.state = 0;
	p->pstate = 0;
	p->pstate = M_PAUSE;
	p->nb_rooms = 0;
	p->nb_actions = 0;
	p->player.life = 100;
	p->angle = 0;
	p->player.rotx_angle = ft_deg_to_rad(p->angle);
	p->player.rotx_vcos = cos(p->player.rotx_angle);
	p->player.rotx_vsin = sin(p->player.rotx_angle);
	p->player.rotx = p->player.rotx_angle;
	p->keys = 0;
	p->pstate = 0;
	p->frame_prev = init_fps();
	p->frame_curr = p->frame_prev;
	p->room_list = NULL;
	p->room_list = NULL;
	p->tex_objs = NULL;
	init_struct_supl(p);
}

void		init_sound(t_param *p)
{
	int		err;

	p->audio_source = malloc(sizeof(ALuint) * 24);
	alGenSources(24, p->audio_source);
	p->nb_audio = 6;
	err = 0;
	if (!(p->audio = malloc(sizeof(t_audio_sources) * p->nb_audio)))
	{
		free(p);
		exit(0);
	}
	err += al_load_wav(&p->audio[0], get_path(p->pstate, "quack.wav"));
	err += al_load_wav(&p->audio[1], get_path(p->pstate, "ala.wav"));
	err += al_load_wav(&p->audio[2], get_path(p->pstate, "pchht.wav"));
	err += al_load_wav(&p->audio[3], get_path(p->pstate, "boom.wav"));
	err += al_load_wav(&p->audio[4], get_path(p->pstate, "jurassic_park.wav"));
	err += al_load_wav(&p->audio[5], get_path(p->pstate, "cat_meow.wav"));
	if (err != p->nb_audio)
	{
		free(p->audio);
		free(p);
		exit(0);
	}
}
