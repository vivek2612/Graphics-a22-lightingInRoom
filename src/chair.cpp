#include "chair.h"

Chair::Chair(float size,float legHeight, float legRadius){
	this->size=size;
	this->legHeight=legHeight;
	this->legRadius=legRadius;
}

void Chair::drawChair(){
	glPushMatrix();
		t.drawTable();
		glTranslatef(size+legRadius,0.4f,0.0);
		glRotatef(70,0.0,0.0,1.0);
		glTranslatef(size+legRadius,0.0,0.0);
		c.drawCuboid();

	glPopMatrix();
}


void Chair::createAllLists(){
	t.size = size;
	t.height = legHeight;
	t.legRadius = legRadius;

	c.breadth=size+legRadius;
	c.height=0.4f;

	t.createAllLists();
	c.createAllLists();
}