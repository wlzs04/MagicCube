#pragma once
#include<vector>
#include "../../../ThreeParty/glm/glm.hpp"

using namespace std;

class MeshBase
{
public:
	MeshBase() {};
	~MeshBase();

	void SetData(vector<float> vertices, vector<unsigned int> indices);
	vector<float>& GetVertices();
	vector<unsigned int>& GetIndices();

	void SetPosition(glm::vec3 newPosition);
	void SetRotation(glm::vec3 newRotation);
	void SetScale(glm::vec3 newScale);

	glm::mat4 GetWorldMatrix();
private:
	void ResetWorldMatrix();

	vector<float> vertices;
	vector<unsigned int> indices;

	glm::vec3 position  = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	glm::mat4 worldMatrix = glm::mat4(1);
};