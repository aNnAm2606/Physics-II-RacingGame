#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include "Module.h"

#include "p2List.h"

struct SDL_Texture;
struct SDL_Surface;

class Textures : public Module
{
public:

	Textures(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~Textures();

	// Called before the first frame
	bool Start();

	// Called before quitting
	bool CleanUp();

	// Load Texture
	uint const Load(const char* path, int* width, int* height);
public:
};


#endif // __TEXTURES_H__