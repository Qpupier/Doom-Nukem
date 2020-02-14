/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vec_null.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 18:57:43 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 18:57:56 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int			vec_null(t_vec u)
{
	return (!u.x && !u.y && !u.z);
}
