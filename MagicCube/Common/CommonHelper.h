#pragma once
#include <string>

using namespace std;

class CommonHelper
{
public:
	//获得当前项目路径，未测试中文路径
	static wstring GetCurrentPath();

	//从文件中读取字符串
	//如果这样使用：char* tempValue = CommonHelper::LoadStringFromFile().c_str();
	//tempValue指向的内存可能被销毁
	static wstring LoadStringFromFile(wstring filePath);

	//获得数组长度，但参数是指针则无法获得正确长度，如int* a = new int[10];
	template<class T>
	static int GetArrayLength(T& array)
	{
		return sizeof(array) / sizeof(array[0]);
	}

private:
	CommonHelper() {}
};