/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vec_collinears.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 22:47:18 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 18:00:12 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

inline int	vec_collinears(t_vec u, t_vec v)
{
	double	k;

	if (v.x)
		k = (double)u.x / (double)v.x;
	else if (v.y)
		k = (double)u.y / (double)v.y;
	else if (v.z)
		k = (double)u.z / (double)v.z;
	else
		return (1);
	return (u.x == k * v.x && u.y == k * v.y && u.z == k * v.z);
}
