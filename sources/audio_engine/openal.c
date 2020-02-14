/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   openal.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/16 10:05:52 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 17:26:38 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static int		al_clean_error(ALCdevice *audio_device,
	ALCcontext *audio_context, uint32_t type)
{
	if (type & 2)
		alcDestroyContext(audio_context);
	if (type & 1)
		alcCloseDevice(audio_device);
	return (0);
}

static int		al_set_listener(void)
{
	ALfloat listener[6];

	listener[0] = 0.0f;
	listener[1] = 0.0f;
	listener[2] = 1.0f;
	listener[3] = 0.0f;
	listener[4] = 1.0f;
	listener[5] = 0.0f;
	alListener3f(AL_POSITION, 0, 0, 0.0f);
	if (alGetError())
		return (0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	if (alGetError())
		return (0);
	alListenerfv(AL_ORIENTATION, listener);
	if (alGetError())
		return (0);
	return (1);
}

int				al_init(void)
{
	ALCdevice	*audio_device;
	ALCcontext	*audio_context;

	if (!(audio_device = alcOpenDevice(NULL)))
	{
		ft_putendl("[Audio Engine] OpenAL error opening device.");
		return (0);
	}
	if (!(audio_context = alcCreateContext(audio_device, NULL)))
	{
		ft_putendl("[Audio Engine] OpenAL error creating context.");
		return (al_clean_error(audio_device, audio_context, 1));
	}
	if (!alcMakeContextCurrent(audio_context))
	{
		ft_putendl("[Audio Engine] OpenAL context current error.");
		return (al_clean_error(audio_device, audio_context, 1 | 2));
	}
	if (!al_set_listener())
	{
		ft_putendl("[Audio Engine] Error setting listeners.");
		return (al_clean_error(audio_device, audio_context, 1 | 2));
	}
	return (1);
}
