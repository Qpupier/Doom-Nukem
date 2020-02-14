/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   createmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 11:53:06 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 13:15:14 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void			print_obj_str(t_obj *tmp, char *str, int f)
{
	ft_putstr_fd(str, f);
	if (tmp->obj == 1)
		ft_putstr_fd("assets/creeper.obj, ", f);
	if (tmp->obj == 2)
		ft_putstr_fd("assets/creeper.obj, ", f);
	if (tmp->obj == 3)
		ft_putstr_fd("assets/creeper.obj, ", f);
	if (tmp->obj == 4)
		ft_putstr_fd("assets/creeper.obj, ", f);
	if (tmp->obj == 5)
		ft_putstr_fd("assets/creeper.obj, ", f);
	ft_putstr_fd("", f);
	ft_putnbr_fd(tmp->pos.x * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmp->pos.z * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmp->pos.y * 10, f);
	if (!ft_strnequ("#LIGHT ", str, 7))
		ft_putstr_fd(", 0 0 0, 0.32", f);
	else
		ft_putstr_fd(", .4, ffffff", f);
	if (tmp->action == 1)
		ft_putstr_fd(", ACTION=0 TRIGGER_ON_DIS=0 ON_DIS=50000", f);
	ft_putstr_fd("\n", f);
}

void			print_obj(t_param *p, int f, int id)
{
	t_obj		*tmp;

	tmp = p->o;
	if (p->o)
	{
		while (tmp)
		{
			if (id == tmp->room)
			{
				if (tmp->type == 1)
					print_obj_str(tmp, "#OBJECT ", f);
				if (tmp->type == 2)
					print_obj_str(tmp, "#OBJECT ", f);
				if (tmp->type == 3)
					print_obj_str(tmp, "#LIGHT ", f);
			}
			tmp = tmp->next;
		}
	}
}

static void		put_wall(t_wall *tmpw, int f)
{
	ft_putnbr_fd(tmpw->p_four.x * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmpw->p_four.z * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmpw->p_four.y * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmpw->p_three.x * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmpw->p_three.z * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmpw->p_three.y * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmpw->p_two.x * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmpw->p_two.z * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmpw->p_two.y * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmpw->p_one.x * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmpw->p_one.z * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(tmpw->p_one.y * 10, f);
	ft_putstr_fd(" ", f);
	tmpw->tex >= 0 ? ft_putnbr_fd(tmpw->tex, f) : ft_putstr_fd("0", f);
}

void			put_player(t_param *p, int f)
{
	ft_putstr_fd("#PLAYER_POSITION", f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(p->character.x * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(p->character.z * 10, f);
	ft_putstr_fd(" ", f);
	ft_putnbr_fd(p->character.y * 10, f);
	ft_putstr_fd("\n", f);
	ft_putstr_fd("#ACTION 0 0 0, 0 10 0, 0, INFINITE_ROTATION", f);
	ft_putstr_fd("\n", f);
	ft_putstr_fd("Map Created\n", 1);
	p->kevent.s = 0;
}

void			create_file(t_param *p)
{
	int		f;
	t_room	*tmpr;
	t_wall	*tmpw;

	if (!(f = open("map", O_RDWR | O_CREAT | O_TRUNC, 000655)))
		ft_error("Create Map Failed");
	tmpr = p->r;
	header_map(p, f);
	while (tmpr)
	{
		tmpw = tmpr->wall;
		ft_putstr_fd("ROOM 1 2\n", f);
		while (tmpw)
		{
			put_wall(tmpw, f);
			(tmpw->tex == -2) ? ft_putstr_fd(", INVISIBLE", f) : 0;
			(tmpw->state == -1) ? ft_putstr_fd(", WALLY", f) : 0;
			ft_putstr_fd("\n", f);
			tmpw = tmpw->next;
		}
		print_obj(p, f, tmpr->i);
		tmpr = tmpr->next;
	}
	close(f);
}
