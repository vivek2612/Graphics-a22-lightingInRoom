#include "almirah.h"

Almirah::Almirah(float xScale, float yScale, float zScale){
	this->xScale = xScale;
	this->yScale = yScale;
	this->zScale = zScale;
	baseCubes = Cuboid(1.0f, 1.0f);
	compartment = Cuboid(10.0f, 10.0f);
}

void Almirah::createAllLists(){
	baseCubes.createAllLists();
	compartment.createAllLists();
}

void Almirah::drawAlmirah(float xTranslate, float yTranslate, float zTranslate){
	glPushMatrix();
		Texture tex;
		GLuint t= tex.loadBMP_custom("./images/wood2.bmp");   
		glTranslatef(xTranslate, yTranslate, zTranslate);
		glScalef(xScale, yScale, zScale);
		compartment.drawCuboid();
		glTranslatef(10.0f, -10.0f, 10.0f);
		baseCubes.drawCuboid();
		glTranslatef(-20.0f, 0.0f, 0.0f);
		baseCubes.drawCuboid();
		glTranslatef(0.0f, 0.0f, -20.0f);
		baseCubes.drawCuboid();
		glTranslatef(20.0f, 0.0f, 0.0f);
		baseCubes.drawCuboid();
	glPopMatrix();
}