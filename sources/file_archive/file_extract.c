/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   file_extract.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/11 15:01:19 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 16:32:45 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mapfile.h"

static void				read_header(t_fileheader *header, const char *buffer)
{
	ft_strncpy(header->name, buffer, MAX_NAME);
	ft_strncpy(header->csize, buffer + (MAX_NAME - 1), 10);
	header->isize = ft_atoull(header->csize);
}

static void				extract_folder_structure(const char *filename,
															const char *dest)
{
	int		i;
	char	*path;
	char	newpath[PATH_MAX];

	i = 1;
	while (filename[++i])
	{
		if (filename[i] == '/')
		{
			if (!(path = ft_strsub(filename, 2, i - 1)))
				ft_error("An Error occured\n");
			ft_strcpy(newpath, dest);
			if (dest[ft_strlen(dest) - 1] != '/')
				ft_strcat(newpath, "/");
			ft_strcat(newpath, path);
			mkdir(newpath, 0777);
			ft_strdel(&path);
		}
	}
}

static void				extract_file(t_fileheader header, const int fd_input,
															const char *dest)
{
	int				fd_output;
	char			newpath[PATH_MAX];

	ft_strcpy(newpath, dest);
	ft_strcat(newpath, "/");
	ft_strcat(newpath, header.name + 2);
	fd_output = open(newpath, O_CREAT | O_WRONLY, 000666);
	if (fd_output == -1)
		exit(1);
	write_file(&header, fd_input, fd_output, 1);
}

void					file_extract(const char *file, const char *dest)
{
	t_fileheader	header;
	t_mfileindex	index;
	int				fd;
	char			buffer[BLOCK_SIZE];

	if (!(get_fileinfos(&header, file)))
		return ;
	mkdir(dest, 0777);
	index.size = header.isize;
	fd = open(file, O_RDONLY);
	index.pos = 0;
	index.offset = 0;
	while (index.pos + index.offset + BLOCK_SIZE <= index.size)
	{
		index.pos += index.offset;
		read(fd, buffer, HEADER_BLOCK);
		read_header(&header, buffer);
		extract_folder_structure(header.name, dest);
		extract_file(header, fd, dest);
		index.offset = (1 + header.isize / BLOCK_SIZE) * BLOCK_SIZE;
	}
}
