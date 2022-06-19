#include <string>


struct ShaderProgramSource {

	std::string VertexSource;
	std::string FragmentSource;
};

class shader {

	private:
		std::string filepath;

	public:
		shader();
		void setShaderPath(std::string fp);
		ShaderProgramSource shaderRead();

};

