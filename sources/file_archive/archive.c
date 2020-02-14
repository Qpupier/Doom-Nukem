/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   archive.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/10 15:22:42 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 11:17:02 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mapfile.h"

static const char	*extract_filename(const char *filepath)
{
	int		len;

	len = ft_strlen(filepath);
	while (len-- > 0)
	{
		if (filepath[len] == '/')
			return (filepath + len + 1);
	}
	return (filepath);
}

short int			get_fileinfos(t_fileheader *header, const char *filepath)
{
	struct stat		fs;
	char			*tmp;

	if (!stat(filepath, &fs))
	{
		header->isize = fs.st_size;
		ft_strncpy(header->name, extract_filename(filepath),
			sizeof(header->name));
		tmp = utoa_base(header->isize, 10);
		ft_strncpy(header->csize, tmp, sizeof(header->csize));
		free(tmp);
		return (1);
	}
	return (0);
}

void				write_file(t_fileheader *header, const int fd_input,
								const int fd_output, const short int extract)
{
	uintmax_t		rsize;
	int				rd;
	char			buffer[BLOCK_SIZE];

	rsize = header->isize;
	while (rsize >= BLOCK_SIZE)
	{
		read(fd_input, buffer, BLOCK_SIZE);
		write(fd_output, buffer, BLOCK_SIZE);
		rsize -= BLOCK_SIZE;
	}
	ft_bzero(buffer, BLOCK_SIZE);
	rd = read(fd_input, buffer, BLOCK_SIZE);
	write(fd_output, buffer, (extract ? rsize : BLOCK_SIZE));
}

void				file_add(const char *filepath, const char *path,
														const int fd_output)
{
	t_fileheader	header;
	int				fd_input;
	char			name[MAX_NAME];

	fd_input = open(filepath, O_RDONLY, 0);
	if (!get_fileinfos(&header, filepath))
		return ;
	ft_bzero(name, MAX_NAME);
	ft_strcpy(name, path);
	ft_strcat(name, header.name);
	write(fd_output, name, sizeof(header.name) - 1);
	write(fd_output, header.csize, sizeof(header.csize) - 1);
	write_file(&header, fd_input, fd_output, 0);
	close(fd_input);
}
