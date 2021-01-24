#include "globals.h"
#include "game.h"


int main(int argc, char* args[]) {
	
	// allows for memory debuging
	#if defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	Game* game = DBG_NEW Game();
	game->play();
	delete game;

	system("pause");

	return 0;
}