/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mapfile.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/11 14:29:54 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 14:52:05 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAPFILE_H
# define MAPFILE_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# define BLOCK_SIZE 256
# define HEADER_BLOCK 110
# define MAX_NAME 101
# define SIZE_OFFSET MAX_NAME

typedef struct		s_fileheader
{
	char				name[MAX_NAME];
	char				csize[11];
	uintmax_t			isize;
}					t_fileheader;

typedef struct		s_mfileindex
{
	uintmax_t		size;
	uintmax_t		pos;
	uintmax_t		offset;
}					t_mfileindex;

char				*utoa_base(uintmax_t nb, short int base);
short int			get_fileinfos(t_fileheader *header, const char *filepath);
void				write_file(t_fileheader *header, const int fd_input, 	\
								const int fd_output, const short int extract);
void				extract(const char *file, const char *dest);
void				file_add(const char *filepath, const char *path,
														const int fd_output);
#endif
