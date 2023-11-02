#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "MathGeoLib/include/Math/float3.h"
#include "MathGeoLib/include/Math/float3x4.h"
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

	float4x4 lTransform;

	float3 position, scale, rotation;

	void SetTransformMatrix(float3 _position, float3 _rotation, float3 _scale);

	//float4x4 GetTransformMatrix();

	void Inspector();

}; 
