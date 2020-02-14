/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_data_gif.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 10:26:26 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 15:18:47 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gif.h"

uint16_t			get_key(t_key *keys, uint8_t *sub_len,
	uint8_t *shift, uint8_t *byte)
{
	int				bits_read;
	int				rpad;
	int				frag_size;
	uint16_t		key;

	key = 0;
	bits_read = 0;
	while (bits_read < keys->key_size)
	{
		rpad = (*shift + bits_read) % 8;
		if (rpad == 0)
		{
			if (*sub_len == 0)
				read(keys->gif->fd, sub_len, 1);
			read(keys->gif->fd, byte, 1);
			(*sub_len)--;
		}
		frag_size = (keys->key_size - bits_read) < (8 - rpad) ?
			(keys->key_size - bits_read) : (8 - rpad);
		key |= ((uint16_t)((*byte) >> rpad)) << bits_read;
		bits_read += frag_size;
	}
	key &= (1 << keys->key_size) - 1;
	*shift = (*shift + keys->key_size) % 8;
	return (key);
}

int					interlaced_line_index(int h, int y)
{
	int				p;

	p = (h - 1) / 8 + 1;
	if (y < p)
		return (y * 8);
	y -= p;
	p = (h - 5) / 8 + 1;
	if (y < p)
		return (y * 8 + 4);
	y -= p;
	p = (h - 3) / 4 + 1;
	if (y < p)
		return (y * 4 + 2);
	y -= p;
	return (y * 2 + 1);
}

int					set_datas(t_gd_gif *gif, t_img_data *datas, t_key *keys)
{
	read(gif->fd, &datas->byte, 1);
	keys->key_size = (int)datas->byte;
	datas->start = lseek(gif->fd, 0, SEEK_CUR);
	discard_sub_blocks(gif);
	datas->end = lseek(gif->fd, 0, SEEK_CUR);
	lseek(gif->fd, datas->start, SEEK_SET);
	datas->clear = 1 << keys->key_size;
	datas->stop = datas->clear + 1;
	if (!(datas->table = new_table(keys->key_size)))
		return (0);
	keys->key_size++;
	datas->init_key_size = keys->key_size;
	datas->shift = 0;
	datas->sub_len = 0;
	datas->key = get_key(keys, &datas->sub_len, &datas->shift, &datas->byte);
	datas->frm_off = 0;
	datas->ret = 0;
	return (1);
}

int					check_data_table(t_img_data *datas, t_key *keys)
{
	if (datas->key == datas->clear)
	{
		keys->key_size = datas->init_key_size;
		datas->table->nentries = (1 << (keys->key_size - 1)) + 2;
		datas->table_is_full = 0;
	}
	else if (!datas->table_is_full)
	{
		datas->ret = add_entry(&datas->table, datas->str_len + 1,
			datas->key, datas->entry.suffix);
		if (datas->ret == -1)
		{
			free(datas->table);
			return (1);
		}
		if (datas->table->nentries == 0x1000)
		{
			datas->ret = 0;
			datas->table_is_full = 1;
		}
	}
	datas->key = get_key(keys, &datas->sub_len, &datas->shift, &datas->byte);
	return (0);
}

void				check_data_entries(t_gd_gif *gif, t_img_data *datas,
	t_inc *inc, int interlace)
{
	datas->entry = datas->table->entries[datas->key];
	datas->str_len = datas->entry.length;
	while (1)
	{
		inc->i = datas->frm_off + datas->entry.length - 1;
		inc->j = inc->i % gif->fw;
		inc->k = inc->i / gif->fw;
		if (interlace)
			inc->k = interlaced_line_index((int)gif->fh, inc->k);
		gif->frame[(gif->fy + inc->k) * gif->width + gif->fx + inc->j] =
			datas->entry.suffix;
		if (datas->entry.prefix == 0xFFF)
			break ;
		else
			datas->entry = datas->table->entries[datas->entry.prefix];
	}
	datas->frm_off += datas->str_len;
	if (datas->key < datas->table->nentries - 1 && !datas->table_is_full)
		datas->table->entries[datas->table->nentries - 1].suffix =
			datas->entry.suffix;
}
