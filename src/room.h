#ifndef ROOM_H
#define ROOM_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Room{
public:
	void createAllLists();
	float doorAngle;
	void drawRoom();
	Room();
	Room(float size);
private:
	float size;
	GLuint wallList;
	GLuint doorList;
	void createWallList();	
	void createDoorList();
};

#endif