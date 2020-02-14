/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clamp.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 19:00:16 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:00:40 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void		fclamp(float *curr, float min, float max)
{
	if (*curr <= min)
		*curr = min;
	if (*curr >= max)
		*curr = max;
}

void		iclamp(intmax_t *curr, int min, int max)
{
	if (*curr <= min)
		*curr = min;
	if (*curr >= max)
		*curr = max;
}
