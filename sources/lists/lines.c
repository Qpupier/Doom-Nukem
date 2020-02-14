/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lines.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 14:03:02 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:52:24 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int				line_pushback(t_list_line **lst, char *str)
{
	t_list_line	*new;
	t_list_line	*tmp;

	if (!(new = malloc(sizeof(t_list_line))))
		return (E_ERROR_MALLOC);
	if (!(new->line = ft_strdup(str)))
		return (E_ERROR_MALLOC);
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

int				line_pushfront(t_list_line **lst, char *str)
{
	t_list_line	*new;

	if (!(new = malloc(sizeof(t_list_line))))
		return (E_ERROR_MALLOC);
	if (!(new->line = ft_strdup(str)))
		return (E_ERROR_MALLOC);
	new->next = NULL;
	if (*lst != NULL)
		new->next = *lst;
	*lst = new;
	return (E_SUCCESS);
}

void			reverse_t_list_line(t_list_line **line)
{
	t_list_line *current;
	t_list_line *prev;
	t_list_line *next;

	current = *line;
	next = NULL;
	prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*line = prev;
}

void			free_t_list_lines(t_list_line **lst)
{
	t_list_line		*head;
	t_list_line		*next;

	head = *lst;
	while (head != NULL)
	{
		next = head->next;
		if (head->line)
			ft_strdel(&head->line);
		ft_memdel((void **)&head);
		head = next;
	}
	*lst = NULL;
	head = NULL;
	next = NULL;
}

unsigned int	t_list_line_count(t_list_line *head)
{
	t_list_line		*tmp;
	unsigned int	i;

	i = 0;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
