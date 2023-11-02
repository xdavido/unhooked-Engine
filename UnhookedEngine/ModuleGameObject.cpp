#pragma once

#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ModuleTexture.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/mesh.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")
#include "ImGui/backends/imgui_impl_sdl2.h"

#define MAX_KEYS 300

#include <vector>
#include <cmath>



#define CHECKERS_HEIGHT 256/4
#define CHECKERS_WIDTH  256/4


ModuleGameObject::ModuleGameObject(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleGameObject::~ModuleGameObject()
{
}

// Called before render is available
bool ModuleGameObject::Init()
{
	LOG("Creating site for gameobjects");
	bool ret = true;


	return ret;
	

}

// Called every draw update
update_status ModuleGameObject::PreUpdate(float dt)
{
	
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return UPDATE_CONTINUE;
}

update_status ModuleGameObject::Update(float dt)
{
	return UPDATE_CONTINUE;
}


// PostUpdate present buffer to screen
update_status ModuleGameObject::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}



// Called before quitting
bool ModuleGameObject::CleanUp()
{
    LOG("Deleting gameobject cositas");
	// detach log stream
	aiDetachAllLogStreams();
    return true;

}




