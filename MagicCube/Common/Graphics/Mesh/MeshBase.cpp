#include "MeshBase.h"
#include "../../../ThreeParty/glm/ext/matrix_transform.hpp"

MeshBase::~MeshBase()
{
}

void MeshBase::SetData(vector<float> vertices, vector<unsigned int> indices)
{
	this->vertices = vertices;
	this->indices = indices;

	worldMatrix = glm::mat4(1.0f);
}

vector<float>& MeshBase::GetVertices()
{
	return this->vertices;
}

vector<unsigned int>& MeshBase::GetIndices()
{
	return this->indices;
}

glm::mat4 MeshBase::GetWorldMatrix()
{
	return worldMatrix;
}

void MeshBase::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
	ResetWorldMatrix();
}

void MeshBase::SetRotation(glm::vec3 newRotation)
{
	rotation = newRotation;
	ResetWorldMatrix();
}

void MeshBase::SetScale(glm::vec3 newScale)
{
	scale = newScale;
	ResetWorldMatrix();
}

void MeshBase::ResetWorldMatrix()
{
	worldMatrix = glm::mat4(1.0f);
	worldMatrix = glm::translate(worldMatrix, position);
}