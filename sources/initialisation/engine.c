/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   engine.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/12 10:38:22 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 14:43:40 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static int		precalcs(t_engine_settings *setting)
{
	setting->height = setting->win_height * setting->quality + .5;
	setting->width = setting->win_width * setting->quality + .5;
	setting->half_height = (setting->height * .5);
	setting->half_width = (setting->width * .5);
	setting->rad_fov_h = ft_deg_to_rad(setting->deg_fov_h);
	setting->rad_fov_v = ft_deg_to_rad(setting->deg_fov_v);
	setting->ratio_fov_h = setting->width / setting->rad_fov_h;
	setting->ratio_fov_v = setting->height / setting->rad_fov_v;
	setting->zbuffer_center = setting->half_height
		* setting->width + setting->half_width;
	setting->hmultw = setting->height * setting->width;
	return (1);
}

static void		init_default(t_engine_settings *setting, int type)
{
	if (type == 1)
	{
		setting->win_width = -1;
		setting->win_height = -1;
		setting->quality = -1;
		setting->deg_fov_h = -1;
		setting->deg_fov_v = -1;
		return ;
	}
	setting->win_width = 1920;
	setting->win_height = 1080;
	setting->quality = .5;
	setting->deg_fov_h = 60;
	setting->deg_fov_v = 36;
}

static int		parse_options(t_engine_settings *tmp)
{
	int					fd;
	char				*line;
	int					state;

	state = 0;
	if ((fd = open("./doom-nukem.conf", O_RDONLY)) == -1)
		return (0);
	init_default(tmp, 1);
	while (get_next_line(fd, &line))
	{
		if (ft_strnequ("width", line, 5) && ++state)
			tmp->win_width = ft_atoi(line + 5);
		if (ft_strnequ("height", line, 6) && ++state)
			tmp->win_height = ft_atoi(line + 6);
		if (ft_strnequ("quality", line, 7) && ++state)
			tmp->quality = ft_atoi(line + 7);
		if (ft_strnequ("fov_h", line, 5) && ++state)
			tmp->deg_fov_h = ft_atoi(line + 5);
		if (ft_strnequ("fov_v", line, 5) && ++state)
			tmp->deg_fov_v = ft_atoi(line + 5);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (state);
}

void			init_engine_settings(t_param *p)
{
	t_engine_settings	tmp;

	if (!(p->engine_settings = malloc(sizeof(t_engine_settings))))
		handle_error(p, E_ERROR_MALLOC);
	init_default(p->engine_settings, 0);
	if (!parse_options(&tmp) && precalcs(p->engine_settings))
		return ;
	if ((tmp.win_width >= 800 && tmp.win_height >= 450
		&& floatcmp((float)tmp.win_width / (float)tmp.win_height, 1.7, 0.1)))
	{
		p->engine_settings->win_height = tmp.win_height;
		p->engine_settings->win_width = tmp.win_width;
	}
	if (tmp.deg_fov_h >= 0)
		p->engine_settings->deg_fov_h =
			tmp.deg_fov_h >= 180 ? 180 : tmp.deg_fov_h;
	if (tmp.deg_fov_v >= 0)
		p->engine_settings->deg_fov_v =
			tmp.deg_fov_v >= 180 ? 180 : tmp.deg_fov_v;
	if (tmp.quality >= 10)
		p->engine_settings->quality =
			(tmp.quality >= 100 ? 100 : tmp.quality) / 100;
	precalcs(p->engine_settings);
}
