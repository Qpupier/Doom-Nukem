/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   integrity_check.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/25 18:14:00 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 14:22:51 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static int			check_one(uint32_t pstate, char *line, int nb_textures)
{
	if (!ft_strncmp("#PLAYER_POSITION ", line, 17))
		return (0);
	else if (!ft_strncmp("#SPRITE ", line, 8))
		return (0);
	else if (!ft_strncmp("##", line, 2))
		return (0);
	else if (!ft_strncmp("#PLAYER_ROTATION ", line, 17))
		return (0);
	else if (!ft_strncmp("#TEXTURE ", line, 9))
		return (check_textures(get_path(pstate, line + 9)));
	else if (!ft_strncmp("ROOM ", line, 5))
		return (check_room(line, nb_textures));
	else if (!ft_strncmp("#ACTION ", line, 8))
		return (0);
	else if (!ft_strncmp("#OBJECT ", line, 8))
		return (check_objects(pstate, line + 8));
	else if (!ft_strncmp("#LIGHT ", line, 7))
		return (check_lights(line + 7));
	else
		return (check_vertices(line, nb_textures));
	(void)nb_textures;
}

static int			start_checker(uint32_t pstate, int nb_textures, 	\
									char *line, int nb_line)
{
	int				ret;

	if ((ret = check_one(pstate, line, nb_textures)))
	{
		ft_putstr("Error on line: ");
		ft_putnbr(nb_line);
		ft_putchar('\n');
		ft_putstr(COLOR_RED "\t");
		ft_putendl(line);
	}
	return (ret);
}

short unsigned int	check_integrity(uint32_t pstate, t_list_line *lines)
{
	t_list_line		*tmp;
	unsigned int	error;
	int				nb_textures;
	int				nb_line;

	nb_line = 1;
	nb_textures = count_textures(lines);
	error = 0;
	tmp = lines;
	while (tmp)
	{
		error += start_checker(pstate, nb_textures, tmp->line, nb_line);
		ft_putstr(COLOR_RESET);
		nb_line++;
		tmp = tmp->next;
	}
	if (error)
	{
		ft_putnbr(error);
		ft_error(COLOR_RED "Errors" COLOR_RESET);
	}
	return (E_SUCCESS);
}
