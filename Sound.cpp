#include "Sound.h"


SoundManager* SoundManager::s_pInstance = 0;

SoundManager::SoundManager()
{
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}


bool SoundManager::load(std::string fileName, int nr)
{
	Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
	if (pChunk == 0)
	{
		std::cout << "Could not load SFX: ERROR - "<< Mix_GetError() << std::endl;
		return false;
	}
	chunk[nr] = pChunk;		//garso effektu masyvas
	return true;
}


void SoundManager::playSound(int kanalas,int id, int loop)
{
	Mix_PlayChannel(kanalas, chunk[id], loop);
}


SoundManager::~SoundManager()
{
	Mix_CloseAudio();
	for (int i = 0; i < 10; i++)
	{
		Mix_FreeChunk(chunk[i]);
	}
}