#ifndef Game_h
#define Game_h

#include <cstdio>
#include "Sprite.h"

class Game
{
public: 

	~Game();
	
	static Game	*init();
	static Game	*getInstance();
	static void		destroy();
	
	Sprite *hero;
	
private:

	static Game	*instance;
	Game();
		
		
};

#endif // Game_h