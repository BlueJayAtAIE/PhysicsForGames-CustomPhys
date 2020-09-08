#pragma once

#include <vector>

#include "physObject.h"

class game
{
	// Accumulator for physics updates.
	float accumulatedDeltaTime;

	std::vector<physObject> physObjects;

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