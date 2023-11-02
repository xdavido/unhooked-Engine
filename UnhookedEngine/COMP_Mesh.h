#pragma once
#include "Globals.h"
#include "Component.h"
#include "ImGui/imgui.h"
#include "Primitive.h"
#include "glmath.h"

#include <vector>

class GameObject;
class Component;
struct MeshData;

enum class Mesh_Type
{
	FBX,
	CUBE,
	SPHERE,
	CYLINDER,
	LINE,
	PLANE,
};

class COMP_Mesh: public Component
{
public:

	COMP_Mesh();
	COMP_Mesh(GameObject* owner);
	~COMP_Mesh();

	Mesh_Type mType;
	MeshData* mesh;
	
	std::vector<MeshData*> meshes;

	Primitive* GO_Primitive;

	/*void UpdateAABB();
	void CreatePrimitive();*/
	
	void Inspector();
};