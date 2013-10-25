#ifndef ALMIRAH_H
#define ALMIRAH_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "cuboid.h"
#include "tex.h"

using namespace std;

class Almirah{
public:
	Almirah(float xScale, float yScale, float zScale);
	void createAllLists();
	void drawAlmirah(float xTranslate, float yTranslate, float zTranslate);
private:
	float xScale;
	float yScale;
	float zScale;
	Cuboid baseCubes;
	Cuboid compartment;
};

#endif
