#include "cuboid.h"

Cuboid::Cuboid(){
	Cuboid(0.0,0.0);
}

Cuboid::Cuboid(float breadth,float height){
	this->height=height;
	this->breadth=breadth;
	lidAngle = 0.0;
}

void Cuboid::createAllLists(){
	createLateralList();
	createTopBottomList();
}

void Cuboid::createLateralList(){
	lateralList=glGenLists(1);
	glNewList(lateralList, GL_COMPILE);
		glBegin(GL_QUADS);
			glNormal3f(0,0,1);
			glTexCoord2f(0.0, 0.0);glVertex3f(breadth,-height,breadth);
			glTexCoord2f(0.0, 1.0);glVertex3f(breadth,height,breadth);
			glTexCoord2f(1.0, 1.0);glVertex3f(-breadth,height,breadth);
			glTexCoord2f(1.0, 0.0);glVertex3f(-breadth,-height,breadth);
		glEnd();
	glEndList();
}

void Cuboid::createTopBottomList(){   	
	topBottomList=glGenLists (1);
	glNewList(topBottomList, GL_COMPILE);
		glBegin(GL_QUADS);
			glNormal3f(0,0,1);
			glTexCoord2f(0.0, 0.0);glVertex3f( breadth,-breadth,breadth);
		    glTexCoord2f(0.0, 1.0);glVertex3f( breadth, breadth,breadth);
		    glTexCoord2f(1.0, 1.0);glVertex3f(-breadth, breadth,breadth);
		    glTexCoord2f(1.0, 0.0);glVertex3f(-breadth, -breadth,breadth);        
		glEnd();
	glEndList();
}

void Cuboid::drawCuboid(){
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glCallList(lateralList);
		glPushMatrix();
			glColor3f(0.6f, 1.0f, 0.9f);
			glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
			glCallList(lateralList);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.4f, 1.0f, 1.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glCallList(lateralList);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.0f, 1.0f, 1.0f);
			glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
			glCallList(lateralList);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.1f, 1.0f, 0.1f);
			glTranslatef(0.0,0.09f*(lidAngle/2.0),0.0);
			glTranslatef(0.0,-(height-breadth),0.0);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glCallList(topBottomList);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0,height-breadth,0.0);
			glTranslatef(-breadth,breadth,0.0);
			glRotatef(lidAngle,0.0,0.0,1.0);
			glTranslatef(breadth,-breadth,0.0);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glCallList(topBottomList);
		glPopMatrix();
	glPopMatrix();	
}
