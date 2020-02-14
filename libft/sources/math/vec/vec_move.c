/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vec_move.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 19:53:57 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/20 15:39:00 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

inline t_vec	vec_move_x(t_vec v, float mov)
{
	v.x += mov;
	return (v);
}

inline t_vec	vec_move_y(t_vec v, float mov)
{
	v.y += mov;
	return (v);
}

inline t_vec	vec_move_z(t_vec v, float mov)
{
	v.z += mov;
	return (v);
}
