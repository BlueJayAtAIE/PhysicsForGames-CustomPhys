#include "game.h"
#include "raylib.h"
#include <iostream>

game::game()
{
	accumulatedDeltaTime = 0.0f;
	fixedTimeStep = 1.0f / 30.0f;
}

void game::init()
{
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Jay's Physics Sim");

	SetTargetFPS(60);
}

bool game::tick()
{
	//std::cout << "do update!" << std::endl;

	// Add delta time to the accumulator.
	accumulatedDeltaTime += GetFrameTime();

	return !WindowShouldClose();
}

void game::tickPhysics()
{
	//std::cout << "do physics!" << std::endl;

	accumulatedDeltaTime -= fixedTimeStep;
}

bool game::shouldTickPhysics() const
{
	return accumulatedDeltaTime >= fixedTimeStep;
}

void game::draw() const
{
	BeginDrawing();
	
	ClearBackground(SKYBLUE);

	// Draws for objects happen here after the background clear.
	// ----------------------------------------------------------



	// ----------------------------------------------------------
	EndDrawing();
}

void game::exit()
{
	CloseWindow();
}
