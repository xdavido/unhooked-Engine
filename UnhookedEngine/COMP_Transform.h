#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "MathGeoLib/include/Math/float3.h"
#include "MathGeoLib/include/Math/float3x4.h"
#include "MathGeoLib/include/Math/Quat.h"
#include "ImGui/imgui.h"
#include "glmath.h"


class GameObject;
class Component;


class COMP_Transform : public Component
{
public:

	COMP_Transform();
	COMP_Transform(GameObject* owner);
	~COMP_Transform();

	mat4x4 lTransform;

	vec3 position, scale, rotation;

	void SetTransformMatrix(vec3 _position, vec3 _rotation, vec3 _scale);

	void Inspector();

}; 
