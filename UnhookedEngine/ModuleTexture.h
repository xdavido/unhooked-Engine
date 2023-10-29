#pragma once
#ifndef _Module_Textures_
#define _Module_Textures_

#include "Module.h"
#include "Globals.h"
#include "Light.h"
#include "Application.h"

#include "Glew/include/glew.h"
#include "DevIL/include/il.h"
#include "DevIL/include/ilu.h"
#include "DevIL/include/ilut.h"


#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64


class ModuleTexture : public Module
{
public:
	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture() {}

	void LoadTexture(const char* file_path);
	bool CheckerTexture();
	void DrawTexture();


private:
	bool Init();
	bool CleanUp();

	

public:
	GLuint checkersID;
	//GLuint testImageID;
	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4]; // height width rgba

};

#endif // !_Module_Textures_