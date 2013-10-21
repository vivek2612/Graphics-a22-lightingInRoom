#ifndef LAMP_H
#define LAMP_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Lamp{
public:
	float height;
	float radius;
	void createAllLists();
	Lamp(float height,float radius); 
	void drawLamp();
private:
	GLuint lampList;
};

#endif