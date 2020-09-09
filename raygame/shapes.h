#pragma once

#include <cstdint> //uint8_t

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