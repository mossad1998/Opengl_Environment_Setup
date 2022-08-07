#pragma once

#include <glm.hpp>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <string>


class gameobject {
private:
	glm::vec2 position;
	glm::vec2 speed;
	glm::vec3 color;
	int health;
	int damage;
	int spawnNumber;
	std::string healthMap;
	std::string spawnMap;
	GLFWwindow* mainWindow;
	void setHealth(int health);
	void setDamage(int damage);
	void setSpeed(glm::vec2 speed);

	public:
		gameobject(int h, int d);
		void movePlayer();
		void takeDamage(int d);
		int dealDamage(int d);
		void moveEnemy(void);
		void movementSpeed();
		void render(int c_location, int p_location);
		void setPosition(glm::vec2 position);
		glm::vec2 getPosition();
		void setColor(glm::vec3 color);
		void setWindow(GLFWwindow* mainWindow);
		std::string* getHealth();
		std::string* getSpawn();
		void spawnLost();


};