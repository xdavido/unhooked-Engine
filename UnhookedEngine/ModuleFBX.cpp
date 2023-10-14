#include "Globals.h"
#include "Application.h"
#include "ModuleFBX.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")
#include "ImGui/backends/imgui_impl_sdl2.h"

#define MAX_KEYS 300



ModuleFBX::ModuleFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

// Destructor
ModuleFBX::~ModuleFBX()
{
	
}

// Called before render is available
bool ModuleFBX::Init()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

}

// Called every draw update
update_status ModuleFBX::PreUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleFBX::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();
}