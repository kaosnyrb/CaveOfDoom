//---------------------------------------------------
//A sound
//---------------------------------------------------
#include <SDL.h>
#include <sdl_audio.h>
#include <malloc.h>
#include <string.h>

#ifndef _SOUND_H
#define _SOUND_H

#define TOTAL_SOUNDS 2

class Sound
{
	public:
		Sound();
		void LoadAndConvertSound(const char* Filename, SDL_AudioSpec *spec,int soundID);
		void PlaySound();
		static void AudioCallback(void *userdata, Uint8 *stream, int len);
	private:
	 
	 Uint32 playLength;
	 SDL_AudioCVT cvt;
	 int ID;
};

#endif
