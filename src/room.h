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
private:
	GLuint wallList;
	void createWallList;
	
};

#endif