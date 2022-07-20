#include"Shader.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>

shader::shader()
{
	filepath = "";
	std::cout << "Please enter the shader path" << std::endl;
}

void shader::setShaderPath(std::string fp)
{
	filepath = fp;
}

ShaderProgramSource shader::readShader()
{
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

unsigned int shader::compileShader(unsigned int type , const std::string& source)
{
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
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertix " : "fragment ") << "shader!!!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
    }

    return id;
}

unsigned int shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    colorUniformAddress = glGetUniformLocation(program, "u_color");
    positionUniformAddress = glGetUniformLocation(program, "u_position");

    return program;
}

int shader::getColorUniformAddress()
{
    return this->colorUniformAddress;
}

int shader::getPositionUniformAddress()
{
    return this->positionUniformAddress;
}
