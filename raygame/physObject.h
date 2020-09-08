#pragma once

#include "glm.hpp"

class physObject
{
	glm::vec2 forces;

public:
	glm::vec2 pos;
	glm::vec2 velocity;
	float mass;

	physObject();
	physObject(glm::vec2 startingPos, glm::vec2 startingVelocity, float startingMass);

	// Apply forces and change the position for this tick.
	void tickPhysics(float deltaTime);

	// Draw the object's sprite.
	void draw() const;

	// addForce
	void addForce(glm::vec2 force);

	// addImpulse
	void addImpulse(glm::vec2 impulse);

	// addAcceleration
	void addAccel(glm::vec2 accel);

	// addVelocityChange
	void addVelocityChange(glm::vec2 velChange);
};