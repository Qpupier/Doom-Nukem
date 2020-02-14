/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/20 23:41:47 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 15:29:24 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

static void	start_prerender_init(t_param *p)
{
	ft_putstr("Converting...\n");
	list_to_array(p);
	ft_putstr("Initializing...\n");
	init_polygons(p);
	ft_putstr("Starting game...\n");
	sleep(1);
	make_projectiles(p);
	make_boundingbox(p);
	doom_move(p, p->player.position);
	doom_rotate(p, vec_roty, p->player.roty_vsin, p->player.roty_vcos);
}

static void	start_init(t_param *p)
{
	log_error(p);
	init_sound(p);
	ft_putstr("Loading configuration...\n");
	init_engine_settings(p);
	if (!(p->buffer = malloc(sizeof(t_buffer) * p->engine_settings->hmultw)))
		ft_error("Malloc error");
	if (!(umlx_init(p)))
		free_and_exit(p);
	ray_precompute(p);
	init_struct(p);
}

static int	show_window(t_param *p)
{
	struct rusage usage;

	if (getrusage(RUSAGE_SELF, &usage) == 0)
	{
		if (usage.ru_maxrss >= 3500000000)
		{
			ft_printf("MLX Crash avoided. Exiting\n");
			exit(1);
		}
	}
	else
	{
		ft_printf("Something wrong has happened, game may be unstable.\n");
		sleep(3);
	}
	if (!(p->mlx->win_ptr = mlx_new_window(p->mlx->mlx_ptr,
			p->engine_settings->win_width, p->engine_settings->win_height,
			"Doom Nukem")))
		return (0);
	return (1);
}

static void	dispatch_arguments(int argc, char *argv[], char *file, int *pack)
{
	*pack = 0;
	if (argc >= 2 && ft_strequ(argv[1], "--pack"))
	{
		map_packager(argc, argv);
		exit(1);
	}
	if (argc < 2 || argv[1][0] == '-' || !al_init())
	{
		ft_putstr("usage: ./doom-nukem [--pack] [map_file]\n");
		exit(1);
	}
	if (ft_strnequ(".pack", argv[1] + (ft_strlen(argv[1]) - 5), 5))
	{
		file_extract(argv[1], "/tmp/doom-nukem/");
		*pack = 1;
		get_file_at_root(file);
	}
	else
		ft_strcpy(file, argv[1]);
	if (!(fileexists(file)))
	{
		ft_printf("%s does not exists.\n", file);
		exit(1);
	}
}

int			main(int argc, char *argv[])
{
	t_param		*p;
	t_error		err;
	int			pack;
	char		file[NAME_MAX];

	ft_putstr("\033[2J");
	dispatch_arguments(argc, argv, file, &pack);
	if (!(p = malloc(sizeof(t_param))))
		ft_error("Malloc error");
	pack ? p->pstate |= PACK_FILE_OPENNED : 0;
	start_init(p);
	pack ? p->pstate |= PACK_FILE_OPENNED : 0;
	err = 0;
	ft_putstr("Loading map...\n");
	if ((err = map_parser(p, file)) != E_SUCCESS)
	{
		ft_putstr("Error parsing map.\n");
		free(p);
		exit(1);
	}
	start_prerender_init(p);
	show_window(p);
	umlx_hooks(p);
	return (1);
}
