/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrix_rotation.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/05 23:19:22 by qpupier      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 23:20:27 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	matrix_rotation_x(float angle, t_matrix_3_3 matrix)
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = cos(angle);
	matrix[1][2] = -sin(angle);
	matrix[2][0] = 0;
	matrix[2][1] = sin(angle);
	matrix[2][2] = cos(angle);
}

void	matrix_rotation_y(float angle, t_matrix_3_3 matrix)
{
	matrix[0][0] = cos(angle);
	matrix[0][1] = 0;
	matrix[0][2] = sin(angle);
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[2][0] = -sin(angle);
	matrix[2][1] = 0;
	matrix[2][2] = cos(angle);
}

void	matrix_rotation_z(float angle, t_matrix_3_3 matrix)
{
	matrix[0][0] = cos(angle);
	matrix[0][1] = -sin(angle);
	matrix[0][2] = 0;
	matrix[1][0] = sin(angle);
	matrix[1][1] = cos(angle);
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

void	matrix_rotation(float theta_x, float theta_y, float theta_z, 	\
		t_matrix_3_3 rot)
{
	t_matrix_3_3	x;
	t_matrix_3_3	y;
	t_matrix_3_3	z;
	t_matrix_3_3	xy;

	matrix_rotation_x(theta_x, x);
	matrix_rotation_y(theta_y, y);
	matrix_rotation_z(theta_z, z);
	matrix_mult_matrix(x, y, xy);
	matrix_mult_matrix(xy, z, rot);
}
