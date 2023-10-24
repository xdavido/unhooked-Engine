#pragma once
#ifndef _Module_Textures_
#define _Module_Textures_

#include "Module.h"
#include "Globals.h"
#include <vector>
#include <string>

#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_sdl2.h"
#include "ImGui/backends/imgui_impl_opengl3.h"

class ModuleTextures : public Module
{
public:
	ModuleTextures(Application* app, bool start_enabled = true);
	~ModuleTextures();
	
private:

};

#endif // !_Module_Textures_