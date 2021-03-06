#include "WindowManager.h"

WindowManager* WindowManager::windowManager = nullptr;

void WindowManager::SetWindowInputKeyCallBack(WindowBase* window, InputKeyHandleEvent inputKeyCallBack)
{
	windowInputKeyMap[window->GetGLFWwindow()] = inputKeyCallBack;
}

void WindowManager::SetWindowInputCharCallBack(WindowBase* window, InputCharHandleEvent inputCharCallBack)
{
	windowInputCharMap[window->GetGLFWwindow()] = inputCharCallBack; ;
}

void WindowManager::SetWindowResizeCallBack(WindowBase* window, ResizeHandleEvent resizeCallBack)
{
	windowResizeMap[window->GetGLFWwindow()] = resizeCallBack;
}

void WindowManager::SetWindowMouseButtonCallBack(WindowBase* window, ButtonHandleEvent buttonCallBack)
{
	windowButtonMap[window->GetGLFWwindow()] = buttonCallBack;
}

void WindowManager::SetWindowMousePositionCallBack(WindowBase* window, PositionHandleEvent positionCallBack)
{
	windowPositionMap[window->GetGLFWwindow()] = positionCallBack;
}

void WindowManager::SetWindowMouseScrollCallBack(WindowBase* window, ScrollHandleEvent scrollCallBack)
{
	windowScrollMap[window->GetGLFWwindow()] = scrollCallBack;
}

void WindowManager::WindowInputKeyCallBack(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
{
	if (WindowManager::GetInstance()->windowInputKeyMap.count(glfwWindow) > 0)
	{
		WindowManager::GetInstance()->windowInputKeyMap[glfwWindow](key, action);
	}
}

void WindowManager::WindowInputCharCallBack(GLFWwindow* glfwWindow, unsigned int charValue)
{
	if (WindowManager::GetInstance()->windowInputCharMap.count(glfwWindow) > 0)
	{
		WindowManager::GetInstance()->windowInputCharMap[glfwWindow](charValue);
	}
}

void WindowManager::WindowResizeCallBack(GLFWwindow* glfwWindow, int width, int height)
{
	if (WindowManager::GetInstance()->windowResizeMap.count(glfwWindow) > 0)
	{
		WindowManager::GetInstance()->windowResizeMap[glfwWindow](width, height);
	}
}

void WindowManager::WindowMouseButtonCallBack(GLFWwindow* glfwWindow, int button, int action, int mods)
{
	if (WindowManager::GetInstance()->windowButtonMap.count(glfwWindow) > 0)
	{
		WindowManager::GetInstance()->windowButtonMap[glfwWindow](button, action);
	}
}

void WindowManager::WindowMousePositionCallBack(GLFWwindow* glfwWindow, double xPosition, double yPosition)
{
	if (WindowManager::GetInstance()->windowPositionMap.count(glfwWindow) > 0)
	{
		WindowManager::GetInstance()->windowPositionMap[glfwWindow](xPosition, yPosition);
	}
}

void WindowManager::WindowMouseScrollCallBack(GLFWwindow* glfwWindow, double xoffset, double yoffset)
{
	if (WindowManager::GetInstance()->windowScrollMap.count(glfwWindow) > 0)
	{
		WindowManager::GetInstance()->windowScrollMap[glfwWindow](yoffset);
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

WindowBase* WindowManager::CreateWindow(int width, int height, wstring title, bool fullSceen, bool canResize, bool showBorder)
{
	WindowBase* window = new WindowBase();
	window->Init(width, height, title, fullSceen, canResize, showBorder);

	windowList.push_back(window);
	return window;
}
