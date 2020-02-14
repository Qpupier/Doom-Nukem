/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension_gif.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 10:26:54 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 15:18:50 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gif.h"

void				read_graphic_control_ext(t_gd_gif *gif)
{
	uint8_t			rdit;

	lseek(gif->fd, 1, SEEK_CUR);
	read(gif->fd, &rdit, 1);
	gif->gce.disposal = (rdit >> 2) & 3;
	gif->gce.input = rdit & 2;
	gif->gce.transparency = rdit & 1;
	gif->gce.delay = read_num(gif->fd);
	read(gif->fd, &gif->gce.tindex, 1);
	lseek(gif->fd, 1, SEEK_CUR);
}

void				read_application_ext(t_gd_gif *gif)
{
	char			app_id[8];
	char			app_auth_code[3];

	lseek(gif->fd, 1, SEEK_CUR);
	read(gif->fd, app_id, 8);
	read(gif->fd, app_auth_code, 3);
	if (!strncmp(app_id, "NETSCAPE", sizeof(app_id)))
	{
		lseek(gif->fd, 2, SEEK_CUR);
		gif->loop_count = read_num(gif->fd);
		lseek(gif->fd, 1, SEEK_CUR);
	}
	else
		discard_sub_blocks(gif);
}

void				read_ext(t_gd_gif *gif)
{
	uint8_t			label;

	read(gif->fd, &label, 1);
	if (label == 0x01)
		discard_sub_blocks(gif);
	else if (label == 0xF9)
		read_graphic_control_ext(gif);
	else if (label == 0xFE)
		discard_sub_blocks(gif);
	else if (label == 0xFF)
		read_application_ext(gif);
}

t_table				*new_table(int key_size)
{
	int				key;
	int				init_bulk;
	t_table			*table;

	init_bulk = (1 << (key_size + 1)) > (0x100) ?
		(1 << (key_size + 1)) : (0x100);
	if ((table = malloc(sizeof(*table) + sizeof(t_entry) * init_bulk)) == NULL)
		return (NULL);
	table->bulk = init_bulk;
	table->nentries = (1 << key_size) + 2;
	table->entries = (t_entry *)&table[1];
	key = 0;
	while (key < (1 << key_size))
	{
		table->entries[key] = (t_entry){1, 0xFFF, key};
		key++;
	}
	return (table);
}

int					add_entry(t_table **tablep, uint16_t length,
	uint16_t prefix, uint8_t suffix)
{
	t_table	*table;

	table = *tablep;
	if (table->nentries == table->bulk)
	{
		table->bulk *= 2;
		table = ft_realloc(table,
			sizeof(*table) + sizeof(t_entry) * table->bulk);
		if (!table)
			return (-1);
		table->entries = (t_entry *)&table[1];
		*tablep = table;
	}
	table->entries[table->nentries] = (t_entry){length, prefix, suffix};
	table->nentries++;
	if ((table->nentries & (table->nentries - 1)) == 0)
		return (1);
	return (0);
}
