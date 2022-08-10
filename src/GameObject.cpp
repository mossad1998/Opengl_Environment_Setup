#include "GameObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>



void gameobject::takeDamage(int d)
{

    static float timeLastCalled = 0.0f;
    float time = (float)glfwGetTime();
    if (time - timeLastCalled > 5.0f) {

        timeLastCalled = (float)glfwGetTime();
        std::cout << time << std::endl;

        health = health - d;
        healthMap.clear();
        for (int i = 0; i < (health / 10) + 1; i++) {
            healthMap.append("#");
        }

    }
}

int gameobject::dealDamage(int d)
{
        damage = d;
        return damage;
}

void gameobject::moveEnemy(void)
{
    //Move anyway
    this->position = this->position + this->speed;

    //Red Flag (switch velocity)
    if (this->position.x >= 1) {
        this->setSpeed(speed*-1.0f);
    }

    //Yellow Flag (switch velocity)
    else if (this->position.x <= -1) {
        this->setSpeed(speed * -1.0f);
    }

}

gameobject::gameobject(int h, int d)
{
    setHealth(h);
    setDamage(d);
    setSpeed(glm::vec2(0.0005f, 0.000f));
    spawnNumber = 5;
    for (int i = 0; i < (health / 10) + 1; i++) {
        healthMap.append("#");
    }

    for (int i = 0; i < spawnNumber; i++) {
        spawnMap.append("#");
    }
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

std::string* gameobject::getHealth()
{
    return &healthMap;
}

std::string* gameobject::getSpawn()
{
    return &spawnMap;
}

void gameobject::spawnLost()
{

    spawnNumber = spawnNumber - 1;
    spawnMap.clear();
    std::cout << "gothtere" << std::endl;
    for (int i = 0; i < spawnNumber; i++) {
        spawnMap.append("#");
    }


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
    this->speed = speed;
}

void gameobject::movePlayer()
{
    static float timeLastCalled = 0.0f;
    float time = (float)glfwGetTime();

    if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS) {
        this->position = this->position + glm::vec2(0, 0.0005);
    }

    if (glfwGetKey(this->mainWindow, GLFW_KEY_S) == GLFW_PRESS) {
        position = position + glm::vec2(0, -0.0005);
    }

    if (glfwGetKey(this->mainWindow, GLFW_KEY_D) == GLFW_PRESS) {
        this->position = this->position + glm::vec2(0.0005, 0);
    }

    if ((glfwGetKey(this->mainWindow, GLFW_KEY_A) == GLFW_PRESS)) {
        this->position = this->position + glm::vec2(-0.0005, 0);
    }

    if (glfwGetKey(this->mainWindow, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->mainWindow, true);
    }
    if (glfwGetKey(this->mainWindow, GLFW_KEY_SPACE) == GLFW_PRESS) {

        if (time - timeLastCalled > 5.0f) {
            timeLastCalled = (float)glfwGetTime();
            this->position = glm::vec2(0.0f, 0.0f);
            spawnLost();
        }
    }
}
