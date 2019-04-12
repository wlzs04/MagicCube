#include "CommonHelper.h"
#include <direct.h>
#include <fstream> 
#include <sstream> 

string CommonHelper::GetCurrentPath()
{
	char buffer[_MAX_PATH];
	char* result = _getcwd(buffer, _MAX_PATH);
	return string(buffer);
}

string CommonHelper::LoadStringFromFile(string filePath)
{
	string value;
	ifstream fileStream;
	// 保证ifstream对象可以抛出异常：
	fileStream.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		fileStream.open(filePath);
		stringstream vShaderStream;
		vShaderStream << fileStream.rdbuf();
		fileStream.close();
		value = vShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		//报错
	}
	return value;
}
