/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_lists.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 11:57:09 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 16:38:16 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		free_tlist_point(t_list_points **lst)
{
	t_list_points		*head;
	t_list_points		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		ft_memdel((void **)&head);
		head = NULL;
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
}

void		free_tlst_numbers(t_list_numbers **lst)
{
	t_list_numbers		*head;
	t_list_numbers		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		ft_memdel((void **)&head);
		head = NULL;
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
}

void		free_t_list_polygons(t_list_polygons **lst)
{
	t_list_polygons		*head;
	t_list_polygons		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		free_tlist_point(&head->points);
		if (head->options & HAS_BEEN_TRIANGULATED || head->options & IS_BLENDER)
			free_tlist_point(&head->vt);
		ft_memdel((void **)&head);
		head = NULL;
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
}

void		free_t_list_room(t_list_room **lst)
{
	t_list_room		*head;
	t_list_room		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		ft_memdel((void **)&head);
		head = NULL;
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
}

void		free_t_list_objects(t_list_objects **lst)
{
	t_list_objects		*head;
	t_list_objects		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		ft_memdel((void **)&head);
		head = NULL;
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
}
