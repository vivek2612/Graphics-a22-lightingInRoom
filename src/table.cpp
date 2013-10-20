#include "table.h"

float tableThickness=0.4f;

Table::Table(){
	Table(0.0,0.0,0.0);
}

Table::Table(float size,float height,float legRadius=1.0){
	this->size=size;
	this->height=height;
	this->legRadius=legRadius;
}

void Table::createSurfaceList(){
	surface.height=tableThickness;
	surface.breadth=size+legRadius;
	surface.createAllLists();
}

void Table::createLegList(){
	legList=glGenLists (1);
	glNewList(legList, GL_COMPILE);
	glPushMatrix();
		glColor3f(1.0,0.3,0.6);
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluQuadricNormals( quadratic, GL_TRUE );
		gluCylinder(quadratic,legRadius,legRadius-0.2,height,32,32);
	glPopMatrix();
	glEndList();
}

void Table::createAllLists(){
	createLegList();
	createSurfaceList();
}

void Table::drawTable(){
	GLuint t;
	Texture tex;
	glPushMatrix();
		t=tex.loadBMP_custom("./images/leg.bmp");
		surface.drawCuboid();
		glPushMatrix();
			glTranslatef(size,0.0,size);
			glCallList(legList);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(size,0.0,-size);
			glCallList(legList);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-size,0.0,size);
			glCallList(legList);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-size,0.0,-size);
			glCallList(legList);
		glPopMatrix();
	glPopMatrix();
}

