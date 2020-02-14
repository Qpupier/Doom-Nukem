/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_wav.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 09:29:04 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 10:33:51 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static int		check_header(t_riff_hdr *riff, t_format_hdr *fmt)
{
	if ((riff->riff[0] == 'R' && riff->riff[1] == 'I'
		&& riff->riff[2] == 'F' && riff->riff[3] == 'F')
	&&
		(riff->wave[0] == 'W' && riff->wave[1] == 'A'
		&& riff->wave[2] == 'V' && riff->wave[3] == 'E')
	&&
		(fmt->fmt_txt[0] == 'f' && fmt->fmt_txt[1] == 'm'
		&& fmt->fmt_txt[2] == 't'))
		return (1);
	return (0);
}

static int		parse_header(int fd, t_riff_hdr *riff, t_format_hdr *fmt,
	t_data_hdr *data)
{
	if (!read(fd, &riff->riff, sizeof(uint8_t) * 4)
		|| !read(fd, &riff->size, sizeof(uint32_t))
		|| !read(fd, &riff->wave, sizeof(uint8_t) * 4)
		|| !read(fd, &fmt->fmt_txt, sizeof(uint8_t) * 4)
		|| !read(fd, &fmt->size, sizeof(uint32_t))
		|| !read(fd, &fmt->audio_fmt, sizeof(uint16_t))
		|| !read(fd, &fmt->channel, sizeof(uint16_t))
		|| !read(fd, &fmt->sampling_f, sizeof(uint32_t))
		|| !read(fd, &fmt->byte_rate, sizeof(uint32_t))
		|| !read(fd, &fmt->block_align, sizeof(uint16_t))
		|| !read(fd, &fmt->bits_per_sample, sizeof(uint16_t))
		|| !read(fd, &data->id, sizeof(uint8_t) * 4)
		|| !read(fd, &data->size, sizeof(uint32_t)))
		return (0);
	return (check_header(riff, fmt));
}

static int		show_error(const char *file)
{
	ft_putstr("[Audio Engine] Parsing file " STYLE_BOLD);
	ft_putstr(file);
	ft_putstr(COLOR_RESET " has failed. Exiting.\n");
	return (0);
}

int				al_load_wav(t_audio_sources *audio_source, const char *file)
{
	int				fd;
	t_riff_hdr		riff;
	t_format_hdr	fmt;
	t_data_hdr		data;
	long int		esize;

	if ((fd = open(file, O_RDONLY)) == -1
		|| !parse_header(fd, &riff, &fmt, &data))
		return (show_error(file) + (close(fd) ? 0 : 0));
	esize = (riff.size - 44 + 8);
	if (riff.size - esize == 36)
	{
		if (!(audio_source->audio.buffer = malloc(sizeof(uint8_t) * esize)))
			return (close(fd) ? 0 : 0);
		if (!(read(fd, audio_source->audio.buffer, esize)))
		{
			free(audio_source->audio.buffer);
			return (close(fd) ? 0 : 0);
		}
		al_set_data(audio_source, fmt, esize);
		return (al_gen_source_buffer(audio_source) + (close(fd) ? 0 : 0));
	}
	return (close(fd) ? 0 : 0);
}
