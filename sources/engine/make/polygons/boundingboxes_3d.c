/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   boundingboxes_3d.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/23 19:07:22 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/03 14:39:38 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

inline static void	reset_oob(t_param *p)
{
	unsigned int	index;
	t_polygon		*poly;

	index = -1;
	while (++index < p->total_polygons)
	{
		poly = p->lst_polygons[index];
		if (poly->obj_ptr && !(poly->obj_ptr->state & OBJ_DISABLE))
		{
			poly->obj_ptr->boundingbox.max.x = -INFINITY;
			poly->obj_ptr->boundingbox.max.y = -INFINITY;
			poly->obj_ptr->boundingbox.max.z = -INFINITY;
			poly->obj_ptr->boundingbox.min.x = INFINITY;
			poly->obj_ptr->boundingbox.min.y = INFINITY;
			poly->obj_ptr->boundingbox.min.z = INFINITY;
		}
	}
}

static void			handle_actions_dis(t_param *p, t_objects *obj)
{
	if (obj->action.dis_id >= 0
		&& obj->boundingbox.dis <= obj->action.on_dis)
		p->actions[obj->action.dis_id].state |= ACT_ACTIVE;
	if (obj->action.teleport_type == 2
		&& obj->boundingbox.dis <= obj->action.teleport_type_option)
		teleport_player(p, obj->action.teleport_position);
	if (obj->action.end_type == 2
		&& obj->boundingbox.dis <= obj->action.end_data)
		(!(p->pstate & P_ENDED)) ? (p->pstate |= P_ENDED) : 0;
}

void				make_boundingbox(t_param *p)
{
	unsigned int	index_pt;
	unsigned int	index;
	t_polygon		*poly;

	reset_oob(p);
	index = -1;
	while (++index < p->total_polygons)
	{
		poly = p->lst_polygons[index];
		poly->boudingbox.min = (t_vec){INFINITY, INFINITY, INFINITY};
		poly->boudingbox.max = (t_vec){-INFINITY, -INFINITY, -INFINITY};
		index_pt = -1;
		while (++index_pt < poly->nb_points)
			generate_box_poly(poly->points[index_pt], &poly->boudingbox);
		if (poly->obj_ptr && !(poly->obj_ptr->state & OBJ_DISABLE))
		{
			generate_box_obj(poly->boudingbox, &poly->obj_ptr->boundingbox);
			handle_actions_dis(p, poly->obj_ptr);
			if (poly->obj_ptr->boundingbox.dis <= 500)
				evt_action_add_inventory(p, poly->index, poly->obj_ptr);
		}
	}
}
