#pragma once
#include "../../ThreeParty/glm/glm.hpp"

class WindowBase;
class GraphicsApi;
class Shader;
class Texture;
class Sprite;
class MeshBase;
class Camera;

class MagicCube
{
public:
	MagicCube();
	~MagicCube();

	//初始化
	void Init();
	//运行
	void Run();
	//结束
	void End();
private:
	void InputKeyCallBack(int key, int action);
	void MouseButtonCallBack(int key,int action);
	void MousePositionCallBack(double xPosition, double yPosition);

	void RunFunction();

	WindowBase* window = nullptr;
	GraphicsApi* graphicsApi = nullptr;
	Shader* shader = nullptr;
	Texture* texture = nullptr;
	Sprite* sprite = nullptr;
	MeshBase* mesh = nullptr;
	Camera* camera = nullptr;

	glm::vec2 lastMousePosition = glm::vec2(0);
	bool moveCamera = false;
};