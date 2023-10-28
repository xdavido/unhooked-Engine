#pragma once
#ifndef _Module_Editor_
#define _Module_Editor_

#include "Module.h"
#include "Globals.h"
#include "Color.h"
#include <vector>
#include <string>

#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_sdl2.h"
#include "ImGui/backends/imgui_impl_opengl3.h"

class ModuleEditor : public Module
{
public:

	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init() override;
	void Draw();
	bool CleanUp() override;

	void AddFPS(float aFPS);

	std::vector<float> mFPSLog;
	bool wireframe = true;


	
	bool gl_DEPTH_TEST, gl_CULL_FACE, gl_LIGHTING, gl_COLOR_MATERIAL, gl_TEXTURE_2D, gl_WIREFRAME = true;

private:
	const char* lastValue = "";
	void MainMenuBar();
	void SettingsMenu();
	void SetWireFrameMode(bool wireframe);


	bool OpenAbout = false;

	std::vector<std::string> MSG;

	Color color = Color(0.0f, 0.0f, 0.0f);

	int Height = 720, Width = 1080;
	bool fullscreen = false, resizable = true, borderless = false, fullscreendesktop = false;
};

#endif // !_Module_Editor_