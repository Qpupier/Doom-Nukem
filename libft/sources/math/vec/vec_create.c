/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vec_create.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 19:55:52 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 19:57:32 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_vec	vec_create(float x, float y, float z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
