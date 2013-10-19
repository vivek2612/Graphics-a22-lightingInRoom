#ifndef CHAIR_H
#define CHAIR_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "cuboid.h"

using namespace std;

class Chair{
public:
	float size;
	float legHeight;
	float legRadius;
	void createAllLists();
	Chair(float size,float legHeight, float legRadius); 
	void drawChair();
private:
	Table t;  // lower portion of chair is of table
	Cuboid c; // upper portion is of cuboid
};

#endif