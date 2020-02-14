/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   obj_parser.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 11:28:06 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 14:44:05 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void			free_mtl_parser(t_parse_mtl **lst)
{
	t_parse_mtl		*head;
	t_parse_mtl		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		if (head->name)
			ft_strdel(&head->name);
		if (head->ka)
			ft_strdel(&head->ka);
		if (head->kd)
			ft_strdel(&head->kd);
		if (head->map_kd)
			ft_strdel(&head->map_kd);
		free(head);
		head = NULL;
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
}

void			free_object_parser(t_tmp_obj tmp, int state)
{
	free_t_list_lines(&tmp.faces);
	free_t_list_lines(&tmp.vertices);
	free_t_list_lines(&tmp.normals);
	free_t_list_lines(&tmp.textures);
	free_t_list_lines(&tmp.file);
	if (state == 0)
	{
		ft_strdel(&tmp.mtl_file);
		return ;
	}
	if (state != 0)
	{
		free_mtl_parser(&tmp.materials_list);
		free_t_list_lines(&tmp.materials);
		free_tlst_numbers(&tmp.materials_indexes);
		if (state == -1)
			return ;
	}
	free(tmp.tab_normals);
	free(tmp.tab_textures);
	free(tmp.tab_vertices);
}

static int		push_object(t_list_objects **lst_objects,
	t_list_polygons *lst_polygons, t_tmp_obj tmp)
{
	t_list_objects	obj_data;

	obj_data.poly = lst_polygons;
	obj_data.position = (t_vec){0, 0, 0};
	obj_data.rot = (t_vec){0, 0, 0};
	obj_data.scale = 10;
	if (tlist_count_polygon(lst_polygons))
	{
		object_push(lst_objects, lst_polygons);
		free_object_parser(tmp, 1);
		return (1);
	}
	return (0);
}

int				parse_obj(t_list_objects **lst_objects, const char *file,
	t_param *p)
{
	t_tmp_obj		tmp;
	t_list_polygons	*lst_polygons;
	int				state;

	lst_polygons = NULL;
	init_reader(&tmp);
	if ((state = open_file(p, &tmp, file)) == -2)
		return (0);
	if (state == 0)
	{
		free_object_parser(tmp, 0);
		return (0);
	}
	if (state == -1)
	{
		free_object_parser(tmp, -1);
		return (0);
	}
	gen_material_polygon(p, &tmp, &lst_polygons);
	generate_polygon_no_mats(p, &tmp, &lst_polygons);
	triangulate_object(&lst_polygons);
	return (push_object(lst_objects, lst_polygons, tmp));
}
