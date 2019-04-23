#pragma once
#include <vector>
#include "../../Game/Actor/Actor.h"
#include "../../ThreeParty/glm/glm.hpp"

class MagicChildCubeActor :public Actor
{
public:
	MagicChildCubeActor(wstring actorName);
	~MagicChildCubeActor();

	void SetRowColDep(int row, int col,int dep);
	void SetColorByIndex(int index,glm::vec4 color);

	void Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) override;
private:
	vector<Actor*> planeList;
	vector<Material*> materialList;

	int row = 0;
	int col = 0;
	int dep = 0;

	glm::vec4 redColor = glm::vec4(1, 0, 0, 1);
	glm::vec4 greenColor = glm::vec4(0, 1, 0, 1);
	glm::vec4 blueColor = glm::vec4(0, 0, 1, 1);
	glm::vec4 yellowColor = glm::vec4(1, 1, 0, 1);
	glm::vec4 pinkColor = glm::vec4(1, 0, 1, 1);
	glm::vec4 GrayColor = glm::vec4(0.5f, 0.5f, 0.5f, 1);
	glm::vec4 whiteColor = glm::vec4(1, 1, 1, 1);
};