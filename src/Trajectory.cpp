#include "Trajectory.h"
#include <iostream>

trajectory::trajectory()
{
	step = 0.0005f;
}

glm::vec2 trajectory::moveLinear(glm::vec2 position)
{

	if (position.x >= 1.0f) {
		step = -0.0005f;
	}
	else if (position.x <= -1.0f) {
		step = 0.0005f;
	}

	position.x = position.x + step;

	return glm::vec2(position.x, position.y);
}
