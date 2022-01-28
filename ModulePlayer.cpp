#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	frictionCoefficient = 0.99f;

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 2, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 12, 10);
	vehicle->type = PhysBody3D::Type::CAR;

	Cube* c = new Cube(2, 1, 4);
	bounds = App->physics->AddBody(*c, 1.0f, true);
	bounds->SetVelocity(btVector3(0, -250, 0));
	bounds->type = PhysBody3D::Type::CAR;
	bounds->collision_listeners.add(this);

	// ZOOM
	minZoom = { 5, -5 };
	maxZoom = { 25, -25 };

	zoom = maxZoom;

	zoomRatio = 0.0f;
	zoomSpeed = 0.05f;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->type == PhysBody3D::Type::CAR) {
		if (body2->type != PhysBody3D::Type::CAR) {
			vec3 b2p;
			body2->GetPos(&b2p.x, &b2p.y, &b2p.z);

			lastPos = b2p;
			lastRot = body2->GetRotation();

			if (body2->type == PhysBody3D::Type::GRASS) {
				btVector3 v = vehicle->GetVelocity();
				v.setValue(v.x() * frictionCoefficient, v.y() * frictionCoefficient, v.z() * frictionCoefficient);
				vehicle->SetVelocity(v);
			}
		}
	}
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	if (App->IsDebug()) return UPDATE_CONTINUE;

	// Vehicle control
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		acceleration = -MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	//-- Camera control --
	//Zoom
	zoomRatio -= App->input->GetMouseZ() * zoomSpeed;
	CAP(zoomRatio);

	zoom = { LERP(minZoom.x, maxZoom.x, zoomRatio), LERP(minZoom.y, maxZoom.y, zoomRatio) };

	//Reposition
	vec3 carpos = vehicle->GetPosition();

	vec3 campos = carpos + vec3(0, zoom.x, zoom.y);

	App->camera->Look(campos, carpos);

	//-- Track control
	if (carpos.y <= -10.0f) {
		vehicle->SetPos(lastPos.x, 3.0f, lastPos.z);
		vehicle->SetRotation(lastRot);
		vehicle->ResetVelocity();
	}

	//-- Bounds follow
	bounds->SetPos(carpos.x, carpos.y, carpos.z);

	// Set title
	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	printf("lastpos(%.2f,%.2f,%.2f)\n", lastPos.x, lastPos.y, lastPos.z);

	return UPDATE_CONTINUE;
}