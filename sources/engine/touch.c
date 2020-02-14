/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 11:25:19 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 12:45:24 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	get_touch(t_param *p)
{
	t_buffer	buffer;

	buffer = p->buffer[p->engine_settings->zbuffer_center];
	if (!buffer.ptr_poly)
		return ;
	if (buffer.ptr_poly->obj_ptr)
	{
		if (buffer.ptr_poly->obj_ptr->action.touch_id >= 0
			&& buffer.ptr_poly->obj_ptr->action.touch_min_dis >= buffer.dis)
		{
			p->actions[buffer.ptr_poly->obj_ptr->action.touch_id].state |=
				ACT_ACTIVE;
		}
	}
}
