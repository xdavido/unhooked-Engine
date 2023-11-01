#pragma once
#include "Globals.h"
#include "Component.h"
#include "ImGui/imgui.h"

#include<string>

class GameObject;
class Component;

class COMP_Texture : public Component
{
public:

	COMP_Texture();
	COMP_Texture(GameObject* owner);
	~COMP_Texture();

	GLuint textureID = 0;

	bool PrintLoaded = true;

	//void LinkTexture(std::string file_path);

	void RefreshTexture();

}; 
