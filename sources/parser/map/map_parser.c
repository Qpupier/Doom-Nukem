/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_parser.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/12 08:13:45 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 14:33:22 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void	start_parsing(t_param *p, t_list_line *lst, 	\
							t_list_numbers *lst_indexes)
{
	t_list_objects	*objects;
	t_list_lights	*lights;
	t_list_polygons	*walls;

	walls = NULL;
	walls = parse_walls(p, lst, (t_room_index){lst_indexes->n,
					lst_indexes->next ? lst_indexes->next->n : -1});
	objects = parse_objects(p, lst, (t_room_index){lst_indexes->n,
					lst_indexes->next ? lst_indexes->next->n : -1});
	lights = parse_lights(lst, (t_room_index){lst_indexes->n,
					lst_indexes->next ? lst_indexes->next->n : -1});
	parse_sprites(p, lst, &walls, (t_room_index){lst_indexes->n,
					lst_indexes->next ? lst_indexes->next->n : -1});
	room_push(&p->room_list, (t_list_room){objects, walls, lights, NULL});
}

int			parse_room(t_param *p, t_list_line *lst)
{
	t_list_numbers	*indexes;
	t_list_numbers	*tmp_indexes;
	t_list_line		*tmp;
	int				i;

	i = 0;
	indexes = NULL;
	tmp = lst;
	while (tmp && ++i)
	{
		if (ft_strnequ("ROOM ", tmp->line, 5) && show_parseprogress(p))
			lst_push_numbers(&indexes, i);
		tmp = tmp->next;
	}
	i = 0;
	tmp_indexes = indexes;
	while (tmp_indexes)
	{
		start_parsing(p, lst, tmp_indexes);
		tmp_indexes = tmp_indexes->next;
	}
	free_tlst_numbers(&indexes);
	indexes = NULL;
	return (E_SUCCESS);
}

static void	parse(t_param *p, t_list_line *lines)
{
	ft_putstr_rgb("[", 255, 255, 255);
	if (texture_parse(p, lines) == E_ERROR_PARSING_TEXTURE)
	{
		ft_printf("%s]\n%sUnexpected fatal error. Exiting.\n" COLOR_RESET,
			COLOR_RESET, COLOR_RED);
		exit(1);
	}
	parse_player(p, lines);
	parse_room(p, lines);
	parse_actions(p, lines);
	progress_comments(p, lines);
	ft_putstr_rgb("]\n", 255, 255, 255);
	ft_putstr("\e[0m");
}

int			map_parser(t_param *p, const char *file)
{
	int				fd;
	char			*line_tmp;
	t_list_line		*lines;

	lines = NULL;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (E_ERROR_READING_FILE);
	if (read(fd, NULL, 0) < 0)
		return (E_ERROR_READING_FILE);
	while (get_next_line(fd, &line_tmp))
	{
		line_pushback(&lines, line_tmp);
		ft_strdel(&line_tmp);
	}
	ft_strdel(&line_tmp);
	if (!lines || !(p->parse_total_line = t_list_line_count(lines)))
		return (E_ERROR_READING_FILE);
	check_integrity(p->pstate, lines);
	parse(p, lines);
	free_t_list_lines(&lines);
	triangulate_map(p);
	lines = NULL;
	close(fd);
	return (E_SUCCESS);
}
