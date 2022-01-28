#include "PhysBody3D.h"
#include "glmath.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// =================================================
PhysBody3D::PhysBody3D(btRigidBody* body) : body(body)
{}

// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{
	delete body;
}

// ---------------------------------------------------------
void PhysBody3D::Push(float x, float y, float z)
{
	body->applyCentralImpulse(btVector3(x, y, z));
}

// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		body->getWorldTransform().getOpenGLMatrix(matrix);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		btTransform t;
		t.setFromOpenGLMatrix(matrix);
		body->setWorldTransform(t);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
	btTransform t = body->getWorldTransform();
	t.setOrigin(btVector3(x, y, z));
	body->setWorldTransform(t);
}

void PhysBody3D::GetPos(float* x, float* y, float* z) const
{
	btVector3 v = body->getWorldTransform().getOrigin();

	*x = v.x();
	*y = v.y();
	*z = v.z();
}

btQuaternion PhysBody3D::GetRotation() const
{
	return body->getWorldTransform().getRotation();
}

void PhysBody3D::SetRotation(btQuaternion& quat)
{
	btTransform t = body->getWorldTransform();
	t.setRotation(quat);
	body->setWorldTransform(t);
}

void PhysBody3D::SetVelocity(btVector3& v)
{
	body->setLinearVelocity(v);
}

btVector3 PhysBody3D::GetVelocity() const
{
	return body->getLinearVelocity();
}

void PhysBody3D::SetLinearFactor(float x, float y, float z)
{
	body->setLinearFactor(btVector3(x, y, z));
}

void PhysBody3D::ClampVelocity(float minv, float maxv)
{
	btVector3 v = body->getLinearVelocity();

	int x = v.x(), y = v.y(), z = v.z();

	CLAMP(x, minv, maxv);
	CLAMP(y, minv, maxv);
	CLAMP(z, minv, maxv);

	v.setValue(x, y, z);

	body->setLinearVelocity(v);
}

void PhysBody3D::ResetVelocity()
{
	body->setLinearVelocity(btVector3(0,0,0));
	body->setAngularVelocity(btVector3(0, 0, 0));
}

void PhysBody3D::ResetRotation()
{
	btTransform t = body->getWorldTransform();
	t.setRotation(btQuaternion(0, 0, 0));
	body->setWorldTransform(t);
}
