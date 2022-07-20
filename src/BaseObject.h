#pragma once

enum geometry {
	none = 0, 
	triangle =  1, 
	rectangle =  2, 
};

static float positionsTriangle[] = {
	   -0.5f, -0.5f,       //0
		0.5f, -0.5f,       //1
		0.5f,  0.5f,       //2
};

static unsigned int indicesTriangle[] = {
	0,1,2,              //first triangle
};

static float positionsRectangle[] = {
	   -0.5f, -0.5f,       //0
		0.5f, -0.5f,       //1
		0.5f,  0.5f,       //2
	   -0.5f,  0.5f,       //3
};

static unsigned int indicesRectangle[] = {
	0,1,2,              //first triangle
	2,3,0               //second triangle
};

class Baseobject{
	public:
		geometry type;
		float* positionContainer;
		unsigned int* incdicesContainer;
		Baseobject(geometry type);
		void setType(geometry type);
		int getType();
		void bindBuffer();
		
	private:
		void containerWork();
		
		

};