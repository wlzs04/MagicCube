#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new  new(_CLIENT_BLOCK, __FILE__, __LINE__)

#include "Project/MagicCube/MagicCubeProject.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MagicCubeProject* magicCube=new MagicCubeProject();
	magicCube->Init();
	magicCube->StartRun();

	delete magicCube;

	return 0;
}