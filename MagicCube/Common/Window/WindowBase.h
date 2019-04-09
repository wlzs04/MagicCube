#pragma once
#include <string>
#include <functional>
#include "../../ThreeParty/GLFW/glfw3.h"

#pragma comment(lib, "ThreeParty/GLFW/glfw3.lib")

struct GLFWwindow;
using namespace std;

typedef function<void()> HandleEvent;
typedef function<void(int, int)> InputHandleEvent;
typedef function<void(int, int)> ResizeHandleEvent;

//窗体基类
class WindowBase
{
	friend class WindowManager;
public:
	~WindowBase();
	//初始化
	void Init(int width,int height,string title);
	//绑定窗体大小改变回调
	void BindWindowResizeCallBack(ResizeHandleEvent sizeChangeCallback);
	//绑定窗体输入回调
	void BindWindowInputCallBack(InputHandleEvent inputCallback);
	//绑定运行事件
	void BindRunFunction(HandleEvent runFunction);

	//运行
	void Run();
	//关闭窗体
	void Close();

	GLFWwindow* GetGLFWwindow();
private:
	WindowBase() {}
	//销毁
	void Destroy();

	GLFWwindow* glfwWindow = nullptr;
	int width = 0;
	int height = 0;
	string title;
	bool haveCreate = false;

	HandleEvent runFunction;
	InputHandleEvent inputCallback;
};