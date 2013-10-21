#include "lamp.h"

Lamp::Lamp(float height, float radius){
	this->height = height;
	this->radius = radius;
}

void Lamp::createAllLists(){
	lampList=glGenLists (1);
	glNewList(lampList, GL_COMPILE);
		glColor3f(1.0f, 0.8f, 0.2f);    
		glTranslatef(0.0f, 0.0f, -20.0f);
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,3*radius,1.5*radius,0.3*height,32,32);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluDisk(quadratic,0.0f,radius,32,32);
		gluCylinder(quadratic,radius,radius,0.6*height,32,32);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.6*height, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic,radius,3.5*radius,0.1*height,32,32);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glEndList();
}

void Lamp::drawLamp(){
	glCallList(lampList);
}