/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_position.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 13:32:35 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 15:29:29 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int			parse_player(t_param *p, t_list_line *lst)
{
	t_list_line	*tmp;
	t_vec		pos;
	float		rot;

	tmp = lst;
	pos = (t_vec){0, 0, 0};
	rot = 0.f;
	p->player.roty_angle = 0;
	while (tmp)
	{
		if (ft_strnequ("#PLAYER_POSITION ", tmp->line, 17)
			&& show_parseprogress(p))
			extract_tvec_from_str(tmp->line + 17, &pos);
		if (ft_strnequ("#PLAYER_ROTATION ", tmp->line, 17)
			&& show_parseprogress(p))
			p->player.roty_angle = ft_deg_to_rad(ft_atoi(tmp->line + 17));
		tmp = tmp->next;
	}
	p->player.position = pos;
	p->player.current_position = pos;
	p->player.roty_vcos = cos(p->player.roty_angle);
	p->player.roty_vsin = sin(p->player.roty_angle);
	return (1);
}
