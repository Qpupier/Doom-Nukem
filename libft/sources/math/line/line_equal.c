/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_equal.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 22:49:00 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	line_equal(t_line l1, t_line l2)
{
	return (vec_collinears(line_vec_dir(l1), line_vec_dir(l2)) && 		\
			vec_collinears(vec_sub(line_point(l1), line_point(l2)), 	\
			line_vec_dir(l2)));
}
