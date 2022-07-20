#include "Game.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm.hpp>


game::game(std::string gameName, int width, int length)
{
	this->gameName = gameName;
	this->width = width;
	this->length = length;
    m_LastFrameTime = 0.0f;
}

int game::createWindow()
{
    // Initialize the library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(length, width, gameName.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize the library
    if (glewInit() != GLEW_OK)
        std::cout << "ERROR!!! in glew intialization" << std::endl;

}

void game::bindBuffers()
{
    mainObject = new Baseobject(geometry::triangle);
    mainObject->bindBuffer();
}

void game::createShader()
{
    mainShader = new shader;
    mainShader->setShaderPath("Resources/Shaders/basic.shader");
    ShaderProgramSource source = mainShader->readShader();
    this->shaderAddress = mainShader->createShader(source.VertexSource, source.FragmentSource);
    glUseProgram(this->shaderAddress);
}

void game::objectsInitialization()
{
     macdonalds = new gameobject(69, 42);
     kfc = new gameobject(96, 24);

     //Initial objects
     kfc->setWindow(window);
     macdonalds->setWindow(window);
     //macdonalds->setPosition(glm::vec2(0.0f, 0.0f));
     kfc->setPosition(glm::vec2(0.5f, 0.5f));
}

game::~game()
{
    delete mainObject;
    delete mainShader;

    //Game Objects
    delete macdonalds;
    delete kfc;
}

GLFWwindow* game::getWindow()
{
    return this->window;
}

unsigned int game::getShaderAddress()
{
    return this->shaderAddress;
}

void game::gameInitialization()
{
    //main Initializations
    createWindow();
    bindBuffers();
    createShader();

    //create game objects
    objectsInitialization();
}

void game::gameLoop()
{

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        float time = (float)glfwGetTime();
        Time_Stamp timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        update(timestep, time);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
}



void game::update(Time_Stamp ts, float time) {

    static glm::vec2 postion = glm::vec2(0.0f, 0.0f);

    static float r = 0.0f;
    static float increment = 0.0005f;

    static float p = 0.0f;
    static float increment_p = 0.0005f;

    m_LastFrameTime = time;
    std::cout << 1 / ts.GetSeconds() << std::endl;


    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    macdonalds->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
    macdonalds->render(mainShader->getColorUniformAddress(), mainShader->getPositionUniformAddress());
    macdonalds->movePlayer();

    kfc->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
    kfc->render(mainShader->getColorUniformAddress(), mainShader->getPositionUniformAddress());




    //glUniform4f(c_location, r, 0.3f, 0.8f, 1.0f);
    //glUniform4f(mainShader->getPositionUniformAddress(), postion.x, postion.y, 0.0f, 1.0f);
    /*
        if (r > 1.0f) {
        increment = -0.0005f;
    }
    else if (r < 0.0f) {
        increment = 0.0005f;
    }

    r = r + increment;
    */


    if (p > 1.0f) {
        increment_p = -0.0005f;
    }
    else if (p < 0.0f) {
        increment_p = 0.0005f;
    }

    p = p + increment_p;

}

