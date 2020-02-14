/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   field.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 15:04:43 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 10:48:15 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_extract_precision_number(t_env *e, char *s, int start)
{
	int j;

	j = start;
	e->precision = 0;
	while (s[j] == '.' || pf_isdigit(s[j]))
	{
		if (pf_isdigit(s[j]))
			e->precision = e->precision * 10 + (s[j] - '0');
		j++;
	}
}

void		pf_extract_precision(t_env *e, int start, int end, char *string)
{
	int j;

	j = start - 1;
	while (++j < end && (string[j] != '.'))
		;
	while (j < end && string[j])
	{
		if (string[j] == '.')
			pf_extract_precision_number(e, string, j);
		j++;
	}
}

void		pf_extract_width(t_env *e, int start, int end, char *string)
{
	int j;

	j = start - 1;
	while (++j < end && (!pf_isdigit(string[j]) || string[j] == '0'))
		;
	while (j < end && string[j])
	{
		if (pf_isdigit(string[j]))
		{
			if (e->width == -1)
				e->width = 0;
			e->width = e->width * 10 + (string[j] - '0');
		}
		if (!pf_isdigit(string[j + 1]))
			break ;
		j++;
	}
}
