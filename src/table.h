#ifndef TAB_H
#define TAB_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "cuboid.h"

using namespace std;

class Table{
public:
	float size;
	float height;
	float legRadius;
	void createAllLists();
	Table(float size,float height,float legRadius); 
	Table();
	void drawTable();
private:
	GLuint legList;
	Cuboid surface;
	void createLegList();
	void createSurfaceList();
};

#endif