/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rotations.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 12:02:28 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 13:10:17 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

t_vec	vec_rotx(t_vec v, float vsin, float vcos)
{
	t_vec	new;

	new.x = v.x;
	new.y = v.y * vcos + v.z * -vsin;
	new.z = v.y * vsin + v.z * vcos;
	return (new);
}

t_vec	vec_roty(t_vec v, float vsin, float vcos)
{
	t_vec	new;

	new.x = v.x * vcos + v.z * vsin;
	new.y = v.y;
	new.z = v.x * -vsin + v.z * vcos;
	return (new);
}

t_vec	vec_rotz(t_vec v, float vsin, float vcos)
{
	t_vec	new;

	new.x = v.x * vcos + v.y * -vsin;
	new.y = v.x * vsin + v.y * vcos;
	new.z = v.z;
	return (new);
}
