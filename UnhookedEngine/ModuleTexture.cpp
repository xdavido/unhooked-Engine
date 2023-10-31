
#include "Globals.h"
#include "Application.h"
#include "ModuleFBX.h"
#include "ModuleTexture.h"


ModuleTexture::ModuleTexture(Application* app, bool start_enabled) : Module(app, start_enabled)
{


}

ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Start()
{
 {
	// Create a checkerboard image.
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}

	// Enable 2D texture.
	glEnable(GL_TEXTURE_2D);

	// Generate and bind a texture buffer.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Configure the texture parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Generate the texture.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

	// Generate mipmaps (optional).
	glGenerateMipmap(GL_TEXTURE_2D);

	// Clean up.
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
 }
	// Initialize clear color.
	glClearColor(0.f, 0.f, 0.f, 1.f);

	ilInit();
	ilClearColour(255, 255, 255, 000);


	//House_Texture_Path = "Assets/textures/Baker_house.png";

	// Load the texture from the specified path.
	//LoadTexture(House_Texture_Path);

	return true;

}

bool ModuleTexture::LoadTexture(string file_path)
{

	//Texture loading success
	bool isTextureLoaded = false;

	// Generate DevIL buffers
	ILuint devilImageId = 0;
	ilGenImages(1, &devilImageId);
	ilBindImage(devilImageId);

	// Load image to binded buffer
	ILboolean success = ilLoadImage(file_path.c_str());
	
	if (!success) {
		LOG("WARNING: Error loading texture %s", file_path.c_str(), ilGetError());
		return 0;
	}

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);


	isTextureLoaded = CreateTexture((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
	
	if (!isTextureLoaded)
	{
		printf("Unable to load %s\n", file_path.c_str());
	}

	//// Extract loaded image data
	//BYTE* data = ilGetData();
	//ILuint imgWidth, imgHeight;
	//imgWidth = ilGetInteger(IL_IMAGE_WIDTH);
	//imgHeight = ilGetInteger(IL_IMAGE_HEIGHT);
	//int const type = ilGetInteger(IL_IMAGE_TYPE);
	//int const format = ilGetInteger(IL_IMAGE_FORMAT);

	//// Change DevIL buffer ID to Glew buffer ID (create buffer by copying binded buffer)
	//GLuint imageId = ilutGLBindTexImage();
	//glBindTexture(GL_TEXTURE_2D, imageId);

	//// How texture behaves outside 0,1 range (S->x, T->y)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//// Texture behaviour after resize (MIN->smaller , MAG->bigger)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//// Create Texture
	//glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, type, data);
	//glGenerateMipmap(GL_TEXTURE_2D);

	// CLEANUP

	// Delete DevIL image buffer
	ilDeleteImages(1, &devilImageId);
	//ilBindImage(0);

	// Unbind glew buffer

	return isTextureLoaded;
}


bool ModuleTexture::Init()
{
	

	return true;
}



bool ModuleTexture::CleanUp()
{
	return true;
}

bool ModuleTexture::CreateTexture(GLuint* imgData, GLuint width, GLuint height)
{
	// Free any existing textures.
	DestroyTexture();

	// Set the width and height of the texture.
	textureWidth = width;
	textureHeight = height;

	// Enable 2D texture.
	glEnable(GL_TEXTURE_2D);

	// Generate and bind a texture buffer.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Configure the texture parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Generate the texture.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

	// Generate mipmaps (optional).
	glGenerateMipmap(GL_TEXTURE_2D);

	// Clean up the texture.
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	// Return true if the texture was created successfully.
	return true;
}

void ModuleTexture::DestroyTexture()
{
	//Delete texture
	if (textureID != 0)
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}

	textureWidth = 0;
	textureHeight = 0;
}


