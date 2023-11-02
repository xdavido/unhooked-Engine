#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"

#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"
#include "Primitive.h"

ModuleHierarchy::ModuleHierarchy(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleHierarchy::~ModuleHierarchy()
{
}

//-----------------------------------------------------------------
bool ModuleHierarchy::Start()
{


	bool ret = true;

	roots = new GameObject();
	roots->name = "Scene";

	return ret;
}

// -----------------------------------------------------------------
bool ModuleHierarchy::CleanUp()
{
	LOG("Cleaning Hierarchy");
	delete roots;
	return true;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::PreUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::Update(float dt)
{
	DrawHierarchy();

	if (App->input->GetKey(SDL_SCANCODE_DELETE))
	{
		delete objSelected;
		objSelected = nullptr;
	}

	if (objSelected != nullptr)
		objSelected->InspectorWindow();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleHierarchy::DrawHierarchy()
{
	if (ImGui::Begin("GameObjects Hierarchy")) {

		GameObjectTree(roots);
		if (objSelected != nullptr) {// don't show the option of creating a gameobj if nothing it's selected :)
			if (ImGui::BeginPopupContextWindow())
			{
				if (ImGui::Selectable("Create Object")) {
					GameObject* parent = objSelected;
					App->scene->createObj(parent);

					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
	}
	ImGui::End();


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

	if (obj->parent != nullptr) {

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("GameObject", obj, sizeof(GameObject*));

			TargetDropped = obj;
			ImGui::Text("Changing...");
			ImGui::EndDragDropSource();
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
		{
			SetGameObject(obj);
			if (objSelected != obj) {
				SetGameObject(objSelected);
			}

		}
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
