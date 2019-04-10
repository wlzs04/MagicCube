#include "CommonHelper.h"
#include <direct.h>

string CommonHelper::GetCurrentPath()
{
	char buffer[_MAX_PATH];
	printf(_getcwd(buffer, _MAX_PATH));
	return string(buffer);
}