/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tweak_obj.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/16 12:57:06 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void			tweak_high_obj(t_param *p)
{
	t_obj		*tmp;

	tmp = p->o;
	if (p->kevent.mouse_4 || p->kevent.mouse_5)
	{
		while (tmp)
		{
			if (tmp->state == 2)
				tmp->pos.z += p->kevent.mouse_4 ? 5 : -5;
			tmp = tmp->next;
		}
	}
}

static void		display_obj_info_bis(t_param *p, t_obj *tmp)
{
	char	*t;

	t = ft_itoa(tmp->action);
	mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y - 25, 0xFFFFFFF, t);
	free(t);
	if (tmp->obj == 1)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y - 10, 0xFFFFFFF, "E-1");
	if (tmp->obj == 2)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y - 10, 0xFFFFFFF, "E-2");
	if (tmp->obj == 3)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y - 10, 0xFFFFFFF, "E-3");
	if (tmp->obj == 4)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y - 10, 0xFFFFFFF, "O-Medic");
	if (tmp->obj == 5)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y - 10, 0xFFFFFFF, "O-Ammo");
	if (tmp->obj == 6)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y - 10, 0xFFFFFFF, "O-Light");
}

static void		display_obj_info_tre(t_param *p, t_obj *tmp)
{
	char		*t;

	t = ft_itoa(tmp->pos.z);
	if (tmp->obj == 1)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y + 5, 0xFFFFFFF, t);
	if (tmp->obj == 2)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y + 5, 0xFFFFFFF, t);
	if (tmp->obj == 3)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y + 5, 0xFFFFFFF, t);
	if (tmp->obj == 4)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y + 5, 0xFFFFFFF, t);
	if (tmp->obj == 5)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y + 5, 0xFFFFFFF, t);
	if (tmp->obj == 6)
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, tmp->pos.x + 10,
		tmp->pos.y + 5, 0xFFFFFFF, t);
	free(t);
}

void			display_obj_info(t_param *p)
{
	t_obj		*tmp;

	if (p->o)
	{
		tmp = p->o;
		while (tmp)
		{
			if (tmp->state == 1 || tmp->state == 2)
			{
				display_obj_info_bis(p, tmp);
				display_obj_info_tre(p, tmp);
			}
			tmp = tmp->next;
		}
	}
}
