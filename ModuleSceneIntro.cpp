#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	
	grass = new Cube(50, 1, 50);
	grass->color.Set255(172, 214, 95);

	PhysBody3D* gb = App->physics->AddBody(*grass, 0.0f);
	gb->collision_listeners.add(this);

	p = { 0,0,0 };
	s = { 10,2,50 };
	a = 0;

	// Create track
	CreateTrack();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	unsigned int size = map_track.Count();

	for (int i = 0; i < size; i++) {
		map_track[i]->Render();
	}

	grass->Render();

	if (!App->IsDebug()) return UPDATE_CONTINUE;

	// EDITOR
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) {
			s.x += 0.1f;
		}
		else {
			p.x += 0.1f;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) {
			s.x -= 0.1f;
		}
		else {
			p.x -= 0.1f;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) {
			s.z += 0.1f;
		}
		else {
			p.z += 0.1f;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) {
			s.z -= 0.1f;
		}
		else {
			p.z -= 0.1f;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT) {
		a += 0.1f;
	}
	else if(App->input->GetKey(SDL_SCANCODE_N) == KEY_REPEAT){
		a -= 0.1f;
	}

	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {
		Cube* cube = new Cube();
		cube->color.Set255(47, 56, 67);
		map_track.PushBack(cube);
	}

	Cube* c = map_track[size - 1];
	c->SetPos(p.x, p.y, p.z);
	c->SetSize(s);
	c->SetRotation(a, vec3(0, 1.0f, 0));
	printf("pos=(%.2f,%.2f,%.2f),size=(%.2f,%.2f,%.2f),angle=%.2f\n", p.x, p.y,p.z,s.x,s.y,s.z,a);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	
}

void ModuleSceneIntro::CreateTrack()
{
	AddTrack({ 0.0f,0.0f,0.0f }, { 10, 2, 50 });
}

void ModuleSceneIntro::AddTrack(vec3 position, vec3 size, float angle, vec3 axis)
{
	Cube* cube = new Cube(size.x, size.y, size.z);
	cube->color.Set255(47, 56, 67);
	cube->SetPos(position.x, position.y, position.z);
	cube->SetRotation(angle, axis);
	App->physics->AddBody(*cube, 0.0f)->collision_listeners.add(this);

	map_track.PushBack(cube);
}