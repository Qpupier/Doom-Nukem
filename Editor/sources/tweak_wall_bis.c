/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tweak_wall_bis.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 16:45:20 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

static void		display_point_info_tre(t_param *p, t_wall *tmp)
{
	char		*t;

	t = ft_itoa(tmp->p_three.z);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->p_two.x + 10,
	tmp->p_two.y + 50, 0xFFFFFFF, t);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr,
	(tmp->p_one.x + tmp->p_two.x) / 2 + 10,
	(tmp->p_one.y + tmp->p_two.y) / 2, 0xFF5555, "TEX");
	free(t);
	t = ft_itoa(tmp->tex);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr,
	(tmp->p_one.x + tmp->p_two.x) / 2 + 10,
	(tmp->p_one.y + tmp->p_two.y) / 2 + 15, 0xFF5555, t);
	free(t);
}

static void		display_point_info_bis(t_param *p, t_wall *tmp)
{
	char		*t;

	t = ft_itoa(tmp->p_one.z);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->p_one.x + 10,
	tmp->p_one.y + 5, 0xFFFFFFF, t);
	free(t);
	t = ft_itoa(tmp->p_four.z);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->p_one.x + 10,
	tmp->p_one.y + 20, 0xFFFFFFF, t);
	free(t);
	t = ft_itoa(tmp->p_two.z);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->p_two.x + 10,
	tmp->p_two.y + 35, 0xFFFFFFF, t);
	free(t);
	display_point_info_tre(p, tmp);
}

void			display_point_info(t_param *p)
{
	t_wall		*tmp;

	if (p->w)
	{
		tmp = p->w;
		while (tmp)
		{
			if (tmp->state == 1 || tmp->state == 2)
				display_point_info_bis(p, tmp);
			tmp = tmp->next;
		}
	}
}

void			sort_wall(t_wall *wall)
{
	t_wall		*tmp;
	t_point		swap;

	tmp = wall;
	while (tmp->next)
	{
		if (!(tmp->p_two.x == tmp->next->p_one.x &&
		tmp->p_two.y == tmp->next->p_one.y &&
		tmp->p_two.z == tmp->next->p_one.z))
		{
			swap = tmp->p_one;
			tmp->p_one = tmp->p_two;
			tmp->p_two = swap;
			swap = tmp->p_four;
			tmp->p_four = tmp->p_three;
			tmp->p_three = swap;
		}
		tmp = tmp->next;
	}
}
