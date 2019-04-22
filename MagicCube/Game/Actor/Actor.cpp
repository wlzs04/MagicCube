#include "Actor.h"
#include "../../ThreeParty/glm/glm.hpp"
#include "../../ThreeParty/glm/ext/matrix_transform.hpp"
#include "../../ThreeParty/glm/gtx/quaternion.hpp"
#include "../../ThreeParty/glm/gtx/transform.hpp"
#include "../../Manager/GraphicsManager.h"
#include "../../Common/Graphics/Mesh/MeshBase.h"
#include "../Material/Material.h"
#include "../Material/MaterialSlot.h"

Actor::Actor(wstring actorName)
{
	this->actorName = actorName;
}

wstring Actor::GetName()
{
	return actorName;
}

void Actor::SetMesh(MeshBase* newMesh)
{
	mesh = newMesh;
}
MeshBase* Actor::GetMesh()
{
	return mesh;
}

void Actor::SetMaterial(Material* newMaterial)
{
	material = newMaterial;
}

glm::mat4 Actor::GetLocalMatrix()
{
	return localMatrix;
}

glm::mat4 Actor::GetWorldMatrix()
{
	if (parentActor != nullptr)
	{
		return parentActor->GetWorldMatrix()* localMatrix;
	}
	else
	{
		return localMatrix;
	}
}

void Actor::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
	ResetLocalMatrix();
}

void Actor::SetRotation(glm::vec3 newRotation)
{
	rotationE = newRotation;
	ResetLocalMatrix();
}

void Actor::SetScale(glm::vec3 newScale)
{
	scale = newScale;
	ResetLocalMatrix();
}

void Actor::SetParent(Actor* newParentActor)
{
	if (parentActor != nullptr)
	{
		parentActor->RemoveChild(this);
		parentActor = nullptr;
	}
	parentActor = newParentActor;
}

Actor* Actor::GetParent()
{
	return parentActor;
}

void Actor::AddChild(Actor* childActor)
{
	if (childActor->GetParent() != this)
	{
		childActor->SetParent(this);
		childrenActorList.push_back(childActor);
	}
}

void Actor::RemoveChild(Actor* childActor)
{
	for (int i = 0; i < childrenActorList.size(); i++)
	{
		if (childrenActorList[i] == childActor)
		{
			childrenActorList.erase(childrenActorList.cbegin()+i);
			return;
		}
	}
}

void Actor::ResetLocalMatrix()
{
	localMatrix = glm::mat4(1.0f);

	localMatrix = glm::translate(localMatrix, position);

	glm::quat rotationQ = glm::quat(rotationE);
	glm::mat4 RotationMatrix = glm::toMat4(rotationQ);
	localMatrix = localMatrix * RotationMatrix;

	localMatrix = glm::scale(localMatrix, scale);
}

void Actor::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	if (material != nullptr)
	{
		MaterialSlotMatrix4* projectionSolt = material->GetMaterialSlot<MaterialSlotMatrix4>(L"projection");
		projectionSolt->SetValue(&projectionMatrix[0][0]);

		MaterialSlotMatrix4* viewSolt = material->GetMaterialSlot<MaterialSlotMatrix4>(L"view");
		viewSolt->SetValue(&viewMatrix[0][0]);

		MaterialSlotMatrix4* modelSolt = material->GetMaterialSlot<MaterialSlotMatrix4>(L"model");
		glm::mat4 meshMatrix = mesh->GetLocalMatrix();
		if (parentActor != nullptr)
		{
			meshMatrix = GetWorldMatrix() * meshMatrix;
		}
		modelSolt->SetValue(&(meshMatrix[0][0]));

		material->PrepareRender();
	}

	if (mesh != nullptr)
	{
		GraphicsManager::GetGraphicsApi()->DrawSprite(mesh->GetMeshId(), (int)mesh->GetIndices().size());
	}
}
