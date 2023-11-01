#include "Application.h"
#include "COMP_Texture.h"
#include "COMP_Mesh.h"
#include "GameObject.h"
#include "ModuleFBX.h"


COMP_Texture::COMP_Texture() : Component(nullptr)
{
	type = COMP_Type::TEXTURE;
	owner = nullptr;
}

COMP_Texture::COMP_Texture(GameObject* owner) : Component(owner)
{
	type = COMP_Type::TEXTURE;
	this->owner = owner;
}

COMP_Texture::~COMP_Texture()
{

}

//void COMP_Texture::LinkTexture(std::string file_path)
//{
//	if (textureID != 0)
//	{
//		Application::GetApp()->texture->DestroyTexture(textureID);
//	}
//	textureID = Application::GetApp()->texture->LoadTexture(file_path);
//
//	RefreshTexture();
//}

void COMP_Texture::RefreshTexture()
{
	COMP_Mesh* refresh = owner->GetComponentMesh();
	if (refresh == nullptr) return;

	uint text = 0;

	if (PrintLoaded) {
		text = textureID;
	}
	else {
		text = Application::GetApp()->texture->checkerID;
	}

	for (int i = 0; i < refresh->meshes.size(); i++)
	{
		refresh->meshes[i]->texture_id = text;
	}

}