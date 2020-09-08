#include "physObject.h"

#include "raylib.h"

physObject::physObject()
{
	pos = glm::vec2{ 0, 0 };
	velocity = glm::vec2{ 0, 0 };
	forces = glm::vec2{ 0, 0 };

	mass = 1.0f;
}

physObject::physObject(glm::vec2 startingPos, glm::vec2 startingVelocity, float startingMass)
{
	pos = startingPos;
	velocity = startingVelocity;
	forces = glm::vec2{ 0, 0 };

	mass = startingMass;
}

void physObject::tickPhysics(float deltaTime)
{
	// Intiragte forces into velocity.
	velocity += forces * deltaTime;
	forces = { 0,0 };

	// TODO: implement some linear drag

	// Intigrate velocity into position.
	pos += velocity * deltaTime;
}

void physObject::draw() const
{
	DrawCircle((int)pos.x, (int)pos.y, 10, ORANGE);
}

void physObject::addForce(glm::vec2 force)
{
	forces += force * (1.0f / mass);
}

void physObject::addImpulse(glm::vec2 impulse)
{
	velocity += impulse * (1.0f / mass);
}

void physObject::addAccel(glm::vec2 accel)
{

}

void physObject::addVelocityChange(glm::vec2 velChange)
{

}