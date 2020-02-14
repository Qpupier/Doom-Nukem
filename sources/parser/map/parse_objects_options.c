/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_objects_options.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 16:27:53 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 15:55:55 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void			get_supl(char **opt, t_list_objects **object, int i)
{
	if (ft_strnequ(opt[i], "BOOM", 4))
		(*object)->action.boom_id = ft_atoi(str_getaocc(opt[i], '='));
	if (ft_strnequ(opt[i], "ITEM_PICKUP", 11))
		(*object)->item_id = ft_atoi(str_getaocc(opt[i], '='));
	if (ft_strnequ(opt[i], "TELEPORT", 8))
		get_teleport(str_getaocc(opt[i], '='), object);
	if (ft_strnequ(opt[i], "LIFT", 4))
		get_lift(str_getaocc(opt[i], '='), object);
	if (ft_strnequ(opt[i], "END", 3))
		get_end(str_getaocc(opt[i], '='), object);
	if (ft_strnequ(opt[i], "PROJECTILE", 10))
		(*object)->type = OBJ_PROJECTILE;
}

static void			get_actions(char **opt, t_list_objects **object, int i)
{
	if (ft_strnequ(opt[i], "ACTION", 6))
		(*object)->action.action_id = ft_atoi(str_getaocc(opt[i], '='));
	if (ft_strnequ(opt[i], "TRIGGER_ON_TOUCH", 16))
		(*object)->action.touch_id = ft_atoi(str_getaocc(opt[i], '='));
	if (ft_strnequ(opt[i], "TOUCH_DIS", 9))
		(*object)->action.touch_min_dis = ft_atof(str_getaocc(opt[i], '='));
	if (ft_strnequ(opt[i], "TRIGGER_ON_CLICK", 16))
		(*object)->action.click_id = ft_atoi(str_getaocc(opt[i], '='));
	if (ft_strnequ(opt[i], "TRIGGER_ON_END", 14))
		(*object)->action.end_id = ft_atoi(str_getaocc(opt[i], '='));
	if (ft_strnequ(opt[i], "TRIGGER_ON_DIS", 14))
		(*object)->action.dis_id = ft_atoi(str_getaocc(opt[i], '='));
	if (ft_strnequ(opt[i], "ON_DIS", 6))
		(*object)->action.on_dis = ft_atof(str_getaocc(opt[i], '='));
}

int					get_obj_options(char **data, t_list_objects **object)
{
	char			**opt;
	int				i;

	(*object)->type = 0;
	i = -1;
	if (!(opt = ft_strsplit(data[4], ' ')))
		return (0);
	while (++i < count_dstr(opt))
	{
		get_actions(opt, object, i);
		get_supl(opt, object, i);
	}
	ft_splitdel(&opt);
	return (0);
}
