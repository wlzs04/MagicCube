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

	localMatrix = glm::mat4(1.0f);
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

glm::mat4 MeshBase::GetLocalMatrix()
{
	return localMatrix;
}

void MeshBase::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
	ResetLocalMatrix();
}

void MeshBase::SetRotation(glm::vec3 newRotation)
{
	rotationE = newRotation;
	ResetLocalMatrix();
}

void MeshBase::SetScale(glm::vec3 newScale)
{
	scale = newScale;
	ResetLocalMatrix();
}

void MeshBase::ResetLocalMatrix()
{
	localMatrix = glm::mat4(1.0f);

	localMatrix = glm::translate(localMatrix, position);

	glm::quat rotationQ = glm::quat(rotationE);
	glm::mat4 RotationMatrix = glm::toMat4(rotationQ);
	localMatrix = localMatrix * RotationMatrix;

	localMatrix = glm::scale(localMatrix, scale);
}