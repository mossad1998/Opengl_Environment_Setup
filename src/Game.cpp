#include "Game.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm.hpp>
#include <GL/glut.h>



game::game(std::string gameName, int width, int length)
{
	this->gameName = gameName;
	this->width = width;
	this->length = length;
    m_LastFrameTime = 0.0f;
}

void game::output(float x, float y, float r, float g, float b, const char* string)
{

    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
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
    mainObject_1 = new Baseobject(geometry::triangle);
    mainObject_1->bindBuffer();

    mainObject_2 = new Baseobject(geometry::rectangle);
    mainObject_2->bindBuffer();
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
     macdonalds->setPosition(glm::vec2(0.5f, 0.5f));
     //kfc->setPosition(glm::vec2(0.5f, 0.5f));
}

void game::fight()
{
    //std::cout << macdonalds->getPosition().x << "," << kfc->getPosition().x << std::endl;
    if (macdonalds->getPosition().x - kfc->getPosition().x <.01 &&
        macdonalds->getPosition().y - kfc->getPosition().y < .01)
    {
        macdonalds->takeDamage(20);
    }
}

void game::gameMenu()
{
    if (glfwGetKey(this->window, GLFW_KEY_P) == GLFW_PRESS) {

        int static counter = 0;

        while (1) {
            if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                break;
            }
            
            static float timeLastCalled = 0.0f;
            float time = (float)glfwGetTime();
            if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS && time - timeLastCalled > 0.2f) {
                counter++;
                timeLastCalled = (float)glfwGetTime();
            }
            else if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS && time - timeLastCalled > 0.2f) {
                counter--;
                timeLastCalled = (float)glfwGetTime();
            }
                

            glClear(GL_COLOR_BUFFER_BIT);

            if(counter % 3 == 0)
            {
                output(-0.1f, 0.5f, 0.0f, 0.0f, 1.0f, "->");
            }
            else if (counter %3 == 1 || counter % 3 == -2)
            {
                output(-0.1f, 0.4f, 0.0f, 0.0f, 1.0f, "->");
            }
            else if (counter % 3 == 2 || counter % 3 == -1)
            {
                output(-0.1f, 0.3f, 0.0f, 0.0f, 1.0f, "->");
            }

            if (glfwGetKey(this->window, GLFW_KEY_ENTER) == GLFW_PRESS) {
                if (counter % 3 == 0)
                {
                    break;
                }
                else if (counter % 3 == 1 || counter % 3 == -2)
                {
                    //OPen setting Menu Function
                }
                else if (counter % 3 == 2 || counter % 3 == -1)
                {
                    glfwSetWindowShouldClose(this->window, true);
                    break;
                };

            }

            output(0.0f, 0.5f, 0.0f, 0.0f, 1.0f, "Start");
            output(0.0f, 0.4f, 0.0f, 0.0f, 1.0f, "Settings");
            output(0.0f, 0.3f, 0.0f, 0.0f, 1.0f, "Exit");

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();

        }
    }
}


game::~game()
{
    delete mainObject_1;
    delete mainObject_2;
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
        fight();

        output(-0.7f, 0.8f, 1.0f, 0.0f, 0.0f, "Health");
        output(-0.7f, 0.7f, 1.0f, 0.0f, 0.0f, macdonalds->getHealth()->c_str());

        output(0.7f, 0.8f, 1.0f, 0.0f, 0.0f, "Spawn");
        output(0.7f, 0.7f, 1.0f, 0.0f, 0.0f, macdonalds->getSpawn()->c_str());

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        gameMenu();
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
    //Time Stamp
    //std::cout << 1 / ts.GetSeconds() << std::endl;


    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    macdonalds->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
    macdonalds->render(mainShader->getColorUniformAddress(), mainShader->getPositionUniformAddress());
    macdonalds->movePlayer();

    kfc->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
    kfc->render(mainShader->getColorUniformAddress(), mainShader->getPositionUniformAddress());

    kfc->moveEnemy();


    if (p > 1.0f) {
        increment_p = -0.0005f;
    }
    else if (p < 0.0f) {
        increment_p = 0.0005f;
    }

    p = p + increment_p;

}

