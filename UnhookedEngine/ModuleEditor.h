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
	void AddToConsole(const std::string& message);
	double GetMemoryUsageInMB();

	std::vector<float> mFPSLog;
	bool wireframe = false;
	bool VertexShow = false;
	bool FaceShow = false;
	float screenWidth;
	float screenHeight;
	bool showSettingsWindow;
	bool showAssetsWindow;
	bool showConsoleWindow;
	// Define a vector to store console messages
	std::vector<std::string> consoleMessages;

	// A flag to control scrolling to the bottom of the console
	bool scrollToBottom;
	bool gl_DEPTH_TEST, gl_CULL_FACE, gl_LIGHTING = true, gl_COLOR_MATERIAL, isTextured = true, Checkers = false;


private:
	const char* lastValue = "";
	void MainMenuBar();
	void SettingsMenu();
	void AssetsWindow();
	void ConsoleWindow();
	void SetWireFrameMode(bool wireframe);
	bool OpenAbout = false;
	std::vector<std::string> MSG;
	Color color = Color(0.0f, 0.0f, 0.0f);

	int Height = 720, Width = 1080;
	bool fullscreen = false, resizable = true, borderless = false, fullscreendesktop = false;

	
};
#endif // !_Module_Editor_