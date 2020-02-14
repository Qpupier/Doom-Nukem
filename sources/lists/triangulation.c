/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   triangulation.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qpupier <qpupier@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/08 11:14:28 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 12:14:36 by qpupier     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int		lst_tri_addpoints(t_pt_tri_tmp **points, t_vec point)
{
	t_pt_tri_tmp	*new;
	t_pt_tri_tmp	*tmp;

	if (!(new = malloc(sizeof(t_pt_tri_tmp))))
		return (0);
	new->point = point;
	new->deleted = 0;
	new->next = NULL;
	if (!*points)
		*points = new;
	else
	{
		tmp = *points;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

void	free_lst_tri_points(t_pt_tri_tmp **lst)
{
	t_pt_tri_tmp		*head;
	t_pt_tri_tmp		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		free(head);
		head = NULL;
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
}

int		lst_tri_add(t_list_tri **tri, t_vec a, t_vec b, t_vec c)
{
	t_list_tri	*new;
	t_list_tri	*tmp;

	if (vec_null(vec_cross_product(vec_sub(b, a), vec_sub(c, a))))
		return (0);
	if (!(new = malloc(sizeof(t_list_tri))))
		return (0);
	new->tri[0] = a;
	new->tri[1] = b;
	new->tri[2] = c;
	new->next = NULL;
	if (!*tri)
		*tri = new;
	else
	{
		tmp = *tri;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

void	free_lst_tri(t_list_tri **lst)
{
	t_list_tri		*head;
	t_list_tri		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		free(head);
		head = NULL;
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
}

int		push_triangulated_polygon(t_list_polygons **list, t_list_polygons data)
{
	t_list_polygons	*new_poly;

	if (!(new_poly = (t_list_polygons *)malloc(sizeof(t_list_polygons))))
		return (0);
	new_poly->points = data.points;
	new_poly->texture = data.texture;
	new_poly->nb_points = 3;
	new_poly->color = data.color;
	new_poly->vt = data.vt ? data.vt : NULL;
	new_poly->options = data.options;
	make_tex_tri(new_poly);
	new_poly->next = NULL;
	if (*list != NULL)
		new_poly->next = *list;
	*list = new_poly;
	return (1);
}
