#pragma once

#include <glm.hpp>


class trajectory {


private:
	float step;



public:
	trajectory();
	glm::vec2 moveLinear(glm::vec2 position);



};