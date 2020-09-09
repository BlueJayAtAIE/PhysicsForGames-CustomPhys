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