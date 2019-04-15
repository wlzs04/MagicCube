#include "CommonHelper.h"
#include <direct.h>
#include <fstream> 
#include <sstream> 

wstring CommonHelper::GetCurrentPath()
{
	wchar_t buffer[_MAX_PATH];
	wchar_t* result = _wgetcwd(buffer, _MAX_PATH);
	return wstring(buffer);
}

wstring CommonHelper::LoadStringFromFile(wstring filePath)
{
	wstring value;
	wifstream fileStream;
	// 保证ifstream对象可以抛出异常：
	fileStream.exceptions(wifstream::failbit | wifstream::badbit);
	try
	{
		fileStream.open(filePath);
		wstringstream vShaderStream;
		vShaderStream << fileStream.rdbuf();
		fileStream.close();
		value = vShaderStream.str();
	}
	catch (wifstream::failure e)
	{
		//报错
	}
	return value;
}
