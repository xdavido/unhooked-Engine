#pragma once
#include "Globals.h"
#include "ImGui/imgui.h"
#include "Component.h"
#include "COMP_Transform.h"
#include <vector>
#include <string>
enum class COMP_Type;
class Component;
class COMP_Transform;
class COMP_Mesh;
//class COMP_Camera;

class GameObject
{
public:
	GameObject();
	~GameObject();
	
	GameObject(GameObject* parent);

	void AddComponent(COMP_Type type);

	GameObject* mParent;
	std::vector<GameObject*> mChildren;
	std::vector<Component*> mComponents;

	COMP_Transform* mTransform;

	std::string name;
	char string[128] = "Game_Object";

	//void DeleteChild(GameObject* child);
	//bool ChangeParent(GameObject* NewParent);
	//bool CheckChildOf(GameObject* parent);

	//void DeleteChild(GameObject child);

	GameObject* GetParent();
	//COMP_Mesh* GetComponentMesh();
	//GameObject* GetCompMesh();

	bool fixed;

	//void FixRotationYZ();

	//void UpdateRecu();

	void InspectorWindow();
}