/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_lists_supl.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/07 11:41:58 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 11:42:14 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		free_t_list_textures(t_textures_obj **lst)
{
	t_textures_obj		*head;
	t_textures_obj		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		ft_memdel((void **)&head->t.img);
		ft_memdel((void **)&head->t.ptr);
		ft_memdel((void **)&head);
		head = NULL;
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
}
