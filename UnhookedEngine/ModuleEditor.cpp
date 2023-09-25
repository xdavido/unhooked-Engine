#include "ModuleEditor.h"
#include "../ImGui/imgui.h"
#include "../ImGui/backends/imgui_impl_opengl3.h"
#include "../ImGui/backends/imgui_impl_sdl2.h"
#include "Application.h"
#include "Modulewindow.h"
#include "ModuleRenderer3D.h"


ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app , start_enabled)
{

}

ModuleEditor::~ModuleEditor()
{

}

bool ModuleEditor::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
 
	ImGui::StyleColorsLight();

	
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init("#version 130");


 return false;
}

void ModuleEditor::DrawEdior()
{
	ImGui_ImplSDL2_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();


	ImGui::ShowDemoWindow();

	ImGuiIO& io = ImGui::GetIO(); (void)io;



}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	/*SDL_GL_DeleteContext(App->renderer3D->context);*/

	return true;
}

//void ModuleEditor::OnResize(int width, int height)
//{
//	glViewport(0, 0, width, height);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
//	glLoadMatrixf(&ProjectionMatrix);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}

