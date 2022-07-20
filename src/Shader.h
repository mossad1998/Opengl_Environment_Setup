#pragma once

#include <string>

struct ShaderProgramSource {

    std::string VertexSource;
    std::string FragmentSource;
};

class shader {

    private:
        std::string filepath;
        int id;
        unsigned int compileShader(unsigned int type, const std::string& source);
        int colorUniformAddress;
        int positionUniformAddress;

    public:
        shader();
        void setShaderPath(std::string fp);
        ShaderProgramSource readShader();
        unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
        int getColorUniformAddress();
        int getPositionUniformAddress();

};