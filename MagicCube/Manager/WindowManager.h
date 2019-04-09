#include "../Common/Window/WindowBase.h"
#include <vector>
#include <unordered_map>
#pragma once

//控制台程序不显示控制台黑框 项目属性设置：链接器/系统/子系统/控制台改为窗体
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

//窗体管理器
class WindowManager
{
	friend class WindowBase;
public:
	static void Init();
	static void Clean();

	static WindowManager* GetInstance();
	
	//创建窗体
	WindowBase* CreateWindow(int width, int height, string title);
private:
	WindowManager() {};
	~WindowManager() {};

	//由WindowBase调用设置回调
	void SetWindowInputCallBack(WindowBase* window, InputHandleEvent inputCallBack);
	void SetWindowResizeCallBack(WindowBase* window,ResizeHandleEvent resizeCallBack);

	//静态回调方法
	static void WindowInputCallBack(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
	static void WindowResizeCallBack(GLFWwindow* glfwWindow, int width, int height);

	static WindowManager* windowManager;
	WindowBase* currentWindow = nullptr;

	vector<WindowBase*> windowList;
	unordered_map<GLFWwindow*, InputHandleEvent> windowInputMap;
	unordered_map<GLFWwindow*, ResizeHandleEvent> windowResizeMap;
};