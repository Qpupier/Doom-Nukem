/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   buffer_init.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 09:43:54 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 10:37:00 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void		al_set_data(t_audio_sources *audio_source, t_format_hdr fmt,
	long int esize)
{
	ALenum		format;

	audio_source->audio.size = esize;
	audio_source->audio.frequency = fmt.sampling_f;
	if (fmt.bits_per_sample == 8)
		format = fmt.channel == 2 ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
	else
		format = fmt.channel == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
	audio_source->audio.format = format;
}

static int	al_clean_error(t_audio_sources *audio_source, uint32_t type)
{
	ft_putendl("An error occured during OpenAL initialization. Cleaning.\n");
	if (type & 1)
		alDeleteSources(1, &audio_source->source);
	if (type & 2)
		alDeleteBuffers(1, &audio_source->buffer);
	if (type & 4 && audio_source->audio.buffer)
		free(audio_source->audio.buffer);
	return (1);
}

static int	al_gen_source(t_audio_sources *audio_source)
{
	alGenSources(1, &audio_source->source);
	if (alGetError() && al_clean_error(audio_source, 4))
		return (0);
	alSource3f(audio_source->source, AL_POSITION, 0, 0, 0);
	if (alGetError() && al_clean_error(audio_source, 1 | 4))
		return (0);
	alSource3f(audio_source->source, AL_VELOCITY, 0, 0, 0);
	if (alGetError() && al_clean_error(audio_source, 1 | 4))
		return (0);
	alSourcei(audio_source->source, AL_LOOPING, 0);
	if (alGetError() && al_clean_error(audio_source, 1 | 4))
		return (0);
	return (1);
}

int			al_gen_source_buffer(t_audio_sources *audio_source)
{
	if (!al_gen_source(audio_source))
		return (0);
	alGenBuffers(1, &audio_source->buffer);
	if (alGetError() && al_clean_error(audio_source, 1 | 4))
		return (0);
	alBufferData(audio_source->buffer, audio_source->audio.format,
				(void *)audio_source->audio.buffer, audio_source->audio.size,
				audio_source->audio.frequency);
	if (alGetError() && al_clean_error(audio_source, 1 | 2 | 4))
		return (0);
	free(audio_source->audio.buffer);
	alSourcei(audio_source->source, AL_BUFFER, audio_source->buffer);
	if (alGetError() && al_clean_error(audio_source, 1 | 2))
		return (0);
	return (1);
}
