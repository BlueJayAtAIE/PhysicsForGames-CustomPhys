#pragma once

#include <cstdint> //uint8_t

#include "vec2.hpp" //vec 2

struct circle
{
	float radius;
};

struct AABB
{
	glm::vec2 dimentions;
};

enum class shapeType : uint8_t
{
	NONE = 0,
	CIRCLE = 1 << 0,
	AABB = 1 << 1
};

struct collider
{
	shapeType colliderShape;

	union
	{
		circle circleData;
		AABB AABBData;
	};
};

bool checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB);
bool checkCircleCircle(glm::vec2 posA, collider circleA, glm::vec2 posB, collider circleB);

bool checkCircleAABB(glm::vec2 posA, circle circle, glm::vec2 posB, AABB AABB);
bool checkCircleAABB(glm::vec2 posA, collider circle, glm::vec2 posB, collider AABB);

bool checkAABBAABB(glm::vec2 posA, AABB AABBa, glm::vec2 posB, AABB AABBb);
bool checkAABBAABB(glm::vec2 posA, collider AABBa, glm::vec2 posB, collider AABBb);


glm::vec2 depenetrationCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB, float& pen);
glm::vec2 depenetrationCircleCircle(glm::vec2 posA, collider circleA, glm::vec2 posB, collider circleB, float& pen);

glm::vec2 depenetrationCircleAABB(glm::vec2 posA, circle circle, glm::vec2 posB, AABB AABB, float& pen);
glm::vec2 depenetrationCircleAABB(glm::vec2 posA, collider circle, glm::vec2 posB, collider AABB, float& pen);

glm::vec2 depenetrationAABBAABB(glm::vec2 posA, AABB AABBa, glm::vec2 posB, AABB AABBb, float& pen);
glm::vec2 depenetrationAABBAABB(glm::vec2 posA, collider AABBa, glm::vec2 posB, collider AABBb, float& pen);


void resoloveCollision(glm::vec2 posA, glm::vec2 velA, float massA,
					   glm::vec2 posB, glm::vec2 velB, float massB,
					   float elasticity, glm::vec2 colNormal, glm::vec2 *dst);