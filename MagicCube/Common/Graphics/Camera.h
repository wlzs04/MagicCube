#pragma once
#include "../../ThreeParty/glm/glm.hpp"
#include "../../ThreeParty/glm/gtc/matrix_transform.hpp"
#include "../../ThreeParty/glm/gtc/type_ptr.hpp"

using namespace glm;

class Camera
{
public:

	void SetPosition(vec3 newPosition);
	vec3 GetPosition();

private:
	vec3 position = vec3(0.0f, 0.0f, 0.0f);
};