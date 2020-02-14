/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   numbers.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/25 18:09:02 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/03 15:25:44 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int			lst_push_numbers(t_list_numbers **lst, int n)
{
	t_list_numbers		*new;
	t_list_numbers		*tmp;

	if (!(new = malloc(sizeof(t_list_numbers))))
		return (E_ERROR_MALLOC);
	new->n = n;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (E_SUCCESS);
}
