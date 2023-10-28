//#include "Globals.h"
//#include "Application.h"
//#include "ModuleFBX.h"
//#include "ModuleTexture.h"
//#pragma comment (lib, "DevIL/libx86/DevIL.lib")
//#include "SDL/include/SDL_opengl.h"
//#include "Assimp/include/cimport.h"
//#include "Assimp/include/scene.h"
//#include "Assimp/include/mesh.h"
//#include "Assimp/include/postprocess.h"
//#pragma comment (lib, "Assimp/libx86/assimp.lib")
//#include "ImGui/backends/imgui_impl_sdl2.h"
//
//#define max_keys 300
//
//
//#include "DevIL/include/il.h"
//#include "DevIL/include/ilu.h"
//#include "DevIL/include/ilut.h"
//
//#include <gl/GL.h>
//#include <gl/GLU.h>
//
//#define checkers_height 256/4
//#define checkers_width  256/4
//
//
//ModuleTexture::ModuleTexture(Application* app, bool start_enabled) : Module(app, start_enabled)
//{
//	checkersID = 0;
//	testImageID = 0;
//
//}
//
//uint ModuleTexture::LoadTexture(const char* file_path)
//{
//	
//
//	//Generate DevIL buffers
//	ILuint devilImageId = 0;
//	ilGenImages(1, &devilImageId);
//	ilBindImage(devilImageId);
//
//	//Load image to binded buffer
//	bool success = ilLoadImage(file_path);
//
//	if (!success) {
//		LOG("WARNING: Error loading texture %s", file_path, ilGetError());
//	}
//	else ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
//
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
//	ilBindImage(0);
//	
//
//	//Unbind glew buffer
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	
//
//	return imageId;
//}
//
//void ModuleTexture::DestroyTexture(uint t)
//{
//	glDeleteBuffers(1, &t);
//}
//
//bool ModuleTexture::Init()
//{
//	ilInit();
//	iluInit();
//	ilutRenderer(ILUT_OPENGL);
//
//	return true; 
//}
//
//
//
//bool ModuleTexture::Start()
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
//	testImageID = LoadTexture("Game/Assets/texture/Baker_House.png");
//	return true;
//}
//
//bool ModuleTexture::CleanUp()
//{
//	glDeleteBuffers(1, &checkersID);
//	return true;
//}
//
