#include "MainHeader.h"

class SoundManager
{
private:
	static SoundManager* s_pInstance;
	Mix_Chunk* chunk[10];
public:
	SoundManager();
	~SoundManager();
	bool load(std::string pav, int nr);
	void playSound(int kanalas, int id, int loop);

	static SoundManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new SoundManager();
			return s_pInstance;
		}
		return s_pInstance;
	}
};