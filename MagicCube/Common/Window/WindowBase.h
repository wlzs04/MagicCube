#pragma once
#include <string>
#include <functional>
#include "../../ThreeParty/glfw/glfw3.h"

//链接器默认从文件根路径开始，不需要添加../
//如果出现warning link 4099 原因是没有找到glfw3.lib相应的调试文件(.pdb)
//此文件在glfw源码进行编译后的目录中\src\glfw.dir\Debug\glfw.pdb
//将其复制到与.exe文件同一目录下即可。
#pragma comment(lib, "ThreeParty/glfw/glfw3.lib")

struct GLFWwindow;
using namespace std;

typedef function<void()> HandleEvent;
typedef function<void(int, int)> InputKeyHandleEvent;
typedef function<void(unsigned int)> InputCharHandleEvent;
typedef function<void(int, int)> ResizeHandleEvent;
typedef function<void(int, int)> ButtonHandleEvent;
typedef function<void(int, int)> PositionHandleEvent;
typedef function<void(int)> ScrollHandleEvent;

//窗体基类
class WindowBase
{
	friend class WindowManager;
public:
	~WindowBase();
	//初始化
	void Init(int width,int height,string title);
	//绑定窗体输入按键回调
	void BindWindowInputKeyCallBack(InputKeyHandleEvent inputCallback);
	//绑定窗体输入字符回调
	void BindWindowInputCharCallBack(InputCharHandleEvent inputCallback);
	//绑定窗体大小改变回调
	void BindWindowResizeCallBack(ResizeHandleEvent sizeChangeCallback);
	//绑定鼠标按钮回调
	void BindWindowMouseButtonCallBack(ButtonHandleEvent buttonCallback);
	//绑定鼠标位置改变回调
	void BindWindowMousePositionCallBack(PositionHandleEvent positionCallback);
	//绑定鼠标滚轮改变回调
	void BindWindowMouseScrollCallBack(ScrollHandleEvent scrollCallback);
	//绑定运行事件
	void BindRunFunction(HandleEvent runFunction);
	//检查指定键是否被按
	bool CheckInputKeyPressed(int key);

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
};