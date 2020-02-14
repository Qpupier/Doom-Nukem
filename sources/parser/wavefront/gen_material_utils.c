/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gen_material_utils.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 16:40:25 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 20:02:36 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			init_polygon_structure(t_list_polygons *polygon)
{
	polygon->points = NULL;
	polygon->vt = NULL;
	polygon->options = 0;
}

t_parse_mtl		*get_material_data(t_tmp_obj *buff, char *name)
{
	t_parse_mtl	*tmp;

	tmp = buff->materials_list;
	while (tmp)
	{
		if (ft_strequ(name, tmp->name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
