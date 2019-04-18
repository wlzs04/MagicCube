#include <string>
#pragma once

using namespace std;

class ProjectConfig
{
public:
	void LoadFromLLXMLNode(wstring filePath);

	wstring GetProjectName();
	bool GetFullScreen();
	int GetWidth();
	int GetHeight();
	bool GetCanResize();
	bool GetShowBorder();
private:
	wstring projectName = L"未命名";
	bool fullScreen = false;
	int width = 800;
	int height = 600;
	bool canResize = true;
	bool showBorder = true;
};