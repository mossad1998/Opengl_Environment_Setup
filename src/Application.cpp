#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>
#include <fstream>
#include <sstream>
#include <string>
#include "Time.h"
#include <thread>
#include "Time_Stamp.h"
#include "gtc/type_ptr.hpp"




static float m_LastFrameTime = 1;

struct ShaderProgramSource {

    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource readShader(const std::string& filepath) {

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1

    };

    std::ifstream stream(filepath);
    std::stringstream ss[2];
    std::string line;

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {

            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }

        }
        else {
            ss[(int)type] << line << '\n';
        }

    }

    return { ss[0].str(), ss[1].str() };
}


static unsigned int CompileShader(unsigned int type, const std::string& source) {

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertix " : "fragment ") << "shader!!!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
    }

    return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    return program;
}

void update(int location,int mat4_location,Time_Stamp ts,float time) {


    static float r = 0.0f;
    static float increment = 0.0005f;

    static float x = 0.0f;
    static float x_increment = 0.0005f;

    m_LastFrameTime = time;

    std::cout << 1/ts.GetSeconds() << std::endl;
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    //glDrawArrays(GL_TRIANGLES, 0, 6);

    glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
    glUniform4f(mat4_location, x, 0.3f, 0.0f, 1.0f);



    if (r > 1.0f) {
        increment = -0.0005f;
    }
    else if (r < 0.0f) {
        increment = 0.0005f;
    }

    r = r + increment;

    if (x > 1.0f) {
        x_increment = -0.0005f;
    }
    else if (x < 0.0f) {
        x_increment = 0.0005f;
    }

    x = x + x_increment;

}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Basic Shader", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize the library */
    if (glewInit() != GLEW_OK)
        std::cout << "ERROR!!! in glew intialization" << std::endl;

    float positions[] = {
        -0.5f, -0.5f,       //0
         0.5f, -0.5f,       //1
         0.5f,  0.5f,       //2
        -0.5f,  0.5f,       //3
    };

    unsigned int indices[] = {
        0,1,2,              //first triangle
        2,3,0               //second triangle
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
   
    ShaderProgramSource source = readShader("Resources/Shaders/basic.shader");

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_color");
    int mat4_location = glGetUniformLocation(shader, "u_transformation_matrix");




    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        float time = (float)glfwGetTime();
        Time_Stamp timestep = time -  m_LastFrameTime;
        m_LastFrameTime = time;

        //m_LastFrameTime = time;


        update(location, mat4_location, timestep, time);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}