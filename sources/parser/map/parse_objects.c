/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_objects.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 13:45:26 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 14:30:28 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void			init_default(t_list_objects **object)
{
	(*object)->action.action_id = -1;
	(*object)->action.touch_id = -1;
	(*object)->action.click_id = -1;
	(*object)->action.touch_min_dis = -1;
	(*object)->action.end_id = -1;
	(*object)->action.dis_id = -1;
	(*object)->action.on_dis = -1;
	(*object)->action.boom_id = -1;
	(*object)->item_id = -1;
	(*object)->action.teleport_type = -1;
	(*object)->action.teleport_type_option = -1;
	(*object)->action.teleport_position = (t_vec){0, 0, 0};
	(*object)->action.lift_type = -1;
	(*object)->action.lift_value = -1;
	(*object)->action.lift_state = 0;
	(*object)->action.lift_data = 0;
	(*object)->action.end_data = 0;
	(*object)->action.end_type = -1;
}

void				get_obj_name(t_param *p, char *line,
	t_list_objects **object)
{
	char		**data;
	t_vec		pos;
	t_vec		rot;

	if (!(data = ft_strsplit(line, ',')))
		return ;
	if (!(extract_tvec_from_str(data[1], &pos))			\
			|| !(extract_tvec_from_str(data[2], &rot)))
	{
		ft_splitdel(&data);
		return ;
	}
	if (parse_obj(object, get_path(p->pstate, data[0]), p))
	{
		init_default(object);
		(*object)->position = pos;
		(*object)->rot = rot;
		(*object)->scale = ft_atof(data[3]);
		fclamp(&(*object)->rot.x, -360, 360);
		fclamp(&(*object)->rot.y, -360, 360);
		fclamp(&(*object)->rot.z, -360, 360);
		fclamp(&(*object)->scale, 0.1, 100);
		get_obj_options(data, object);
	}
	ft_splitdel(&data);
}

t_list_objects		*parse_objects(t_param *p, t_list_line *lst, 			\
									t_room_index index)
{
	t_list_line		*tmp_lst;
	int				i;
	t_list_objects	*objects;

	objects = NULL;
	tmp_lst = lst;
	i = 0;
	while (tmp_lst && ++i)
	{
		if (((i > index.start && index.end == -1)
				|| (i > index.start && index.end != -1 && i < index.end))
					&& tmp_lst->line[0] == '#')
			if (ft_strnequ("#OBJECT ", tmp_lst->line, 8)
				&& show_parseprogress(p))
				get_obj_name(p, tmp_lst->line + 8, &objects);
		tmp_lst = tmp_lst->next;
	}
	return (objects);
}
