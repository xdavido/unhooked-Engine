//#include "ModuleTextures.h"
//#include "Globals.h"
//#include "Application.h"
//#include "ModuleFBX.h"
//#include "Game/Assimp/include/cimport.h"
//#include "Game/Assimp/include/scene.h"
//#include "Game/Assimp/include/mesh.h"
//#include "Game/Assimp/include/postprocess.h"
//#pragma comment (lib, "Game/Assimp/libx86/assimp.lib")
//#pragma comment (lib, "DevIL/libx86/DevIL.lib")
//#include <gl/GL.h>
//#include <gl/GLU.h>
//
//#include "ImGui/backends/imgui_impl_sdl2.h"
//
//#define MAX_KEYS 300
//
//#include <vector>
//#include <cmath>
//
//
//
//#define CHECKERS_HEIGHT 256/4
//#define CHECKERS_WIDTH  256/4
//ModuleTextures::ModuleTextures(Application* app, bool start_enabled) : Module(app, start_enabled)
//{
//
//}
//
//ModuleTextures::~ModuleTextures()
//{
//}
//
//void ModuleTextures::LoadTexture(const char* file_path)
//{//Generate DevIL buffers
//	uint devilImageId;
//	ilGenImages(1, &devilImageId);
//	ilBindImage(devilImageId);
//
//	//Load image to binded buffer
//	bool success = ilLoadImage(file_path);
//
//	if (!success) {
//		LOGT(LogsType::WARNINGLOG, "Error loading texture %s", file_path);
//		return 0;
//	}
//
//	success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
//
//	if (!success) {
//		LOGT(LogsType::WARNINGLOG, "Error converting texture %s", file_path);
//		return 0;
//	}
//
//	string ext = FileInfo(file_path).extension;
//
//	//Png is the only format not flipped
//	if (ext != ".png" && ext != ".PNG") {
//		iluFlipImage();
//	}
//
//	//Extract loaded image data
//	BYTE* data = ilGetData();
//	ILuint imgWidth, imgHeight;
//	imgWidth = ilGetInteger(IL_IMAGE_WIDTH);
//	imgHeight = ilGetInteger(IL_IMAGE_HEIGHT);
//	int const type = ilGetInteger(IL_IMAGE_TYPE);
//	int const format = ilGetInteger(IL_IMAGE_FORMAT);
//
//	//Change DevIL buffer ID to Glew buffer ID (create buffer by copying binded buffer)
//	uint imageId = ilutGLBindTexImage();
//	glBindTexture(GL_TEXTURE_2D, imageId);
//
//	//How texture behaves outside 0,1 range (S->x, T->y)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//
//	//Texture behaviour after resize (MIN->smaller , MAG->bigger)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//	//Create Texture
//	glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, type, data);
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	//CLEANUP
//
//	//Delete DevIL image buffer
//	ilDeleteImages(1, &devilImageId);
//
//	//Unbind glew buffer
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	return imageId;
//}
//
//void ModuleTextures::DestroyTexture(uint t)
//{
//	glDeleteBuffers(1, &t);
//}
//
//bool ModuleTextures::Init()
//{
//	ilInit();
//	iluInit();
//	ilutInit();
//
//	return true;
//}
//
//bool ModuleTextures::Start()
//{
//	//Initialize checker image
//	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
//		for (int j = 0; j < CHECKERS_WIDTH; j++) {
//			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
//			checkerImage[i][j][0] = (GLubyte)c;
//			checkerImage[i][j][1] = (GLubyte)c;
//			checkerImage[i][j][2] = (GLubyte)c;
//			checkerImage[i][j][3] = (GLubyte)255;
//		}
//	}
//
//	glEnable(GL_TEXTURE_2D);
//	glActiveTexture(GL_TEXTURE0);
//
//	//Generate and bind texture
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glGenTextures(1, &checkersID);
//	glBindTexture(GL_TEXTURE_2D, checkersID);
//
//	//How texture behaves outside 0,1 range (S->x, T->y)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //GL_CLAMP
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	//Texture behaviour after resize (MIN->smaller , MAG->bigger)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//	//Create Texture
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
//		0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	//unbind texture
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glDisable(GL_TEXTURE_2D);
//
//	return true;
//}
//
//bool ModuleTextures::CleanUp()
//{
//	glDeleteBuffers(1, &checkersID);
//	return true;
//}