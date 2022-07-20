#pragma once

#include <glm.hpp>
#include "GL/glew.h"
#include <GLFW/glfw3.h>

class gameobject {
	private:
		int health;
		int damage;
		glm::vec2 speed;
		glm::vec2 position;
		glm::vec3 color;
		GLFWwindow* mainWindow;
		void setHealth(int health);
		void setDamage(int damage);
		void setSpeed(glm::vec2 speed);

	public:
		void movePlayer();
		int takeDamage(int d);
		int dealDamage(int d);
		gameobject(int h, int d);
		void movementSpeed();
		void render(int c_location, int p_location);
		void setPosition(glm::vec2 position);
		glm::vec2 getPosition();
		void setColor(glm::vec3 color);
		void setWindow(GLFWwindow* mainWindow);

};