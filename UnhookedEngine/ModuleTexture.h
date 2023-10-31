#pragma once
#ifndef _Module_Textures_
#define _Module_Textures_

#include "Module.h"
#include "Globals.h"
#include "Light.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"
#include "DevIL/include/il.h"
#include "DevIL/include/ilu.h"
#include "DevIL/include/ilut.h"
#pragma comment(lib, "DevIL/libx86/DevIL.lib")
#pragma comment(lib, "DevIL/libx86/ILU.lib")
#pragma comment(lib, "DevIL/libx86/ILUT.lib")
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ImGui/backends/imgui_impl_opengl3.h"

using namespace std;

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64


class ModuleTexture : public Module
{
public:
	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();

	bool Init();
	bool Start();
	bool CleanUp();
	bool CreateTexture(GLuint* imgData, GLuint width, GLuint height);
	bool LoadTexture(string file_path);
	void DestroyTexture();

	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	GLuint textureID = 0,textureWidth = 0, textureHeight = 0;
	string House_Texture_Path = "";

};

#endif // !_Module_Textures_