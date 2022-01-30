#include "Application.h"
#include "Textures.h"

#include "Globals.h"

#pragma comment(lib, "SDL_image/libx86/SDL2_image.lib")

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "glew/include/GL/glew.h"
#include "SDL\include\SDL_opengl.h"

Textures::Textures(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

// Destructor
Textures::~Textures()
{}

// Called before the first frame
bool Textures::Start()
{
	LOG("start textures");
	bool ret = true;

	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool Textures::CleanUp()
{
	LOG("Freeing textures and Image library");

	IMG_Quit();
	return true;
}

// Load new texture from file path
uint const Textures::Load(const char* path, int* width, int* height)
{
	SDL_Surface* srfc = IMG_Load(path);

	uint tex = -1;

	if(srfc == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, srfc->w, srfc->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, srfc->pixels);
		*width = srfc->w;
		*height = srfc->h;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		SDL_FreeSurface(srfc);
	}

	return tex;
}
