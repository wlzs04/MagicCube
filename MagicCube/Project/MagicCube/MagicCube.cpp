#include "MagicCube.h"
#include "../../Common/CommonHelper.h"
#include "../../Manager/WindowManager.h"
#include "../../Manager/GraphicsManager.h"
#include "../../Manager/MeshManager.h"
#include "../../Common/Graphics/GraphicsApi.h"
#include "../../Common/Graphics/Camera.h"
#include "../../ThreeParty/glm/ext/matrix_transform.hpp"
#include "../../ThreeParty/glm/gtc/type_ptr.hpp"
#include <functional>

MagicCube::MagicCube()
{
	WindowManager::Init();
	GraphicsManager::Init();
	MeshManager::Init();

	camera = new Camera();
}

MagicCube::~MagicCube()
{
	GraphicsManager::Clean();
	WindowManager::Clean();
	MeshManager::Clean();
	delete camera;
}

void MagicCube::Init()
{
	window = WindowManager::GetInstance()->CreateWindow(800, 600, "领会");
	window->BindWindowInputKeyCallBack([this](int key, int action)-> void {InputKeyCallBack(key, action); });
	window->BindWindowMouseButtonCallBack([this](int key, int action)-> void {MouseButtonCallBack(key, action); });
	window->BindWindowMousePositionCallBack([this](double xPosition,double yPosition)-> void {MousePositionCallBack(xPosition, yPosition); });
	window->BindRunFunction([this]()-> void {RunFunction(); });

	GraphicsManager::SetGraphicsApiType(GraphicsApiType::OpenGL);
	graphicsApi = GraphicsManager::GetGraphicsApi();
	
	string vsPath = CommonHelper::GetCurrentPath() + "/Project/MagicCube/Shader/Cube.vs";
	string fsPath = CommonHelper::GetCurrentPath() + "/Project/MagicCube/Shader/Cube.fs";

	string imagePath = CommonHelper::GetCurrentPath() + "/Project/MagicCube/Texture/me.jpg";
	
	shader = graphicsApi->LoadShader(vsPath, fsPath);
	texture = graphicsApi->LoadTexture(imagePath);
	mesh = MeshManager::GetInstance()->CreateCube();

	vector<VertexAttribute> attributes;
	attributes.push_back(VertexAttribute(0, 3));
	attributes.push_back(VertexAttribute(1, 2));

	sprite = graphicsApi->GetSprite(mesh->GetVertices(),mesh->GetIndices(), attributes,5);
	camera->SetPosition(vec3(0, 0, 5));
	camera->SetDirection(vec3(0, 0, -1));
}

void MagicCube::Run()
{
	window->Run();
}

void MagicCube::End()
{
	window->Close();
}

void MagicCube::InputKeyCallBack(int key, int action)
{
	//如果是按键传入为大写字母。
	switch (key)
	{
	case GLFW_KEY_ESCAPE://'ESCAPE'
		End();
		break;
	default:
		break;
	}
}

void MagicCube::MouseButtonCallBack(int key, int action)
{
	if (key == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			moveCamera = true;
		}
		else if(action == GLFW_RELEASE)
		{
			moveCamera = false;
		}
	}
}

void MagicCube::MousePositionCallBack(double xPosition, double yPosition)
{
	if (moveCamera)
	{
		float rateX = -0.01f;
		float rateY = 0.01f;

		float moveX = xPosition - lastMousePosition.x;
		float moveY = yPosition - lastMousePosition.y;

		float angleYaw = moveX * rateX;
		float anglePitch = moveY * rateY;

		camera->RotationY(angleYaw);
		camera->Pitch(anglePitch);
	}
	lastMousePosition = glm::vec2(xPosition, yPosition);
}

void MagicCube::RunFunction()
{
	if (window->CheckInputKeyPressed('Q'))
	{
		camera->Rise(-1);
	}
	if (window->CheckInputKeyPressed('E'))
	{
		camera->Rise(1);
	}
	if (window->CheckInputKeyPressed('W'))
	{
		camera->Walk(1);
	}
	if (window->CheckInputKeyPressed('S'))
	{
		camera->Walk(-1);
	}
	if (window->CheckInputKeyPressed('A'))
	{
		camera->Strafe(1);
	}
	if (window->CheckInputKeyPressed('D'))
	{
		camera->Strafe(-1);
	}

	graphicsApi->ClearViewPort();
	shader->Use();
	//shader->SetFloat("ourColor", 0.5);

	// 在绑定纹理之前先激活纹理单元
	
	graphicsApi->SetTexture(0,texture);
	//shader->SetInt("texture0", 0); // 或者使用着色器类设置

	shader->SetMatrix4("projection", camera->GetProjectMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	shader->SetMatrix4("model", mesh->GetWorldMatrix());
	graphicsApi->DrawSprite(sprite);
}