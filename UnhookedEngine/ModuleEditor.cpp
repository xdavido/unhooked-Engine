#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "SDL/include/SDL_opengl_glext.h"
#include <filesystem>
#include "Globals.h"
#include <windows.h>
#include <psapi.h>


ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{

    

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    ImGui_ImplOpenGL3_Init();

    return true;
}

void ModuleEditor::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    MainMenuBar();

    if (showSettingsWindow)
        SettingsMenu();

    if (showAssetsWindow)
        AssetsWindow();

    if (showConsoleWindow)
        ConsoleWindow();

    if (OpenAbout == true)
    {
        if (ImGui::Begin("About Uss"))
        {
            ImGui::SeparatorText("ABOUT UNHOOKED ENGINE:");
            ImGui::Text("Unhooked Engine v.0.1");
            ImGui::Text("The new 3D Game Engine under CITM development");
            ImGui::Text("David Ruiz Luengo & Pau Garriga Brotons");
            ImGui::Text("3rd party Libraries:");

            ImGui::End();
        }
    }

    //ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui::EndFrame();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ModuleEditor::CleanUp()
{
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

void ModuleEditor::MainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::Button("Exit"))
        {
            App->renderer3D->TurnOff = true;
        }

        if (ImGui::BeginMenu("Menu"))
        {
            ImGui::MenuItem("Settings", NULL, &showSettingsWindow);
            ImGui::MenuItem("Assets", NULL, &showAssetsWindow);
            ImGui::MenuItem("Console", NULL, &showConsoleWindow);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            {
                OpenAbout = !OpenAbout;
            }

            if (ImGui::MenuItem("GitHub"))
            {
                ShellExecute(NULL, "open", "https://github.com/xdavido/unhooked-Engine", 0, 0, SW_SHOWNORMAL);

            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}



void ModuleEditor::SettingsMenu()
{
    float Settings2WindowWidth = 200.0f;

    float gameAreaWidth = ImGui::GetIO().DisplaySize.x - Settings2WindowWidth;

    if (gameAreaWidth < 200.0f)
        gameAreaWidth = 200.0f;

    // AssetsWindow anclada a la derecha
    ImGui::SetNextWindowPos(ImVec2(gameAreaWidth, 19));
    ImGui::SetNextWindowSize(ImVec2(Settings2WindowWidth, ImGui::GetIO().DisplaySize.y - 19));

    if (ImGui::Begin("Settings"))
    {
        ImGui::PlotHistogram("FPS", mFPSLog.data(), mFPSLog.size(), 2, lastValue);

        if (ImGui::CollapsingHeader("LOG"))
        {
            ImGui::SeparatorText("OPEN GL:");
            ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
            ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
            ImGui::Text("OpenGL version supported %s", glGetString(GL_VERSION));
            ImGui::Text("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
            SDL_version version;
            SDL_GetVersion(&version);
            ImGui::SeparatorText("System Information:");
            ImGui::Text("Memory Usage: %.2f MB", GetMemoryUsageInMB());
            ImGui::Text("SDL Version: %d.%d.%d", version.major, version.minor, version.patch);
            ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION));
            ImGui::Text("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
        }

        if (ImGui::CollapsingHeader("Render Options"))
        {
            if (ImGui::Checkbox("GL_DEPTH_TEST", &gl_DEPTH_TEST))
            {
                if (gl_DEPTH_TEST)
                {
                    glEnable(GL_DEPTH_TEST);
                    MSG.push_back("GL_DEPTH_TEST Enabled");
                }
                else
                {
                    glDisable(GL_DEPTH_TEST);
                    MSG.push_back("GL_DEPTH_TEST Disabled");
                }
            }
            if (ImGui::Checkbox("GL_CULL_FACE", &gl_CULL_FACE))
            {
                if (gl_CULL_FACE)
                {
                    glEnable(GL_CULL_FACE);
                    MSG.push_back("GL_CULL_FACE Enabled");
                }
                else
                {
                    glDisable(GL_CULL_FACE);
                    MSG.push_back("GL_CULL_FACE Disabled");
                }
            }
            if (ImGui::Checkbox("GL_LIGHTING", &gl_LIGHTING))
            {
                if (gl_LIGHTING)
                {
                    glEnable(GL_LIGHTING);
                    MSG.push_back("GL_LIGHTING Enabled");
                }
                else
                {
                    glDisable(GL_LIGHTING);
                    MSG.push_back("GL_LIGHTING Disabled");
                }
            }
            if (ImGui::Checkbox("GL_COLOR_MATERIAL", &gl_COLOR_MATERIAL))
            {
                if (gl_COLOR_MATERIAL)
                {
                    glEnable(GL_COLOR_MATERIAL);
                    MSG.push_back("GL_COLOR_MATERIAL Enabled");
                }
                else
                {
                    glDisable(GL_COLOR_MATERIAL);
                    MSG.push_back("GL_COLOR_MATERIAL Disabled");
                }
            }
            if (ImGui::Checkbox("Texture", &gl_TEXTURE_2D))
            {
                if (gl_TEXTURE_2D)
                {
                    glEnable(GL_TEXTURE_2D);
                    MSG.push_back("GL_TEXTURE_2D Enabled");
                }
                else
                {
                    glDisable(GL_TEXTURE_2D);
                    MSG.push_back("GL_TEXTURE_2D Disabled");
                }
            }
            if (ImGui::Checkbox("Wireframe Mode", &wireframe))
            {
                SetWireFrameMode(wireframe);
            }
            if (ImGui::Checkbox("Show Vertex Normals", &VertexShow))
            {
                
            }
            if (ImGui::Checkbox("Show Face Normals", &FaceShow))
            {

            }
            //ImGui::Checkbox("Vsync", &vsync);
            //SetVsync(vsync);
            
        }

        if (ImGui::CollapsingHeader("Window Settings"))
        {
            ImGui::SeparatorText("Window");

            ImGui::SliderInt("Height", &Height, 144, 1080);
            ImGui::SliderInt("Width", &Width, 256, 1920);

            ImGui::Checkbox("FullScreen", &fullscreen);
            ImGui::Checkbox("Resizable", &resizable);
            ImGui::Checkbox("Borderless", &borderless);
            ImGui::Checkbox("FullScreen Desktop", &fullscreendesktop);

            if (ImGui::Button("Apply Changes"))
            {
                App->window->SetNewWindow(Height, Width, fullscreen, resizable, borderless, fullscreendesktop);
                MSG.push_back("Window Changes Applied");
            }

            ImGui::SeparatorText("Background Color");

            ImGui::SliderFloat("Red", &color.r, 0, 255);
            ImGui::SliderFloat("Green", &color.g, 0, 255);
            ImGui::SliderFloat("Blue", &color.b, 0, 255);
            App->renderer3D->ChangeColorScene(color);
        }

        // Button Save/Load
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("Save"))
        {
            MSG.push_back("Boton Pulsado");
        }ImGui::SameLine();
        ImGui::Button("Load");

    }
    ImGui::End();
}

