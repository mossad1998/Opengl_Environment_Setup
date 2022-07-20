#include "GameObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>



int gameobject::takeDamage(int d)
{
        health = health - d;
        return health;

}

int gameobject::dealDamage(int d)
{
        damage = d;
        return damage;
}

gameobject::gameobject(int h, int d)
{
    setHealth(h);
    setDamage(d);
    //setWindow(mainWindow);
}

void gameobject::movementSpeed()
{
}

void gameobject::render(int c_location, int p_location)
{
    
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glUniform4f(c_location, color.x, color.y, color.z, 0.0f);
        glUniform4f(p_location, position.x, position.y, 0.0f, 1.0f);

    
}

void gameobject::setPosition(glm::vec2 position)
{
    this->position = position;
}

glm::vec2 gameobject::getPosition() {
    return position;
}

void gameobject::setColor(glm::vec3 color)
{
    this->color = color;
}

void gameobject::setWindow(GLFWwindow* mainWindow)
{
    this->mainWindow = mainWindow;
}

void gameobject::setHealth(int health) {
    this->health = health;
}

void gameobject::setDamage(int damage) 
{
    this->damage = damage;
}

void gameobject::setSpeed(glm::vec2 speed)
{
}

void gameobject::movePlayer()
{
    if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS) {
        this->position = this->position + glm::vec2(0, 0.05);
    }

    if (glfwGetKey(this->mainWindow, GLFW_KEY_S) == GLFW_PRESS) {
        position = position + glm::vec2(0, -0.05);
    }

    if (glfwGetKey(this->mainWindow, GLFW_KEY_D) == GLFW_PRESS) {
        this->position = this->position + glm::vec2(0.05, 0);
    }

    if ((glfwGetKey(this->mainWindow, GLFW_KEY_A) == GLFW_PRESS)) {
        this->position = this->position + glm::vec2(-0.05, 0);
    }

    if (glfwGetKey(this->mainWindow, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->mainWindow, true);
    }
}
