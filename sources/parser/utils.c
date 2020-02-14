/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 11:44:41 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 11:28:28 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void	get_path_nopack(const char *file, char *dst)
{
	if (ft_strnequ("./assets/", file, 9))
		ft_strcpy(dst, file);
	else if (ft_strnequ("assets/", file, 7))
		ft_strcpy(dst, file);
	else
	{
		ft_strcpy(dst, "assets/");
		ft_strcat(dst, file);
	}
}

char		*get_path(uint32_t pstate, const char *file)
{
	static char		dst[PATH_MAX];

	ft_memset(dst, '\0', PATH_MAX);
	if (pstate & PACK_FILE_OPENNED)
	{
		if (ft_strnequ("./assets/", file, 9))
		{
			ft_strcpy(dst, "/tmp/doom-nukem/");
			ft_strcat(dst, file + 2);
		}
		else if (ft_strnequ("assets/", file, 7))
		{
			ft_strcpy(dst, "/tmp/doom-nukem/");
			ft_strcat(dst, file);
		}
		else
		{
			ft_strcpy(dst, "/tmp/doom-nukem/assets/");
			ft_strcat(dst, file);
		}
	}
	else
		get_path_nopack(file, dst);
	return (dst);
}
