#pragma once
#include<vector>
#include "../../../ThreeParty/glm/glm.hpp"
#include "../../Graphics/GraphicsApi.h"

using namespace std;

class MeshBase
{
public:
	MeshBase() {};
	~MeshBase();

	void SetData(vector<float> vertices, vector<unsigned int> indices, vector<VertexAttribute> attributes);
	vector<float>& GetVertices();
	vector<unsigned int>& GetIndices();

	int GetMeshId();

	void SetPosition(glm::vec3 newPosition);
	void SetRotation(glm::vec3 newRotation);
	void SetScale(glm::vec3 newScale);

	glm::mat4 GetWorldMatrix();
private:
	void ResetWorldMatrix();

	vector<float> vertices;
	vector<unsigned int> indices;

	vector<VertexAttribute> attributes;

	glm::vec3 position  = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotationE = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	glm::mat4 worldMatrix = glm::mat4(1);

	int meshId = 0;
};