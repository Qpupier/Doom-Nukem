/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   axes_rotation.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 14:52:03 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

t_rotation_axes		axes_rotation_init(t_axis axis, t_vec rot)
{
	t_rotation_axes	value;

	value.cos_x.x = cos(ft_deg_to_rad(rot.x * axis.x.x));
	value.cos_x.y = cos(ft_deg_to_rad(rot.x * axis.x.y));
	value.cos_x.z = cos(ft_deg_to_rad(rot.x * axis.x.z));
	value.cos_y.x = cos(ft_deg_to_rad(rot.y * axis.y.x));
	value.cos_y.y = cos(ft_deg_to_rad(rot.y * axis.y.y));
	value.cos_y.z = cos(ft_deg_to_rad(rot.y * axis.y.z));
	value.cos_z.x = cos(ft_deg_to_rad(rot.z * axis.z.x));
	value.cos_z.y = cos(ft_deg_to_rad(rot.z * axis.z.y));
	value.cos_z.z = cos(ft_deg_to_rad(rot.z * axis.z.z));
	value.sin_x.x = sin(ft_deg_to_rad(rot.x * axis.x.x));
	value.sin_x.y = sin(ft_deg_to_rad(rot.x * axis.x.y));
	value.sin_x.z = sin(ft_deg_to_rad(rot.x * axis.x.z));
	value.sin_y.x = sin(ft_deg_to_rad(rot.y * axis.y.x));
	value.sin_y.y = sin(ft_deg_to_rad(rot.y * axis.y.y));
	value.sin_y.z = sin(ft_deg_to_rad(rot.y * axis.y.z));
	value.sin_z.x = sin(ft_deg_to_rad(rot.z * axis.z.x));
	value.sin_z.y = sin(ft_deg_to_rad(rot.z * axis.z.y));
	value.sin_z.z = sin(ft_deg_to_rad(rot.z * axis.z.z));
	return (value);
}

void				axes_apply_rot(t_vec *pt, t_rotation_axes rot)
{
	*pt = vec_rotx(*pt, rot.sin_x.x, rot.cos_x.x);
	*pt = vec_roty(*pt, rot.sin_x.y, rot.cos_x.y);
	*pt = vec_rotz(*pt, rot.sin_x.z, rot.cos_x.z);
	*pt = vec_rotx(*pt, rot.sin_y.x, rot.cos_y.x);
	*pt = vec_roty(*pt, rot.sin_y.y, rot.cos_y.y);
	*pt = vec_rotz(*pt, rot.sin_y.z, rot.cos_y.z);
	*pt = vec_rotx(*pt, rot.sin_z.x, rot.cos_z.x);
	*pt = vec_roty(*pt, rot.sin_z.y, rot.cos_z.y);
	*pt = vec_rotz(*pt, rot.sin_z.z, rot.cos_z.z);
}

void				axes_apply_rot_origin(t_vec center, t_vec *pt,
	t_rotation_axes rot)
{
	*pt = vec_rotx(vec_sub(*pt, center), rot.sin_x.x, rot.cos_x.x);
	*pt = vec_add(*pt, center);
	*pt = vec_roty(vec_sub(*pt, center), rot.sin_x.y, rot.cos_x.y);
	*pt = vec_add(*pt, center);
	*pt = vec_rotz(vec_sub(*pt, center), rot.sin_x.z, rot.cos_x.z);
	*pt = vec_add(*pt, center);
	*pt = vec_rotx(vec_sub(*pt, center), rot.sin_y.x, rot.cos_y.x);
	*pt = vec_add(*pt, center);
	*pt = vec_roty(vec_sub(*pt, center), rot.sin_y.y, rot.cos_y.y);
	*pt = vec_add(*pt, center);
	*pt = vec_rotz(vec_sub(*pt, center), rot.sin_y.z, rot.cos_y.z);
	*pt = vec_add(*pt, center);
	*pt = vec_rotx(vec_sub(*pt, center), rot.sin_z.x, rot.cos_z.x);
	*pt = vec_add(*pt, center);
	*pt = vec_roty(vec_sub(*pt, center), rot.sin_z.y, rot.cos_z.y);
	*pt = vec_add(*pt, center);
	*pt = vec_rotz(vec_sub(*pt, center), rot.sin_z.z, rot.cos_z.z);
	*pt = vec_add(*pt, center);
}
