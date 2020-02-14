/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_actions.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/03 14:48:13 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:52:24 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void	init_default(t_actions *action)
{
	action->state = 0;
	action->pos = (t_vec){0, 0, 0};
	action->pos_curr = (t_vec){0, 0, 0};
	action->rot = (t_vec){0, 0, 0};
	action->rot_curr = (t_vec){0, 0, 0};
	action->pos_inc = (t_vec){1, 1, 1};
	action->time_to_wait = 0;
	action->sound = -1;
	action->item_id = -1;
	action->time_on_start = 0;
}

static void	store_action(unsigned int nb_options, char **data, 			\
													t_actions *action)
{
	unsigned int	i;

	i = -1;
	while (++i < nb_options)
	{
		if (ft_strequ(data[i], "REPEAT"))
			action->state |= ACT_REPEAT;
		if (ft_strequ(data[i], "INFINITE_ROTATION"))
			action->state |= ACT_INFINITE_ROT;
		if (ft_strnequ(data[i], "WAIT_TRIGGER=", 13))
			action->time_to_wait = ft_atoi(str_getaocc(data[i], '='));
		if (ft_strnequ(data[i], "ITEM_DEPENDENCY=", 16))
			action->item_id = ft_atoi(str_getaocc(data[i], '='));
		if (ft_strnequ(data[i], "INSTANT", 7))
			action->state |= ACT_INSTANT;
	}
}

void		parse_action_data(t_param *p, char *line, unsigned int index)
{
	char			**data;
	char			**data_options;
	uint32_t		state;
	unsigned int	nb_options;

	state = 0;
	data_options = NULL;
	nb_options = 0;
	if (!(data = ft_strsplit(line, ',')))
		handle_error(p, E_ERROR_MALLOC);
	if (count_dstr(data) >= 4 && !(data_options = ft_strsplit(data[3], ' ')))
	{
		ft_splitdel(&data);
		handle_error(p, E_ERROR_MALLOC);
	}
	init_default(&p->actions[index]);
	extract_tvec_from_str(data[0], &p->actions[index].pos);
	extract_tvec_from_str(data[1], &p->actions[index].rot);
	p->actions[index].sound = ft_atoi(data[2]);
	if (data_options)
		nb_options = count_dstr(data_options);
	store_action(nb_options, data_options, &p->actions[index]);
	ft_splitdel(&data);
	if (data_options)
		ft_splitdel(&data_options);
}

void		parse_actions(t_param *p, t_list_line *lines)
{
	unsigned int	nb_actions;
	t_list_line		*tmp;

	p->nb_actions = 0;
	nb_actions = 0;
	tmp = lines;
	while (tmp)
	{
		if (ft_strnequ("#ACTION ", tmp->line, 8))
			p->nb_actions++;
		tmp = tmp->next;
	}
	if (!(p->actions = malloc(sizeof(t_actions) * p->nb_actions)))
	{
		p->nb_actions = 0;
		return ;
	}
	tmp = lines;
	while (tmp)
	{
		if (ft_strnequ("#ACTION ", tmp->line, 8) && show_parseprogress(p))
			parse_action_data(p, tmp->line + 8, nb_actions++);
		tmp = tmp->next;
	}
}
