#include "MeshBase.h"
#include "../../../ThreeParty/glm/glm.hpp"
#include "../../../ThreeParty/glm/ext/matrix_transform.hpp"
#include "../../../ThreeParty/glm/gtc/type_ptr.hpp"
#include "../../../ThreeParty/glm/gtx/quaternion.hpp"
#include "../../../Manager/GraphicsManager.h"

MeshBase::~MeshBase()
{
}

void MeshBase::SetData(vector<float> vertices, vector<unsigned int> indices ,vector<VertexAttribute> attributes)
{
	this->vertices = vertices;
	this->indices = indices;
	this->attributes = attributes;

	meshId = GraphicsManager::GetGraphicsApi()->GetSprite(GetVertices(), GetIndices(), attributes, 5);

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

int MeshBase::GetMeshId()
{
	return meshId;
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
	rotationE = newRotation;
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

	glm::quat rotationQ = glm::quat(rotationE);
	glm::mat4 RotationMatrix = glm::toMat4(rotationQ);
	worldMatrix = worldMatrix * RotationMatrix;

	worldMatrix = glm::scale(worldMatrix, scale);
	
}