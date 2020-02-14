/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_perpendicular_line_point_plane.c            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 22:44:47 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 22:45:19 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_line	line_perpendicular_line_point_plane(t_line l, t_vec p, t_vec n)
{
	return (line_create_point_vec(p, vec_cross_product(n, line_vec_dir(l))));
}
