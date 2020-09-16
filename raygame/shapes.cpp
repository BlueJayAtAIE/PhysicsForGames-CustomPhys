#include "shapes.h"

#include "glm/glm.hpp"

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

void resoloveCollision(glm::vec2 posA, glm::vec2 velA, float massA, glm::vec2 posB, glm::vec2 velB, float massB, float elasticity, glm::vec2 colNormal, glm::vec2* dst)
{
	// Calculate relitive velocity.
	glm::vec2 relVel = velA - velB;

	// Calculate inpulse magnitutde.
	float impulseMag = glm::dot(-(-1.0f + elasticity) * relVel, colNormal) / 
					   glm::dot(colNormal, colNormal * (1 / massA + 1 / massB));

	// Write all impulses for the two objects into the given array.
	dst[0] = velA + (impulseMag / massA) * colNormal;
	dst[1] = velB - (impulseMag / massB) * colNormal;
}