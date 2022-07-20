#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <string>
#include "BaseObject.h"
#include "Shader.h"
#include"Time_Stamp.h"
#include "GameObject.h"


class game {

	public:
		game(std::string gameName,int width,int length);
		void gameInitialization();
		void update(Time_Stamp ts, float time);
		void gameLoop();


		GLFWwindow* getWindow();
		unsigned int getShaderAddress();
		~game();
		



	private:
		//Game window
		std::string gameName;
		int length; 
		int width;
		GLFWwindow* window;
		int createWindow();

		//Game base object
		Baseobject* mainObject;
		void bindBuffers();

		//Game shader
		shader* mainShader;
		unsigned int shaderAddress;
		void createShader();

		//Game fps calculation
		float m_LastFrameTime;

		//Game objects
		gameobject* macdonalds;
		gameobject* kfc;
		void objectsInitialization();


};