#include "COMP_Mesh.h"
#include "GameObject.h"
#include "ModuleFBX.h"

COMP_Mesh::COMP_Mesh() : Component(nullptr)
{
	owner = nullptr;
	mesh = nullptr;
}

COMP_Mesh::COMP_Mesh(GameObject* owner) : Component(owner)
{
	this->owner = owner;
	mesh = nullptr;
}



COMP_Mesh::~COMP_Mesh()
{
	mesh = nullptr;
}


void COMP_Mesh::Inspector()
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		ImGui::LabelText("##%f", "Number of vertex:");
		ImGui::SameLine();
		if (mesh == nullptr) return;
		ImGui::Text("%d", mesh->num_vertex);
	}
}

