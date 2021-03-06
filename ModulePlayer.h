#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;
class btQuaternion;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	vec2 zoomRange;

	float zoomRatio;
	float zoomSpeed;

	void Stop();
	void ResetPosition();
public:
	vec3 lastPos;
	btQuaternion lastRot;

	PhysVehicle3D* vehicle;
	PhysBody3D* bounds;
	float turn;
	float acceleration;
	float brake;

	float frictionCoefficient;
	float boostCoefficient;
};