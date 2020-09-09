#pragma once

#include "glm.hpp" //vec2

#include "shapes.h" // collider

class physObject
{
	glm::vec2 forces;

public:
	glm::vec2 pos;
	glm::vec2 velocity;
	float mass;
	bool useGravity;

	collider coll;

	physObject();
	physObject(glm::vec2 startingPos, glm::vec2 startingVelocity, float startingMass, bool useGrav);

	// Apply forces and change the position for this tick.
	void tickPhysics(float deltaTime);

	// Draw the object's sprite.
	void draw() const;

	// Add a continuous force to the object using its mass.
	void addForce(glm::vec2 force);

	// Add an instant force to the object using its mass.
	void addImpulse(glm::vec2 impulse);

	// Add a continuous force to the object ignoring its mass.
	void addAccel(glm::vec2 accel);

	// Add an instant force to the object ignoring its mass.
	void addVelocityChange(glm::vec2 velChange);
};