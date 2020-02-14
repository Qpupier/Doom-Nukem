/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   character.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/04 12:03:34 by asaba        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 10:45:54 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/editor.h"

void			tweak_high_chara(t_param *p)
{
	if (p->kevent.mouse_4)
	{
		if (p->character.state == 2)
			p->character.z += 5;
		p->kevent.mouse_4 = 0;
	}
}

void			tweak_low_chara(t_param *p)
{
	if (p->kevent.mouse_5)
	{
		if (p->character.state == 2)
			p->character.z -= 5;
		p->kevent.mouse_5 = 0;
	}
}

void			display_chara_info(t_param *p)
{
	char	*t;

	t = ft_itoa(p->character.z);
	if (p->character.state == 1 || p->character.state == 2)
	{
		mlx_string_put(p->mlx->mlx_ptr, p->mlx->win_ptr, p->character.x + 10,
		p->character.y + 5, 0xFFFFFFF, t);
	}
	free(t);
}

static void		trace_character(t_param *p)
{
	if (p->character.state == 2)
		fillcircle(p, (t_v){p->character.x, p->character.y},
		7, 0x00e600);
	if (p->character.state == 1)
		fillcircle(p, (t_v){p->character.x, p->character.y},
		7, 0x66ff66);
	if (p->character.state == 0)
		fillcircle(p, (t_v){p->character.x, p->character.y},
		7, p->character.lay == p->lay ? 0xbeff33 : 0xccffcc);
}

void			place_character(t_param *p)
{
	if (p->kevent.q)
	{
		p->character.x = p->kevent.mouse_x;
		p->character.y = p->kevent.mouse_y;
	}
	tweak_low_chara(p);
	tweak_high_chara(p);
	trace_character(p);
}
