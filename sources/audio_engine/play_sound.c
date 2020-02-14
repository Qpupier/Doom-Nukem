/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   play_sound.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 17:26:26 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 17:27:20 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

int				al_get_id(t_param *p)
{
	int		i;
	ALenum	state;

	i = -1;
	while (++i < 24)
	{
		alGetSourcei(p->audio_source[i], AL_SOURCE_STATE, &state);
		if (state == AL_PLAYING)
			continue ;
		else
			return (i);
	}
	return (-1);
}

void			play_sound(t_param *p, t_audio_sources audio,
	ALfloat pitch, ALfloat gain)
{
	int		id;

	if ((id = al_get_id(p)) == -1)
		return ;
	alSource3f(p->audio_source[id], AL_POSITION, 0, 0, 0);
	alSource3f(p->audio_source[id], AL_VELOCITY, 0, 0, 0);
	alSourcei(p->audio_source[id], AL_LOOPING, 0);
	alSourcef(p->audio_source[id], AL_PITCH, pitch);
	alSourcef(p->audio_source[id], AL_GAIN, gain);
	alBufferData(audio.buffer, audio.audio.format, (void *)audio.audio.buffer,
		audio.audio.size, audio.audio.frequency);
	alSourcei(p->audio_source[id], AL_BUFFER, audio.buffer);
	alSourcePlay(p->audio_source[id]);
}

int				al_isplaying(t_audio_sources audio_source)
{
	ALenum state;

	alGetSourcei(audio_source.source, AL_SOURCE_STATE, &state);
	return (state == AL_PLAYING);
}
