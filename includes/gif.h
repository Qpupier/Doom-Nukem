/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gif.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 10:25:23 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 15:19:01 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GIF_H
# define GIF_H
# include "libft.h"

typedef struct		s_gd_palette {
	int				size;
	uint8_t			colors[0x100 * 3];
}					t_gd_palette;

typedef struct		s_gd_gce {
	uint16_t		delay;
	uint8_t			tindex;
	uint8_t			disposal;
	int				input;
	int				transparency;
}					t_gd_gce;

typedef struct		s_gd_gif {
	int				fd;
	off_t			anim_start;
	uint16_t		width;
	uint16_t		height;
	uint16_t		depth;
	uint16_t		loop_count;
	t_gd_gce		gce;
	t_gd_palette	*palette;
	t_gd_palette	lct;
	t_gd_palette	gct;
	uint16_t		fx;
	uint16_t		fy;
	uint16_t		fw;
	uint16_t		fh;
	uint8_t			bgindex;
	uint8_t			*canvas;
	uint8_t			*frame;
}					t_gd_gif;

typedef struct		s_gd_set_gif
{
	int				fd;
	uint8_t			sigver[3];
	uint16_t		width;
	uint16_t		height;
	uint16_t		depth;
	uint8_t			fdsz;
	uint8_t			bgidx;
	uint8_t			aspect;
	int				gct_sz;
	t_gd_gif		*gif;
}					t_gd_set_gif;

typedef struct		s_entry
{
	uint16_t		length;
	uint16_t		prefix;
	uint8_t			suffix;
}					t_entry;

typedef struct		s_table
{
	int				bulk;
	int				nentries;
	t_entry			*entries;
}					t_table;

typedef struct		s_inc
{
	int				i;
	int				j;
	int				k;
}					t_inc;

typedef struct		s_gif_data
{
	int				f;
	int				curr_width;
	int				curr_height;
	char			*buffer;
	uint8_t			*color;
	t_gd_set_gif	*gif;
}					t_gif_data;

typedef struct		s_img_data
{
	t_inc			*inc;
	uint8_t			sub_len;
	uint8_t			shift;
	uint8_t			byte;
	int				init_key_size;
	int				table_is_full;
	int				frm_off;
	int				str_len;
	int				ret;
	uint16_t		key;
	uint16_t		clear;
	uint16_t		stop;
	t_table			*table;
	t_entry			entry;
	off_t			start;
	off_t			end;
}					t_img_data;

typedef struct		s_key
{
	int				key_size;
	t_gd_gif		*gif;
}					t_key;

int					super_free(t_img_data **datas, t_inc **inc, t_key **keys);
int					freemem(void **ptr);
void				free_four(t_inc *inc, t_key *key, t_img_data *data);
void				gd_rewind(t_gd_gif *gif);
void				gd_close_gif(t_gd_set_gif *gif);
int					set_datas(t_gd_gif *gif, t_img_data *datas, t_key *keys);
int					check_data_table(t_img_data *datas, t_key *keys);
void				check_data_entries(t_gd_gif *gif, t_img_data *datas,
	t_inc *inc, int interlace);

uint16_t			read_num(int fd);
void				read_ext(t_gd_gif *gif);
void				discard_sub_blocks(t_gd_gif *gif);
t_table				*new_table(int key_size);
int					add_entry(t_table **tablep, uint16_t length,
	uint16_t prefix, uint8_t suffix);

int					render_frame_rect(t_gd_gif *gif, uint8_t *buffer);
int					gd_get_frame(t_gd_gif *gif);
t_gd_set_gif		*gd_open_gif(const char *fname);

#endif
