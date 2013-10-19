#ifndef CUB_H
#define CUB_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Cuboid{
public:
	void createAllLists();
	void createLateralList();
	void createTopBottomList();
	float height;
	float breadth; 
	Cuboid(float breadth,float height); 
	float lidAngle;
	void drawCuboid();
	Cuboid();
private:
	GLuint lateralList;
	GLuint topBottomList;
};

#endif