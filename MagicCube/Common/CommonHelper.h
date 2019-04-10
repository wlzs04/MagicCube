#include <string>
#pragma once

using namespace std;

class CommonHelper
{
public:
	//获得当前项目路径，未测试中文路径
	static string GetCurrentPath();

	//获得数组长度
	template<class T>
	static int GetArrayLength(T& array)
	{
		return sizeof(array) / sizeof(array[0]);
	}

private:
	CommonHelper() {}
};