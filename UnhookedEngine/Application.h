#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleEditor.h"
#include "ModuleFBX.h"
#include "ModuleTexture.h"
#include "ModuleHierarchy.h"
#include "ModuleScene.h"
#include<vector>

#include "MemLeaks.h"

enum class GameState
{
	PLAY = 0,
	PAUSE = 1,
	STOP = 2
};

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleEditor* editor;
	ModuleFBX* FBX;
	ModuleTexture* texture;
	ModuleHierarchy* hierarchy;
	ModuleScene* scene;


private:

	float timeSpeed = 1;
	float	dt;
	float	dtG;
	GameState gameState = GameState::STOP;
	std::vector<Module*> list_modules;


public:

	int fps = 60;
	
	~Application();
	void PreUpdate();
	void PostUpdate();
	static Application* GetApp();


	bool Init();
	update_status Update();
	bool CleanUp();

	void SetDT(float dt);
	float DTG();
	

private:

	Application();
	static Application* externalapp;
	void AddModule(Module* mod);

};

