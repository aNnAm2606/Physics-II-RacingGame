#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"

class btRigidBody;
class Module;
class btGhostBody;
class btQuaternion;
class btVector3;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	enum class Type {
		CAR,
		TRACK,
		GRASS,
		OBSTACLE,
		GOAL
	};

	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void GetPos(float* x, float* y, float* z) const;

	btQuaternion GetRotation() const;
	void SetRotation(btQuaternion& quat);

	void SetVelocity(btVector3& v);
	btVector3 GetVelocity() const;

	void SetLinearFactor(float x, float y, float z);
	void ClampVelocity(float min, float max);
	void ResetVelocity();
	void ResetRotation();
private:
	btRigidBody* body = nullptr;
public:
	p2List<Module*> collision_listeners;
	Type type;
};

#endif // __PhysBody3D_H__