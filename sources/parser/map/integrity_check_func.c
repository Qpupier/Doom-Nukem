/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   integrity_check_func.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/03 15:53:30 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 14:22:47 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

short unsigned int	check_textures(char *line)
{
	struct stat		filestat;

	if (stat(line, &filestat))
	{
		ft_putstr(line);
		ft_putstr(COLOR_RED " not found\n" COLOR_RESET);
		return (1);
	}
	return (0);
}

short unsigned int	check_room(char *line, int nb_textures)
{
	char		**data;

	if (!(data = ft_strsplit(line, ' ')))
		return (1);
	if (count_dstr(data) != 3)
	{
		ft_splitdel(&data);
		return (1);
	}
	if (!str_isnumber(data[1]) || !str_isnumber(data[2])
					|| ft_atoi(data[1]) < 0 || ft_atoi(data[1]) >= nb_textures
					|| ft_atoi(data[2]) < 0 || ft_atoi(data[2]) >= nb_textures)
	{
		ft_splitdel(&data);
		return (1);
	}
	ft_splitdel(&data);
	return (0);
}

short unsigned int	check_vertices(char *line, int nb_textures)
{
	char			**data;
	unsigned int	i;
	int				error;
	int				count;

	error = 0;
	if (!(data = ft_strsplit(line, ' ')))
		return (1);
	if ((count = count_dstr(data) < 13))
		error = 1;
	i = -1;
	while (++i < 13 && !error)
	{
		if (!str_isnumber(data[i]) && i < 12)
			error = 1;
		if (i == 12)
			if ((count >= 13 && !str_isnumbern(data[i], ft_strlen(data[i]) - 1))
				|| (count == 12 && !str_isnumber(data[i])))
				error = 1;
	}
	if (!error && (ft_atoi(data[12]) < 0 || ft_atoi(data[12]) >= nb_textures))
		error = 1;
	ft_splitdel(&data);
	return (error);
}

short unsigned int	check_lights(char *line)
{
	char		**data;

	if (!(data = ft_strsplit(line, ',')))
		return (1);
	if (count_dstr(data) < 3
		|| !(check_tvec_from_str(data[0]))
		|| !str_isnumber(data[1][0] == ' ' ? data[1] + 1 : data[1]))
	{
		ft_splitdel(&data);
		return (1);
	}
	ft_splitdel(&data);
	return (0);
}

short unsigned int	check_objects(uint32_t pstate, char *line)
{
	char		**data;

	if (!(data = ft_strsplit(line, ',')))
		return (1);
	if (!(fileexists(get_path(pstate, data[0]))))
	{
		ft_putstr("file does not exists\n");
		ft_splitdel(&data);
		return (1);
	}
	if (count_dstr(data) < 4
		|| !(check_tvec_from_str(data[1])) || !(check_tvec_from_str(data[2])))
	{
		ft_splitdel(&data);
		return (1);
	}
	ft_splitdel(&data);
	return (0);
}
