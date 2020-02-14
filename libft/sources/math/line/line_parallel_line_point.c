/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_parallel_line_point.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 22:43:35 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 22:44:11 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_line	line_parallel_line_point(t_line l, t_vec p)
{
	return (line_create_point_vec(p, line_vec_dir(l)));
}
