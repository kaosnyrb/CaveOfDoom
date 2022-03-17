//--------------------------------------------
// A sound
//--------------------------------------------
#include "Sound.h"


struct sample {
    Uint8 *data;
    Uint32 dpos;
    Uint32 dlen;
} sounds[TOTAL_SOUNDS];

Sound::Sound()
{
	ID = -1;
}

void Sound::LoadAndConvertSound(const char* Filename, SDL_AudioSpec *spec, int soundID)
{
	Uint8 *buffer;
	if ( SDL_LoadWAV(Filename,spec,&buffer,&playLength) == NULL )
	{
        fprintf(stderr, "Couldn't load %s: %s\n", Filename, SDL_GetError());
        return;
	}
	SDL_BuildAudioCVT(&cvt, spec->format, spec->channels, spec->freq,AUDIO_S16,2,22050);
    cvt.buf = (Uint8*)malloc(playLength*cvt.len_mult);
    memcpy(cvt.buf, buffer, playLength);
    cvt.len = playLength;
    SDL_ConvertAudio(&cvt);
    SDL_FreeWAV(buffer);
	ID = soundID;
}

void Sound::PlaySound()
{
	SDL_LockAudio();
    sounds[ID].data = cvt.buf;
    sounds[ID].dlen = cvt.len_cvt;
    sounds[ID].dpos = 0;
    SDL_UnlockAudio();
}

void Sound::AudioCallback(void *userdata, Uint8 *stream, int len)
{
	int i;
	Uint32 amount;

	for ( i=0; i<TOTAL_SOUNDS; ++i ) 
	{
		amount = (sounds[i].dlen-sounds[i].dpos);
		if ( amount > len ) 
		{
			amount = len;
		}
		SDL_MixAudio(stream, &sounds[i].data[sounds[i].dpos], amount, SDL_MIX_MAXVOLUME);
		sounds[i].dpos += amount;
	}
}

