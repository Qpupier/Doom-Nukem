/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_walls_options.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/10 15:04:40 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:51:17 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		store_option(char *str, t_list_polygons *poly)
{
	if (ft_strequ("IGNORE", str))
		poly->options |= O_IGNORE;
	if (ft_strequ("INVISIBLE", str))
		poly->options |= O_INVISIBLE | O_IGNORE;
	if (ft_strequ("WALLY", str))
		poly->options |= O_WALLY;
}

void			get_wall_options(char *line, t_list_polygons *poly)
{
	char			**data;
	char			**opt_list;
	int				i;

	i = -1;
	if (!(data = ft_strsplit(line, ',')))
		return ;
	if (count_dstr(data) < 2)
	{
		ft_splitdel(&data);
		return ;
	}
	if (!(opt_list = ft_strsplit(data[1], ' ')))
	{
		ft_splitdel(&data);
		return ;
	}
	while (++i < count_dstr(opt_list))
		store_option(opt_list[i], poly);
	ft_splitdel(&data);
	ft_splitdel(&opt_list);
}