void ModuleEditor::AssetsWindow()
{
    float assetsWindowWidth = 200.0f;

    // AssetsWindow anclada a la izquierda
    ImGui::SetNextWindowPos(ImVec2(0, 19));
    ImGui::SetNextWindowSize(ImVec2(assetsWindowWidth, ImGui::GetIO().DisplaySize.y - 19));

    

    if (ImGui::Begin("Assets", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
    {
        
        if (ImGui::TreeNode("Root Object"))
        {
            if (ImGui::TreeNode("Child Object 1"))
            {
                ImGui::Text("Position: (x, y, z)");
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
        ImGui::End();
    }

    //float assetsWindowWidth = 200.0f;

    //// AssetsWindow anchored to the left
    //ImGui::SetNextWindowPos(ImVec2(0, 19));
    //ImGui::SetNextWindowSize(ImVec2(assetsWindowWidth, ImGui::GetIO().DisplaySize.y - 19));

    //if (ImGui::Begin("Assets", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
    //{
    //    // Iterate through your scene objects and display them
    //    for (const auto& sceneObject : sceneObjects)
    //    {
    //        if (ImGui::TreeNode(sceneObject.name.c_str()))
    //        {
    //            ImGui::Text("Position: (%f, %f, %f)", sceneObject.position.x, sceneObject.position.y, sceneObject.position.z);
    //            // You can add more object-specific information here

    //            ImGui::TreePop();
    //        }
    //    }

    //    ImGui::End();
    //}
}

void ModuleEditor::ConsoleWindow()
{
    float consoleWindowHeight = 200.0f;
    float leftWindowWidth = 200.0f;
    float rightWindowWidth = 200.0f;

    float consoleWindowX = leftWindowWidth;
    float consoleWindowY = ImGui::GetIO().DisplaySize.y - consoleWindowHeight;

    //ConsoleWindow anclada abajo
    ImGui::SetNextWindowPos(ImVec2(consoleWindowX, consoleWindowY));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - leftWindowWidth - rightWindowWidth, consoleWindowHeight));

    if (ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
    {
        ImGui::BeginChild("ConsoleLog", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        for (const std::string& message : consoleMessages)
        {
            ImGui::TextUnformatted(message.c_str());
        }

        ImGui::EndChild();
        ImGui::End();
    }
}

void ModuleEditor::AddToConsole(const std::string& message)
{
    consoleMessages.push_back(message);
    scrollToBottom = true;
}



void ModuleEditor::AddFPS(float aFPS)
{
    if (mFPSLog.size() < 30)
    {
        mFPSLog.push_back(aFPS);
    }
    else
    {
        mFPSLog.erase(mFPSLog.begin());
        mFPSLog.push_back(aFPS);
    }
}

#include <windows.h>

double ModuleEditor::GetMemoryUsageInMB()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));

    SIZE_T virtualMemory = pmc.PrivateUsage;

    // Convert bytes to megabytes
    double memoryInMB = static_cast<double>(virtualMemory) / (1024.0 * 1024.0);

    return memoryInMB;
}

void ModuleEditor::SetWireFrameMode(bool wireframe)
{
    if (wireframe)
    {
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);

    }
    else
    {
        App->FBX->DrawMesh();
    }
}