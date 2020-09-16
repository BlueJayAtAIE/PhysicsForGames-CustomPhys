// HEADER
#include "game.h"

// SYSTEM LIBRAIES
#include <iostream> // cout
#include <ctime> // time
#include <cstdlib> // rand, srand

// PROJECT LIBRARIES
#include "raylib.h"

// PROJECT HEADERS
#include "enumUtils.h"

// Define a function that initializes our static variable.
collisionMap setupCollisionChecks()
{
	collisionMap map;
	map[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::CIRCLE)] = checkCircleCircle;
	map[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::AABB)] = checkCircleAABB;
	map[static_cast<collisionPair>(shapeType::AABB | shapeType::AABB)] = checkAABBAABB;

	return map;
}

depenetrationMap setupDepenetrationFuncs()
{
	depenetrationMap map;
	map[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::CIRCLE)] = depenetrationCircleCircle;
	map[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::AABB)] = depenetrationCircleAABB;
	map[static_cast<collisionPair>(shapeType::AABB | shapeType::AABB)] = depenetrationAABBAABB;

	return map;
}

// Define the static variable in game.
collisionMap game::collisionCheckers = setupCollisionChecks();
depenetrationMap game::depenetrationFuncs = setupDepenetrationFuncs();

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
	// Left click for Circle,
	if (IsMouseButtonPressed(0))
	{
		auto cursorPos = GetMousePosition();

		physObject baby({ cursorPos.x, cursorPos.y }, { 0,0 }, (rand() % 10) + 3, true);
		baby.coll.colliderShape = shapeType::CIRCLE;
		baby.coll.circleData.radius = baby.mass;
		baby.addImpulse({ rand() % 201 , rand() % 201 });

		physObjects.push_back(baby);
	}

	// and Right click for AABB.
	if (IsMouseButtonPressed(1))
	{
		auto cursorPos = GetMousePosition();

		physObject baby({ cursorPos.x, cursorPos.y }, { 0,0 }, (rand() % 10) + 5, true);
		baby.coll.colliderShape = shapeType::AABB;
		baby.coll.AABBData.dimentions = { baby.mass, baby.mass };
		baby.addImpulse({ rand() % 201 , rand() % 201 });

		physObjects.push_back(baby);
	}

	// TODO: hold right click pushes away particles within a radius.

	return !WindowShouldClose();
}

void game::tickPhysics()
{
	accumulatedDeltaTime -= fixedTimeStep;

	for (auto& lhs : physObjects)
	{
		if (lhs.useGravity)
		{
			lhs.addForce({ 0, 9.81f }); // Consider other ways of adding gravity maybe?
		}

		// TODO optimize with spatial partitioning

		// Test for collision
		for (auto& rhs : physObjects)
		{
			// Skip ourselves
			if (&lhs == &rhs) { continue; }

			auto* first = &lhs;
			auto* second = &rhs;

			// Swap our pointers around so they're in the right order.
			// static_cast<TARGET_TYPE>(VARIABLE) is effectively the same as (TARGET_TYPE)VARIABLE
			if (static_cast<uint8_t>(lhs.coll.colliderShape) > static_cast<uint8_t>(rhs.coll.colliderShape))
			{
				first = &rhs;
				second = &lhs;
			}

			// Get type of collision to test for.
			collisionPair pairType = static_cast<collisionPair>(lhs.coll.colliderShape | lhs.coll.colliderShape);

			// Get the collision check function to call, and then call it.
			bool collision = collisionCheckers[pairType](first->pos, first->coll, second->pos, second->coll);

			// Gather collision response data.
			if (collision)
			{
				float pen = 0.0f;

				// Generate responding impulses.
				glm::vec2 normal = depenetrationFuncs[pairType](first->pos, first->coll, second->pos, second->coll, pen);

				glm::vec2 resImpulses[2];

				resoloveCollision(first->pos, first->velocity, first->mass, second->pos, second->velocity, second->mass, 1.0f, normal, resImpulses);
				// Physically separate the two objects.
				first->pos += normal * pen;
				second->pos -= normal * pen;

				// Update their velocities.
				first->velocity = resImpulses[0];
				second->velocity = resImpulses[1];
			}
		}
	}

	// Update all physObjects.
	for (auto& obj : physObjects)
	{
		obj.tickPhysics(fixedTimeStep);
	}
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
