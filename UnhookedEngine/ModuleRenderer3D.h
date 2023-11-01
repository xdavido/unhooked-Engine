#pragma once

#include <string>

#include "Module.h"
#include "Globals.h"
#include "Light.h"
#include "ModuleFBX.h"

#include "MathGeoLib/include/Math/float3x3.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "Primitive.h"

#include "Glew/include/glew.h"

//todo: REMOVE this before 1st delivery!!
#include "glmath.h"

#include <vector>

#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt) override;
	update_status PostUpdate(float dt);
	bool CleanUp();

	void ChangeColorScene(Color color);
	
	void OnResize(int width, int height);

public:

	void HandlePath(std::string path);

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	//CPlane Grid;

	bool TurnOff = false;

	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	std::vector<MeshData> MeshVertex;
	GLuint textureID;

};