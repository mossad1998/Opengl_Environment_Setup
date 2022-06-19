#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>


shader::shader()
{
    filepath = "";
    std::cout << "Please set the path of the shader" << std::endl;
}

void shader::setShaderPath(std::string fp)
{
    filepath = fp;
}

ShaderProgramSource shader::shaderRead()
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
