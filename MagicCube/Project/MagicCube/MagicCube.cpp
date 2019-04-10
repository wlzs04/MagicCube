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
	window->BindWindowInputKeyCallBack([this](int key, int action)-> void {InputCallBack(key, action); });
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
	camera->SetDirection(vec3(0,0,-1));
}

void MagicCube::Run()
{
	window->Run();
}

void MagicCube::End()
{
	window->Close();
}

void MagicCube::InputCallBack(int key, int action)
{
	//如果是按键传入为大写字母。
	switch (key)
	{
	case 27://'ESCAPE'
		End();
		break;
	default:
		break;
	}
}

void MagicCube::RunFunction()
{
	if (window->CheckInputKeyPressed('Q'))
	{
		camera->MovePosition(0, 0.1f, 0);
	}
	if (window->CheckInputKeyPressed('E'))
	{
		camera->MovePosition(0, -0.1f,0 );
	}
	if (window->CheckInputKeyPressed('W'))
	{
		camera->MovePosition(0, 0, -0.1f);
	}
	if (window->CheckInputKeyPressed('S'))
	{
		camera->MovePosition(0, 0, 0.1f);
	}
	if (window->CheckInputKeyPressed('A'))
	{
		camera->MovePosition(-0.1f, 0, 0);
	}
	if (window->CheckInputKeyPressed('D'))
	{
		camera->MovePosition(0.1f, 0, 0);
	}

	graphicsApi->ClearViewPort();
	shader->Use();
	//shader->SetFloat("ourColor", 0.5);

	// 在绑定纹理之前先激活纹理单元
	
	graphicsApi->SetTexture(0,texture);
	//shader->SetInt("texture0", 0); // 或者使用着色器类设置

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	shader->SetMatrix4("projection", projection);
	shader->SetMatrix4("view", camera->GetViewMatrix());
	shader->SetMatrix4("model", mesh->GetWorldMatrix());
	graphicsApi->DrawSprite(sprite);
}
