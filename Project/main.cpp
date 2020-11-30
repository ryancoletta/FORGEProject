#include "game.h"
#include "globals.h"


// const expressions - type safe "macros" or constants

int main(int argc, char* args[]) {
	
	#if defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	malloc(5000);

	Game game;

	#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
	#endif

	return 0;
}