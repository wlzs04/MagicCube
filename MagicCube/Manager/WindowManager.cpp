#include "WindowManager.h"

WindowManager* WindowManager::windowManager = nullptr;

void WindowManager::SetWindowInputCallBack(WindowBase* window, InputHandleEvent inputCallBack)
{
	windowInputMap[window->GetGLFWwindow()] = inputCallBack;
}

void WindowManager::SetWindowResizeCallBack(WindowBase* window, ResizeHandleEvent resizeCallBack)
{
	windowResizeMap[window->GetGLFWwindow()] = resizeCallBack;
}

void WindowManager::WindowInputCallBack(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
{
	if (WindowManager::GetInstance()->windowInputMap.count(glfwWindow) > 0)
	{
		WindowManager::GetInstance()->windowInputMap[glfwWindow](key, action);
	}
}

void WindowManager::WindowResizeCallBack(GLFWwindow* glfwWindow, int width, int height)
{
	if (WindowManager::GetInstance()->windowResizeMap.count(glfwWindow) > 0)
	{
		WindowManager::GetInstance()->windowResizeMap[glfwWindow](width, height);
	}
}

void WindowManager::Init()
{
	if (windowManager == nullptr)
	{
		windowManager = new WindowManager();
	}
}

void WindowManager::Clean()
{
	if (windowManager != nullptr)
	{
		for (auto window : windowManager->windowList)
		{
			delete window;
		}
		delete windowManager;
		windowManager = nullptr;
	}
}

WindowManager* WindowManager::GetInstance()
{
	return windowManager;
}

WindowBase* WindowManager::CreateWindow(int width, int height, string title)
{
	WindowBase* window = new WindowBase();
	window->Init(width, height, title);

	windowList.push_back(window);
	return window;
}
