#pragma once

#include <vector>           // vector
#include <unordered_map>    // unordered map, like a hashtable

#include "physObject.h" 

using collisionPair = uint8_t; // type-alias, like a typedef - for better readability.
using collisionFunc = bool(*)(glm::vec2, collider, glm::vec2, collider);  // RETURN_TYPE(*)(PARAMETER_TYPES) - function pointer - so we can call them later
using collisionMap = std::unordered_map<collisionPair, collisionFunc>; // unordered map is basically a hash table
// Given two objects, we need to figure out what function to call in order to test whether they're in collision.
// Type punning.


class game
{
	// Accumulator for physics updates.
	float accumulatedDeltaTime;

	std::vector<physObject> physObjects;

	static collisionMap collisionCheckers;

public:
	game();

	// Time between every fixed update.
	// Expressed in seconds.
	float fixedTimeStep;

	// Create window and initialize the rendering context.
	void init(int screenWidth, int screenHeight, float timeStep);

	// Update logic for the game.
	// - Return true for as long as the window stays open.
	bool tick();

	// Update the physics logic for the game.
	// This should run every fixed timespan.
	void tickPhysics();

	// Determines if the physics should update on this tick.
	// - Returns true if the accumulated time is greater or equal to our fixedTimeStep.
	bool shouldTickPhysics() const;

	// Render all the objects for the game.
	void draw() const;

	// Destroy the window and deinitialize the rendering context.
	void exit();
};