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

	if (!App->IsDebug()) return UPDATE_CONTINUE;

	// EDITOR
	/*if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
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
	printf("pos=(%.2f,%.2f,%.2f),size=(%.2f,%.2f,%.2f),angle=%.2f\n", p.x, p.y,p.z,s.x,s.y,s.z,a);*/

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateTrack()
{
	AddTrack({ 0.0f,0.0f,0.0f }, { 10, 2, 50 });
	AddTrack({ 3.8,0,41.7 }, { 9.7,2,37.1 }, 12);
	AddTrack({ 13.2, 0, 73.4 }, { 9.7,2,36.3 }, 21);
	AddTrack({ 28.6, 0, 102.6 }, { 9.9,2,36.3 }, 34.5);
	AddTrack({35.9, 0,132.4}, { 9.8,2,36.3 }, -5.9);
	AddTrack({22.8, 0, 159.4}, { 9.2,2,36.3 }, -46.1);
	AddTrack({12.3, 0, 180.9}, { 9.2,2,25.5 }, 6.3);
	AddTrack({22.70, 0, 208.5}, { 9.2,2,40.1 }, 30);
	AddTrack({29.4, 0, 239.11}, { 9.2,2,33.1 }, -8.5);
	AddTrack({8.6, 0, 264.91}, { 9.2,2,48.3 }, -57.8);
	AddTrack({-24, 0, 277.51}, { 9.2,2,29.9 }, -88.5);
	AddTrack({-47.4, 0, 285.11}, { 9.2,2,29.9 }, -54.7);
	AddTrack({-89.7, 0, 291.61}, { 9.2,2,66.7 }, -92);
	AddTrack({-124.4, 0, 279.81}, { 9.2,2,29.2 }, 22.6);
	AddTrack({-129, 0, 203.9}, { 9.4,2,130.2 }, -0.2);
	AddTrack({-135.4, 0, 130.5}, { 9.5,2,27.4 }, 33.5);
	AddTrack({-191.9, 0, 122.3}, { 9.3,2,106.2 }, 91.3);
	AddTrack({-254.81, 0, 117.6}, { 9,2,29.1 }, 62.1);
	AddTrack({-273.31, 0, 100.7}, { 9,2,29.1 }, 34.8);
	AddTrack({-282.41, 0, 80.2}, { 9,2,23.1 }, 9.6);
	AddTrack({-280.91, 0, 60.4}, { 9,2,23.1 }, -18.9);
	AddTrack({-264.01, 0, 34.9}, { 9,2,45.1 }, -40.4);
	AddTrack({-221.6, 0, 10.6}, { 9,2,64.7 }, -73.3);
	AddTrack({-172.1, 0, 2.9}, { 9,2,40.8 }, -94.6);
	AddTrack({-134.8, 0, -2}, { 9,2,40.8 }, -70.3);
	AddTrack({-101.2, 0, -20.4}, { 9,2,40.8 }, -51.6);
	AddTrack({-68.4, 0, -39.6}, { 9,2,40.8 }, -67.3);
	AddTrack({-35.5, 0, -45.1}, { 9,2,34.4 }, -96.6);
	AddTrack({-9.3, 0, -32.3}, { 9,2,34.4 }, -136.3);
}

void ModuleSceneIntro::AddTrack(vec3 position, vec3 size, float angle, vec3 axis)
{
	Cube* cube = new Cube(size.x, size.y, size.z);
	cube->color.Set255(47, 56, 67);
	cube->SetPos(position.x, position.y, position.z);
	cube->SetRotation(angle, axis);
	PhysBody3D* pb3d = App->physics->AddBody(*cube, 0.0f);
	pb3d->collision_listeners.add(this);
	pb3d->type = PhysBody3D::Type::TRACK;

	map_track.PushBack(cube);

	cube = new Cube(size.x * 2, size.y / 2, size.z * 1.05);
	cube->color.Set255(172, 214, 95);
	cube->SetPos(position.x, position.y, position.z);
	cube->SetRotation(angle, axis);
	pb3d = App->physics->AddBody(*cube, 0.0f);
	pb3d->collision_listeners.add(this);
	pb3d->type = PhysBody3D::Type::GRASS;

	map_track.PushBack(cube);
}