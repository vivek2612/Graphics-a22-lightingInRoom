#include "room.h"

Room::Room(){
	Room(0.0);
}

Room::Room(float size){
	this->size = size;
	doorAngle = 0.0;
}

void Room::createWallList(){
	wallList=glGenLists(1);
	glNewList(wallList, GL_COMPILE);
		glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glTexCoord2f(0.0, 0.0);glVertex3f(size,-size,size);
			glTexCoord2f(0.0, 1.0);glVertex3f(size,size,size);
			glTexCoord2f(1.0, 1.0);glVertex3f(-size,size,size);
			glTexCoord2f(1.0, 0.0);glVertex3f(-size,-size,size);
		glEnd();
	glEndList();
}

void Room::createDoorList(){
	doorList=glGenLists(1);
	glNewList(doorList, GL_COMPILE);
		glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glTexCoord2f(0.0, 0.0);glVertex3f(1.0*size/3.0,-(size/2.0),size);
			glTexCoord2f(0.0, 1.0);glVertex3f(1.0*size/3.0,size/2.0,size);
			glTexCoord2f(1.0, 1.0);glVertex3f(-1.0*size/3.0,size/2.0,size);
			glTexCoord2f(1.0, 0.0);glVertex3f(-1.0*size/3.0,-(size/2.0),size);
		glEnd();
	glEndList();
}

void Room::drawRoom(){
	glColor3f(1.0f, 0.0f, 0.0f);
	Texture tex;
	GLuint t;
	glPushMatrix();
		
		//firstly, draw the front face with a door

		// The door
		t = tex.loadBMP_custom("./images/door.bmp");
		glPushMatrix();
			glColor3f(0.6f, 0.7f, 0.9f);
			glTranslatef(-2.0*size/3.0,-(size/2.0),0.0);
			glTranslatef(-1.0*size/3.0,0.0,size);
			glRotatef(doorAngle,0.0,-1.0,0.0);
			glTranslatef(1.0*size/3.0,0.0,-size);
			glCallList(doorList);
		glPopMatrix();

		t = tex.loadBMP_custom("./images/wall5.bmp");
		// The portion of front face : aside the door
		glPushMatrix();
			glTranslatef(1.0*size/3.0,0.0,0.0);
			glBegin(GL_QUADS);
				glNormal3f(0,0,-1);
				glTexCoord2f(0.0, 0.0);glVertex3f(2.0*size/3.0,-size,size);
				glTexCoord2f(0.0, 1.0);glVertex3f(2.0*size/3.0,size,size);
				glTexCoord2f(1.0, 1.0);glVertex3f(-2.0*size/3.0,size,size);
				glTexCoord2f(1.0, 0.0);glVertex3f(-2.0*size/3.0,-size,size);
			glEnd();
		glPopMatrix();

		// The portion of front face above the door
		glPushMatrix();
			glTranslatef(-2.0*size/3.0,size/2.0,0.0);
			glCallList(doorList);
		glPopMatrix();


		glPushMatrix();
			glColor3f(0.6f, 1.0f, 0.9f);
			glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
			glCallList(wallList);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.4f, 1.0f, 1.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glCallList(wallList);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.0f, 1.0f, 1.0f);
			glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
			glCallList(wallList);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.1f, 1.0f, 0.1f);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glCallList(wallList);
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glCallList(wallList);
		glPopMatrix();

	glPopMatrix();
}

void Room::createAllLists(){
	
	createDoorList();
	createWallList();
}