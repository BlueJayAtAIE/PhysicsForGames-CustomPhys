#include "game.h"

#include <iostream> // cout
#include <ctime> // time
#include <cstdlib> // rand, srand

#include "raylib.h"

game::game()
{
	accumulatedDeltaTime = 0.0f;
	fixedTimeStep = 1.0f / 30.0f;
}

void game::init(int screenWidth, int screenHeight, float timeStep)
{
	InitWindow(screenWidth, screenHeight, "Jay's Physics Sim");

	SetTargetFPS(60);

	fixedTimeStep = timeStep;

	// Seed RNG with unique value (in this case, system time).
	srand(time(0));
}

bool game::tick()
{
	// Add delta time to the accumulator.
	accumulatedDeltaTime += GetFrameTime();

	// If clicked, add a new physObject.
	if (IsMouseButtonPressed(0))
	{
		auto cursorPos = GetMousePosition();

		physObject baby({ cursorPos.x, cursorPos.y }, { 0,0 }, (rand() % 10) + 1);
		baby.addImpulse({ 100, 0 });

		physObjects.push_back(baby);
	}

	// TODO: hold right click pushes away particles within a radius.

	return !WindowShouldClose();
}

void game::tickPhysics()
{
	accumulatedDeltaTime -= fixedTimeStep;

	// TODO: gravity for all physics objects which have gravity enabled.

	// Update all physObjects.
	for (auto& obj : physObjects)
	{
		obj.tickPhysics(fixedTimeStep);
	}

	// TODO: screenwrap?
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
	for (auto& obj : physObjects)
	{
		obj.draw();
	}


	// ----------------------------------------------------------
	EndDrawing();
}

void game::exit()
{
	CloseWindow();
}
