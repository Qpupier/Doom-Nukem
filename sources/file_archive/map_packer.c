/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_packer.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/07 11:05:49 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 11:34:03 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"
#include <dirent.h>
#include "mapfile.h"

static void		insert_archive(int fd_output, char *argv[])
{
	char			file_path[PATH_MAX];
	struct dirent	*dir;
	DIR				*od;

	file_add(argv[2], "./", fd_output);
	od = opendir("./assets/");
	if (od)
	{
		while ((dir = readdir(od)))
		{
			if (dir->d_name[0] == '.' || ft_strnequ(dir->d_name, "..", 2))
				continue ;
			ft_memset(file_path, ' ', PATH_MAX);
			ft_strcpy(file_path, "./assets/");
			ft_strcat(file_path, dir->d_name);
			file_add(file_path, "./assets/", fd_output);
			ft_printf("Archiving %s...\n", file_path);
		}
		closedir(od);
	}
	file_add(argv[2], "./tmp/", fd_output);
}

int				map_packager(int argc, char *argv[])
{
	int				fd;
	char			filepack[NAME_MAX];

	if (argc < 3 || argc > 3)
	{
		return (ft_printf("Invalid number of arguments. Got %d, 2 expected\n",
			argc - 1) ? 0 : 0);
	}
	if (!fileexists(argv[2]))
		return (ft_printf("File %s, not found\n", argv[2]) ? 0 : 0);
	ft_memset(filepack, 0, NAME_MAX);
	ft_strcpy(filepack, argv[2]);
	ft_strcat(filepack, ".pack");
	if ((fd = open(filepack, O_CREAT | O_WRONLY | O_TRUNC, 000644)) < 0)
	{
		ft_printf("Error creating map pack.\n");
		exit(1);
	}
	insert_archive(fd, argv);
	close(fd);
	return (1);
}

void			get_file_at_root(char *file)
{
	DIR				*od;
	struct dirent	*dir;

	od = opendir("/tmp/doom-nukem");
	if (od)
	{
		while ((dir = readdir(od)))
		{
			if (dir->d_name[0] == '.' || ft_strnequ(dir->d_name, "..", 2))
				continue ;
			if (dir->d_type == 8)
			{
				ft_strcpy(file, "/tmp/doom-nukem/");
				ft_strcat(file, dir->d_name);
			}
		}
		closedir(od);
	}
}
