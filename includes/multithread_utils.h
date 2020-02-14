/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   multithread_utils.h                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/07 09:46:27 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:44:00 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MULTITHREAD_UTILS_H
# define MULTITHREAD_UTILS_H

typedef struct				s_mt_upscale
{
	struct s_mlx_img2		from;
	struct s_mlx_img2		to;
	int						max_w;
	int						min_w;
	t_engine_settings		*settings;
}							t_mt_upscale;

typedef struct				s_generate_poly_mt
{
	int						start;
	int						end;
	t_param					*p;
}							t_generate_poly_mt;

typedef struct				s_multi_disp
{
	t_param					*p;
	int						i;
	int						start_width;
	int						end_width;
	int						start_height;
	int						end_height;
}							t_multi_disp;

#endif
