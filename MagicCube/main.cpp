#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new  new(_CLIENT_BLOCK, __FILE__, __LINE__)

#include "Project/MagicCube.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MagicCube* magicCube=new MagicCube();
	magicCube->Init();
	magicCube->Run();

	delete magicCube;

	return 0;
}