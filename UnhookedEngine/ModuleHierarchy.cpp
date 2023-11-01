#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleHierarchy.h"
#include "COMP_Mesh.h"
#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"
#include "Primitive.h"

ModuleHierarchy::ModuleHierarchy(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	roots = nullptr;
	//objPicked = nullptr;
	objSelected = nullptr;
}

ModuleHierarchy::~ModuleHierarchy()
{
}

bool ModuleHierarchy::Start()
{
	//LOG("Setting up the hierarchy");
	bool ret = true;

	roots = new GameObject();
	roots->name = "Scene";

	return ret;
}


bool ModuleHierarchy::CleanUp()
{
	LOG("Cleaning Hierarchy");
	delete roots;
	return true;
}


update_status ModuleHierarchy::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}


update_status ModuleHierarchy::Update(float dt)
{


	if (App->editor->GetKey(SDL_SCANCODE_DELETE))
	{
		delete objSelected;
		objSelected = nullptr;
	}

	if (objSelected != nullptr)
		objSelected->InspectorWindow();

	return UPDATE_CONTINUE;
}


update_status ModuleHierarchy::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}



void ModuleHierarchy::GameObjectTree(GameObject* obj)
{
	ImGuiTreeNodeFlags flag_TNode = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow;

	bool clown;

	if (obj->mParent == nullptr) {
		flag_TNode |= ImGuiTreeNodeFlags_DefaultOpen;
	}
	else {
		flag_TNode |= ImGuiTreeNodeFlags_OpenOnArrow;
	}

	if (obj == objSelected) {
		flag_TNode |= ImGuiTreeNodeFlags_Selected;
	}

	if (obj->mChildren.size() != 0)
		clown = ImGui::TreeNodeEx(obj, flag_TNode, obj->name.c_str());

	else {
		flag_TNode |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx(obj, flag_TNode, obj->name.c_str());
		clown = false;
	}

	if (obj->mParent != nullptr) {

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("GameObject", obj, sizeof(GameObject*));

			objPicked = obj;//the obj we move
			ImGui::EndDragDropSource();
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
		{
			objDropped = obj;
			SetGameObject(obj);
			/*if (objSelected != obj) {
				SetGameObject(objSelected);
			}	*/
		}
	}

	if (ImGui::BeginDragDropTarget()) {
		if (const ImGuiPayload* PL = ImGui::AcceptDragDropPayload("GameObject")) {
			objPicked->NewChild(objDropped);
			//objPicked = nullptr;
		}
		ImGui::EndDragDropTarget();
	}
	if (clown)
	{
		if (!obj->mChildren.empty()) {
			for (unsigned int i = 0; i < obj->mChildren.size(); i++)
			{
				GameObjectTree(obj->mChildren[i]);
			}
		}
		ImGui::TreePop();
	}
}

void ModuleHierarchy::SetGameObject(GameObject* obj)
{
	objSelected = obj;
}