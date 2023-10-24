#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleEditor.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include "ModuleFbx.h"
#include "ModuleInput.h"
#include "Game/Assimp/include/cimport.h"
#include "Game/Assimp/include/scene.h"
#include "Game/Assimp/include/postprocess.h"
#include <cmath>

#include <vector>

#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "glu32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib")
#pragma comment (lib, "DevIL/libx86/DevIL.lib")



#ifdef _DEBUG
#pragma comment (lib, "MathGeoLib/libx86/Debug/MathGeoLib.lib") /* link Microsoft OpenGL lib   */
#else
#pragma comment (lib, "MathGeoLib/libx86/Release/MathGeoLib.lib") /* link Microsoft OpenGL lib   */
#endif // _DEBUG


ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

//static const GLfloat CubeVertices[] = {
//		  //front
//		  //0.2f, 0.2f, 0.0f, 1.0f, 1.0f,    // top right
//		  //0.2f, -0.2f, 0.0f, 1.0f, 0.0f,   // bottom right
//		  //-0.2f, -0.2f, 0.0f, 0.0f, 0.0f,  // bottom left
//		  //-0.2f, 0.2f, 0.0f, 0.0f, 1.0f,   // top left 
//
//		  ////back
//		  //0.2f, 0.2f, -0.4f, 1.0f, 1.0f,   // top right
//		  //0.2f, -0.2f, -0.4f, 1.0f, 0.0f,  // bottom right
//		  //-0.2f, -0.2f, -0.4f, 0.0f, 0.0f, // bottom left
//		  //-0.2f, 0.2f, -0.4f, 0.0f, 1.0f,  // top left 
//	-1,-1,-1, 0, 0,
//	 1,-1,-1, 1, 0,
//	 1, 1,-1, 2, 0,
//	-1, 1,-1, 3, 0,
//	-1,-1,-1, 4, 0,
//
//	-1,-1, 1, 0, 1,
//	 1,-1, 1, 1, 1,
//	 1, 1, 1, 2, 1,
//	-1, 1, 1, 3, 1,
//	-1,-1, 1, 4, 1,
//
//	-1, 1,-1, 0,-1,
//	 1, 1,-1, 1,-1,
//
//	-1, 1, 1, 0, 2,
//	 1, 1, 1, 1, 2
//
//};
//static const GLuint CubeIndices[] = {
//
//	  //// front
//	  //0, 1, 3,
//	  //1, 2, 3,
//	  //// back
//	  //4, 5, 7,
//	  //5, 6, 7,
//	  //// right
//	  //0, 1, 4,
//	  //1, 4, 5,
//	  //// left
//	  //2, 3, 7,
//	  //2, 6, 7,
//	  //// top
//	  //0, 3, 4,
//	  //3, 4, 7,
//	  //// bottom
//	  //1, 2, 5,
//	  //2, 5, 6
//
//	0, 1, 5,  5, 1, 6,
//	 1, 2, 6,  6, 2, 7,
//	 2, 3, 7,  7, 3, 8,
//	 3, 4, 8,  8, 4, 9,
//	10,11, 0,  0,11, 1,
//	 5, 6,12, 12, 6,13
//};

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;

	//OpenGL initialitzation
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if (context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (ret == true)
	{
		//Use Vsync
		if (VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);

		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		GLfloat LightModelAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);

		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();

		GLfloat MaterialAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);

		glewInit();
	}

	App->FBX->LoadFBX("Assets/BakerHouse.fbx", MeshVertex);


	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	Grid.axis = true;


	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for (uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::Update(float dt)
{
	
	if (App->input->droped)
	{
		App->FBX->LoadFBX(App->input->dropped_filedir, MeshVertex);
		App->input->droped = false;
	}
	if (App->editor->wireframe)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
		for (int i = 0; i < MeshVertex.size(); ++i)
		{
			MeshVertex[i].DrawFBX();
		}
	}
	else {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		for (int i = 0; i < MeshVertex.size(); ++i)
		{
			MeshVertex[i].DrawFBX();
		}
	}


	return UPDATE_CONTINUE;

}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	Grid.Render();
	
	App->editor->Draw();

	
	SDL_GL_SwapWindow(App->window->window);

	

	if (TurnOff)
	{
		return UPDATE_STOP;
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::ChangeColorScene(Color color)
{
	float red = color.r / 255.0f;
	float green = color.g / 255.0f;
	float blue = color.b / 255.0f;

	//Change Color
	glClearColor(red, green, blue, 1.f);
}

void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//todo: USE MATHGEOLIB here BEFORE 1st delivery! (TIP: Use MathGeoLib/Geometry/Frustum.h, view and projection matrices are managed internally.)
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(ProjectionMatrix.M);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
