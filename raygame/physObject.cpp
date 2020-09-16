#include "physObject.h"

#include "raylib.h"

physObject::physObject()
{
	pos = glm::vec2{ 0, 0 };
	velocity = glm::vec2{ 0, 0 };
	forces = glm::vec2{ 0, 0 };

	mass = 1.0f;

	useGravity = true;

	coll = { shapeType::CIRCLE, circle{10.0f} };
}

physObject::physObject(glm::vec2 startingPos, glm::vec2 startingVelocity, float startingMass, bool useGrav)
{
	pos = startingPos;
	velocity = startingVelocity;
	forces = glm::vec2{ 0, 0 };

	mass = startingMass;

	useGravity = useGrav;

	// DEFAULT, CREATE A WAY TO OVERRIDE THIS LATER
	coll = { shapeType::CIRCLE, circle{10.0f} };
}

void physObject::tickPhysics(float deltaTime)
{
	// Intiragte forces into velocity.
	velocity += forces * deltaTime;
	forces = { 0,0 };

	// TODO: implement some linear drag

	// Intigrate velocity into position.
	pos += velocity * deltaTime;

	// SCREEN-WRAP --------------------------
	if (pos.x > (GetScreenWidth() + 10))
	{
		pos.x = -10;
	}
	if (pos.x < -10)
	{
		pos.x = GetScreenWidth() + 10;
	}
	if (pos.y > (GetScreenHeight() + 10))
	{
		pos.y = -10;
	}
	if (pos.y < -10)
	{
		pos.y = GetScreenHeight() + 10;
	}
	// --------------------------------------
}

void physObject::draw() const
{
	switch (coll.colliderShape)
	{
	case shapeType::NONE:
		DrawPixel((int)pos.x, (int)pos.y, BLACK);
		break;
	case shapeType::CIRCLE:
		DrawCircle((int)pos.x, (int)pos.y, coll.circleData.radius, WHITE);
		break;
	default:
		break;
	}
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
	forces += accel;
}

void physObject::addVelocityChange(glm::vec2 velChange)
{
	velocity += velChange;
}