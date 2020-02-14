/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_object_options_supl.c                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 15:38:49 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 15:39:12 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			get_teleport(char *str, t_list_objects **object)
{
	char		**data;

	if (!(data = ft_strsplit(str, ';')))
		return ;
	if ((count_dstr(data) != 5) || (!str_isnumber(data[1])
			|| !str_isnumber(data[2]) || !str_isnumber(data[3])
			|| !str_isnumber(data[4])))
	{
		ft_splitdel(&data);
		return ;
	}
	if (ft_strequ(data[0], "CLICK"))
		(*object)->action.teleport_type = 1;
	if (ft_strequ(data[0], "DIS"))
		(*object)->action.teleport_type = 2;
	(*object)->action.teleport_type_option = ft_atoi(data[1]);
	(*object)->action.teleport_position.x = ft_atoi(data[2]);
	(*object)->action.teleport_position.y = ft_atoi(data[3]);
	(*object)->action.teleport_position.z = ft_atoi(data[4]);
	ft_splitdel(&data);
}

void			get_lift(char *str, t_list_objects **object)
{
	char		**data;

	if (!(data = ft_strsplit(str, ';')))
		return ;
	if ((count_dstr(data) != 3) || (!str_isnumber(data[1])
			|| !str_isnumber(data[2])))
	{
		ft_splitdel(&data);
		return ;
	}
	if (ft_strequ(data[0], "CLICK"))
		(*object)->action.lift_type = 1;
	(*object)->action.lift_data = ft_atoi(data[1]);
	(*object)->action.lift_value = ft_atoi(data[2]);
	ft_splitdel(&data);
}

void			get_end(char *str, t_list_objects **object)
{
	char		**data;

	if (!(data = ft_strsplit(str, ';')))
		return ;
	if ((count_dstr(data) != 2) || (!str_isnumber(data[1])))
	{
		ft_splitdel(&data);
		return ;
	}
	if (ft_strequ(data[0], "CLICK"))
		(*object)->action.end_type = 1;
	if (ft_strequ(data[0], "DIS"))
		(*object)->action.end_type = 2;
	(*object)->action.end_data = ft_atoi(data[1]);
	ft_splitdel(&data);
}
