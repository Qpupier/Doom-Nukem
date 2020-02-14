/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 13:55:09 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:52:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			convert_lights(t_list_lights *lst_lights,
									unsigned int nb_lights, t_lights *lights)
{
	t_list_lights	*tmp;
	unsigned int	light_index;

	light_index = 0;
	tmp = lst_lights;
	while (lst_lights && light_index <= nb_lights)
	{
		lights[light_index].pos = lst_lights->pos;
		lights[light_index].intensity = lst_lights->intensity;
		lights[light_index].color = lst_lights->color;
		light_index++;
		lst_lights = lst_lights->next;
	}
}

void			convert_t_list_points(t_list_points *lst_points, t_vec *dest)
{
	t_list_points	*tmp;
	unsigned int	pt_index;

	pt_index = 0;
	tmp = lst_points;
	while (tmp)
	{
		dest[pt_index] = tmp->point;
		pt_index++;
		tmp = tmp->next;
	}
}

void			convert_vt_tmp(t_list_points *lst_points, t_vec *dest)
{
	t_list_points	*tmp;
	unsigned int	pt_index;

	pt_index = 0;
	tmp = lst_points;
	while (tmp && pt_index < 3)
	{
		dest[pt_index] = tmp->point;
		pt_index++;
		tmp = tmp->next;
	}
}
