#include "BaseObject.h"
#include <GL/glew.h>

Baseobject::Baseobject(geometry type)
{
	this->type = type;
}

void Baseobject::setType(geometry type)
{
	this->type = type;
}

int Baseobject::getType()
{
	return type;
}

void Baseobject::containerWork()
{
	int pT = sizeof(positionsTriangle) / sizeof(float);
	int iT = sizeof(indicesTriangle) / sizeof(unsigned int);
	int pR = sizeof(positionsRectangle) / sizeof(float);
	int iR = sizeof(indicesRectangle) / sizeof(unsigned int);
	
	if (type == geometry::triangle) {
		positionContainer = new float[pT];
		incdicesContainer = new unsigned int[iT];

		for (int i = 0; i < pT; i++) {
			positionContainer[i] = positionsTriangle[i];
		}

		for (int y = 0; y < iT; y++) {
			incdicesContainer[y] = indicesTriangle[y];
		}
	}

	else if (type == geometry::rectangle) {
		positionContainer = new float[pR];
		incdicesContainer = new unsigned int[iR];
		
		for (int i = 0; i < pR; i++) {
			positionContainer[i] = positionsRectangle [i];
		}

		for (int y = 0; y < iR; y++) {
			incdicesContainer[y] = indicesRectangle[y];
		}
	}
}

void Baseobject::bindBuffer()
{
	containerWork();

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER,type * 6 * sizeof(float), positionContainer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int indexBufferObject;
	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, type * 6 * sizeof(unsigned int), incdicesContainer, GL_STATIC_DRAW);
}


