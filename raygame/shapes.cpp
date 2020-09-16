#include "shapes.h"

#include "glm/glm.hpp"

#pragma region checks

bool checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB)
{
	// Get the distance between the two circles
	float dist = glm::length(posA - posB);

	// Get the sum of the radi
	float sum = circleA.radius + circleB.radius;

	// Return dist < sum
	return dist < sum;
}

bool checkCircleCircle(glm::vec2 posA, collider circleA, glm::vec2 posB, collider circleB)
{
	return checkCircleCircle(posA, circleA.circleData, posB, circleB.circleData);
}

bool checkCircleAABB(glm::vec2 posA, circle circle, glm::vec2 posB, AABB AABB)
{
	// Clamp the values of the circle's center to be along the AABB's bounds.
	glm::vec2 clampedPoint = { glm::clamp(posA.x, posB.x + (AABB.dimentions.x / 2), posB.x - (AABB.dimentions.x / 2)),
							   glm::clamp(posA.y, posB.y + (AABB.dimentions.y / 2), posB.y - (AABB.dimentions.y / 2)) };

	float dist = glm::length(clampedPoint - posA);

	// Compare the distance from the circle's center to the clamped point and the circle's radius.
	// If the radius is greater or equal to- they're colliding.
	return circle.radius >= dist;
}

bool checkCircleAABB(glm::vec2 posA, collider circle, glm::vec2 posB, collider AABB)
{
	return checkCircleAABB(posA, circle.circleData, posB, AABB.AABBData);
}

bool checkAABBAABB(glm::vec2 posA, AABB AABBa, glm::vec2 posB, AABB AABBb)
{
	// Get the min/max of AABBa.
	glm::vec2 AABBaMin = { posA.x - AABBa.dimentions.x / 2, posA.y - AABBa.dimentions.y / 2 };
	glm::vec2 AABBaMax = { posA.x + AABBa.dimentions.x / 2, posA.y + AABBa.dimentions.y / 2 };

	// Get the min/max of AABBa.
	glm::vec2 AABBbMin = { posA.x - AABBb.dimentions.x / 2, posA.y - AABBb.dimentions.y / 2 };
	glm::vec2 AABBbMax = { posA.x + AABBb.dimentions.x / 2, posA.y + AABBb.dimentions.y / 2 };

	// It's faster to check if they DON't collide since it's quicker to exit.
	// Return a value based on if none of the maximum points on either AABB are less than the minimums.
	//return !(AABBbMax.x < AABBaMin.x || AABBaMax.x < AABBbMin.x || AABBbMax.y < AABBaMin.y || AABBaMax.y < AABBbMin.y);
	return AABBaMin.x < AABBbMax.x && AABBaMax.x > AABBbMin.x && AABBaMin.y < AABBbMax.y && AABBaMax.y > AABBbMin.y;
}

bool checkAABBAABB(glm::vec2 posA, collider AABBa, glm::vec2 posB, collider AABBb)
{
	return checkAABBAABB(posA, AABBa.AABBData, posB, AABBb.AABBData);
}

#pragma endregion

#pragma region depenetration

glm::vec2 depenetrationCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB, float& pen)
{
	// Calculate their distances.
	float distance = glm::length(posA - posB);

	// pen = the difference between the sum of their radi - distance between two circles
	float sum = circleA.radius + circleB.radius;

	pen = sum - distance;

	// coll normal is normalized vec between two pos
	return glm::normalize(posA - posB);
}

glm::vec2 depenetrationCircleCircle(glm::vec2 posA, collider circleA, glm::vec2 posB, collider circleB, float& pen)
{
	return depenetrationCircleCircle(posA, circleA.circleData, posB, circleB.circleData, pen);
}

glm::vec2 depenetrationCircleAABB(glm::vec2 posA, circle circleA, glm::vec2 posB, AABB AABB, float& pen)
{
	return glm::vec2();
}

glm::vec2 depenetrationCircleAABB(glm::vec2 posA, collider circle, glm::vec2 posB, collider AABB, float& pen)
{
	return depenetrationCircleAABB(posA, circle.circleData, posB, AABB.AABBData, pen);
}

glm::vec2 depenetrationAABBAABB(glm::vec2 posA, AABB AABBa, glm::vec2 posB, AABB AABBb, float& pen)
{
	// Find which axis has more penetration.
	// The one
	pen = glm::max(glm::length(posA.x - posB.x), glm::length(posA.y - posB.y));

	// Use that axis as the normal???.
	return glm::normalize(posA - posB);
}

glm::vec2 depenetrationAABBAABB(glm::vec2 posA, collider AABBa, glm::vec2 posB, collider AABBb, float& pen)
{
	return depenetrationAABBAABB(posA, AABBa.AABBData, posB, AABBb.AABBData, pen);
}

#pragma endregion

void resoloveCollision(glm::vec2 posA, glm::vec2 velA, float massA, glm::vec2 posB, glm::vec2 velB, float massB, float elasticity, glm::vec2 colNormal, glm::vec2* dst)
{
	// Calculate relitive velocity.
	glm::vec2 relVel = velA - velB;

	// Calculate inpulse magnitutde.
	float impulseMag = glm::dot(-(1.0f + elasticity) * relVel, colNormal) / 
					   glm::dot(colNormal, colNormal * (1 / massA + 1 / massB));

	// Write all impulses for the two objects into the given array.
	dst[0] = velA + (impulseMag / massA) * colNormal;
	dst[1] = velB - (impulseMag / massB) * colNormal;
}