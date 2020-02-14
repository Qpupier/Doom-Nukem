/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fileexists.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 19:05:04 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 19:05:24 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>

int			fileexists(char *file)
{
	struct stat fs;

	if (stat(file, &fs) == -1)
		return (0);
	return (1);
}
