//#pragma once
//#include "Globals.h"
//#include "Component.h"
//#include "ImGui/imgui.h"
//#include "Assimp/include/cimport.h"
//#include "Assimp/include/scene.h"
//#include "Assimp/include/mesh.h"
//#include "Assimp/include/postprocess.h"
//
//#include "MathGeoLib/include/MathGeoLib.h"
//#include "MathGeoLib/include/Math/float3x3.h"
//#include "MathGeoLib/include/Math/float4x4.h"
//#include "Primitive.h"
//
//#include "Glew/include/glew.h"
//class GameObject;
//class Component;
//
//class COMP_Camera : public Component
//{
//public:
//
//	COMP_Camera();
//	COMP_Camera(GameObject* owner);
//	~COMP_Camera();
//
//	void SetCam();
//	void GenBuffer();
//
//	float* GetViewMatrix();
//	float* GetProjectionMatrix();
//
//	void LookAt(const float3& target);
//
//	void TransformCam();
//
//
//	bool ContainsAaBox(MeshData* refBox);
//
//	Frustum FrustumCam;
//	float4x4 viewMatrix;
//	float4x4 projectionMatrix;
//
//	int printCount;
//
//	int FOV = 60.0f;
//
//	unsigned int cameraBuffer;
//	unsigned int frameBuffer;
//
//private:
//
//	unsigned int renderObjBuffer;
//};