#pragma once

#include <cstdint> //uint8_t

#include "vec2.hpp" //vec 2

struct circle
{
	float radius;
};

// TODO: create an AABB shape

enum class shapeType : uint8_t
{
	NONE = 0,
	CIRCLE = 1 << 0,
	AABB = 1 << 1 // TODO: implement AABBs into our shape system
};

struct collider
{
	shapeType colliderShape;
	union
	{
		circle circleData;
		// TODO: add the data for an AABB
	};
};

bool checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB);
bool checkCircleCircle(glm::vec2 posA, collider circleA, glm::vec2 posB, collider circleB);

glm::vec2 depenetrationCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB, float& pen);
glm::vec2 depenetrationCircleCircle(glm::vec2 posA, collider circleA, glm::vec2 posB, collider circleB, float& pen);

void resoloveCollision(glm::vec2 posA, glm::vec2 velA, float massA,
					   glm::vec2 posB, glm::vec2 velB, float massB,
					   float elasticity, glm::vec2 colNormal, glm::vec2 *dst);