#include "lamp.h"


Lamp::Lamp(float height, float radius){
	this->height = height;
	this->radius = radius;
}

void Lamp::createHeadList(){
	headList=glGenLists (1);
	glNewList(headList, GL_COMPILE);
		GLUquadricObj *quadratic;
		gluQuadricOrientation(quadratic, GLU_OUTSIDE)
		quadratic = gluNewQuadric();
		gluQuadricTexture(quadratic,1);
		gluCylinder(quadratic,3*radius,1.5*radius,0.3*height,32,32);
	glEndList();
}

void Lamp::createNeckList(){
	neckList=glGenLists (1);
	glNewList(neckList, GL_COMPILE);
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		gluDisk(quadratic,0.0f,radius,32,32);
		gluQuadricTexture(quadratic,1);
		gluCylinder(quadratic,radius,radius,0.6*height,32,32);
	glEndList();
}

void Lamp::createBaseList(){
	baseList=glGenLists (1);
	glNewList(baseList, GL_COMPILE);
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		gluQuadricTexture(quadratic,1);
		gluCylinder(quadratic,radius,3.5*radius,0.1*height,32,32);
	glEndList();
}



void Lamp::drawLamp(){
	glPushMatrix();
		Texture tex;
		GLuint t;
		t= tex.loadBMP_custom("./images/lampBase.bmp");   
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glCallList(headList);

		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		t= tex.loadBMP_custom("./images/lampNeck.bmp");   
		glCallList(neckList);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.6*height, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		t = tex.loadBMP_custom("./images/lampBase.bmp");
		glCallList(baseList);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Lamp::createAllLists(){
	createHeadList();
	createNeckList();
	createBaseList();
}