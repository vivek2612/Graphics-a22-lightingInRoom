
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glut.h>
#include <cstdio>
// #include "box.h"
//#include "human.h"
#include "point.h"
#include "bezier.h"
#include "cuboid.h"
#include "table.h"
#include "chair.h"
#include "room.h"
#include "tex.h"
#include "vector"
#include "human.h"
#include "lamp.h"

#define _USE_MATH_DEFINES


/* Global variables */
char title[] = "Room and Music Box";
float lidAngle=0.0;
float eyex=-20.0;
float eyez=30.0f;
float eyey=-10.0f;

Lamp lampObject(30.0f, 1.5f);
Human humanObject;
int mode = -1;
/* Initialize OpenGL Graphics */
Cuboid cuboidObject(4.0,5.0);
Table tableObject(9.0,7.0,1.0f);
Chair chairObject(5.0,7.0,0.6);
float roomSize=50.0;
Room roomObject(roomSize);
Point clickedPoint;
vector<Point> controlPoints;
Bezier b;
vector<Point> curvePoints;
int i=0;
float zParam=0.0;
vector<Point> v;
bool light0,light1,light2;

void printInstructions(){
	cout<<endl<<
	"\tb : Click bezier points"<<endl<<
	"\tn : Animation"<<endl<<
	"\t= : Open the Lid"<<endl<<
	"\t- : Close the lid"<<endl<<
	"\td : Open the door"<<endl<<
	"\t[ : Light 0 on/off" <<endl<<
		"\t] : Light 1 on/off"<<endl<<
"\t\t\n\tMoveMent\n"<<
"\t<-: Rotate clockwise in x-z plane\n"<<
"\t->: Rotate anti-clockwise in x-z plane\n"
"\tup: Move in +Z-dir\n"<<
"\tdown: Move in -Z-dir\n"<<
"\t/ : move camera in +y"<<endl;

}


void initGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClearDepth(1.0f);                   // Set background depth to farthest
  glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
  glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective correction
  glEnable(GL_LIGHTING);

  cuboidObject.createAllLists();
  tableObject.createAllLists();
  chairObject.createAllLists();
  roomObject.createAllLists();
  humanObject.createAllLists();
  lampObject.createAllLists();

  // v.push_back(Point(0,0,0));
  v.push_back(Point(-20,0,-20));
  v.push_back(Point(-10.0,5,20.0));
  v.push_back(Point(-10,10,30));
  v.push_back(Point(10,10,30));
  v.push_back(Point(30,10,35));
  v.push_back(Point(0,0,0));
  // v.push_back(Point(2.0,14.0,10));
  b.controlPoints=v;
  curvePoints=b.findCurve();
  light0=true;light1=true;
  light2=true;
  printInstructions();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, 0.0f, -6*roomSize/7,0.0, 0.0f, 1.0f, 0.0f);

    GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
    // GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};  
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light0_position[] ={roomSize/2.0,-roomSize/2.0,-roomSize/2.0,1.0}; 
    GLfloat light1_position[] ={0.0,-roomSize/2.0,roomSize/2.0,1.0}; 
    GLfloat light2_position[] ={0.0,-6.0*roomSize/7.0 + 21.0f ,-20.0,1.0}; 
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(20.0f); 
    glBegin(GL_POINTS);
    	glVertex3f(0.0,-6.0*roomSize/7.0 + 21.0f ,-20.0);
    glEnd();


    if(light0){
    	glEnable(GL_LIGHT0);
    	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    }
    else{
    	glDisable(GL_LIGHT0);
    }

    if(light1){
    	glEnable(GL_LIGHT1);
    	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    }
    else{
    	glDisable(GL_LIGHT1);
    }

    if(light2){
    	glEnable(GL_LIGHT2);
    	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    }
    else{
    	glDisable(GL_LIGHT2);
    }

    Texture tex;
    GLuint boxTexture;
    glPushMatrix();
    roomObject.drawRoom();
    // Drawing Lamp

    glPushMatrix();
    	glTranslatef(0.0,-6.0*roomSize/7.0 + 14.5f ,-20.0);
    	lampObject.drawLamp();
    glPopMatrix();

    //Drawing Table
    glPushMatrix();
    glTranslatef(0.0,-6*roomSize/7  ,0.0);
    tableObject.drawTable();


    glTranslatef(0.0,4.8,0.0);
    glPushMatrix();
    glScalef(0.6,0.6,0.6);
    glTranslatef(0.0,-0.2f,0.0);
    humanObject.drawHuman();        
    glPopMatrix();
    boxTexture = tex.loadBMP_custom("./images/wood2.bmp");
    cuboidObject.drawCuboid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(roomSize/2.0,-6.0*roomSize/7.0,0.0);
    chairObject.drawChair();

    glPopMatrix();
    glPopMatrix();
    b.drawCurve(curvePoints);
    


    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

// source : http://nehe.gamedev.net/article/using_gluunproject/16013/
Point GetOGLPos(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZNear,posZFar,posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv(GL_VIEWPORT,viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	return Point(posX, posY, posZ);
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(60.0f, aspect, 0.1f, 1000.0f);
}

void mouse(int button, int state, int x, int y){
	if (state == GLUT_DOWN){
		if(mode==1){
			if(button == GLUT_LEFT_BUTTON){
				if(clickedPoint.x==-1 && clickedPoint.y==-1 && clickedPoint.z==-1){
					controlPoints.clear();
					curvePoints.clear();
					zParam=0.0;
				}
				clickedPoint= GetOGLPos(x,y);
				controlPoints.push_back(clickedPoint);
			}
			else if(button == GLUT_RIGHT_BUTTON){
				mode=-1;
				i=0;
				clickedPoint = Point(-1,-1,-1);
				b.controlPoints=controlPoints;
				curvePoints = b.findCurve();
			}
		}
	}
	glutPostRedisplay();
}

void inputKey(int key, int x, int y) 
{
	switch (key) {
		case GLUT_KEY_LEFT : {
			float degree=-0.1f;
			eyex = eyex*cos(degree)-eyez*sin(degree);
			eyez = eyex*sin(degree)+eyez*cos(degree);
			glutPostRedisplay();break;
		}
		case GLUT_KEY_RIGHT :{
			float degree= 0.1f;
			eyex = eyex*cos(degree)-eyez*sin(degree);
			eyez = eyex*sin(degree)+eyez*cos(degree);
			glutPostRedisplay();break;
		} 
		case GLUT_KEY_UP : eyez-=1.0f; glutPostRedisplay(); break;
		case GLUT_KEY_DOWN : eyez+=1.0f;glutPostRedisplay(); break;
	}
}

void animation(int j){
	int len = curvePoints.size();
	if (j<len){
		if(len!=0){
			eyex=curvePoints[j%len].x;
			eyey=curvePoints[j%len].y;
			eyez=curvePoints[j%len].z;
		}
		glutPostRedisplay();
		j++;
		glutTimerFunc(10,animation,j);
	}

}

void keyboard(unsigned char key, int x, int y){
	switch(key){  
		case 'b':
		{
			mode=1;
			glutPostRedisplay();
			break;
		}
		case 'n':
		{
			glutTimerFunc(10,animation,0);
			break;
		}

		case 27:
		{
			exit(0);
			break;
		}
		case '=':
		{
			if(cuboidObject.lidAngle < 221.0f){
				cuboidObject.lidAngle+=2.0f;
				humanObject.hipTranslatey+=0.15f;
			}
			glutPostRedisplay();
			break;
		}
		case '-':
		{
			if(cuboidObject.lidAngle > 0.0f){
				cuboidObject.lidAngle-=2.0f;
				humanObject.hipTranslatey-=0.15f;
			}
			glutPostRedisplay();
			break;
		}
		case 'd':
		{
			roomObject.doorAngle-=1.0f;
			glutPostRedisplay();
			break;
		}
		case 'D':
		{
			roomObject.doorAngle+=1.0f;
			glutPostRedisplay();
			break;
		}
		case '/':
		{
			eyey+=1.0f;
			glutPostRedisplay();
			break;
		}
		case '?':
		{
			eyey-=1.0f;
			glutPostRedisplay();
			break;
		}
		case '[':
		{
			light0=(!light0);
			glutPostRedisplay();
			break;
		}
		case ']':
		{
			light1=(!light1);
			glutPostRedisplay();
			break;
		}
		case 'l':
		{
			light2=(!light2);
			glutPostRedisplay();
			break;
		}
	
		case 'r':{
			humanObject.reset();
			glutPostRedisplay();
		}
		case '0':{
			mode = 0;
			glutPostRedisplay();
			break;
		}
		case '1':{
			mode = 1;
			glutPostRedisplay();
			break;
		}
		case '2':{
			mode = 2;
			glutPostRedisplay();
			break;
		}
		case '3':{
			mode = 3;
			glutPostRedisplay();
			break;
		}
		case '4':{
			mode = 4;
			glutPostRedisplay();
			break;
		}
		case '5':{
			mode = 5;
			glutPostRedisplay();
			break;
		}
		case '6':{
			mode = 6;
			glutPostRedisplay();
			break;
		}
		case '7':{
			mode = 7;
			glutPostRedisplay();
			break;
		}
		case '8':{
			mode = 8;
			glutPostRedisplay();
			break;
		}
		case 'p':{
			mode = 9;
			glutPostRedisplay();
			break;
		}
		case 'o':{
			mode = 10;
			glutPostRedisplay();
			break;
		}
		case 'i':{
			mode = 11;
			glutPostRedisplay();
			break;
		}
		case 'u':{
			mode = 12;
			glutPostRedisplay();
			break;
		}
		case 'z':{
			if(mode>=0){
				if(mode == 0){
		          //Hip Translation
					humanObject.hipTranslatez += 0.1f;
				}
				else if (mode == 1){
		          // Head Rotation
					if(humanObject.headz <= 45.0f)
						humanObject.headz += 2.0f;
				}
				else if (mode == 2){
		          // Neck Rotation
					if(humanObject.neckz <= 25.0f)
						humanObject.neckz += 2.0f;
				}
				else if (mode == 3){
		          // Torso Rotation
					if(humanObject.torsoz <= 25.0f)
						humanObject.torsoz += 2.0f;
				}
				else if (mode == 4){
					if((((int)humanObject.leftUpperArmx)%360 <= 20.0f || ((int)humanObject.leftUpperArmx)%360 >= 340.0f) && humanObject.leftUpperArmy >= 30.0f){

						if(humanObject.leftUpperArmz < 0.0f && humanObject.leftUpperArmz < 4.0/7.0*humanObject.leftLowerArmx ){
							humanObject.leftUpperArmz+=2.0f;
						}
					}else{
						if(humanObject.leftUpperArmz < 0.0f)
							humanObject.leftUpperArmz += 2.0f;
					}
				}
				else if (mode == 6){
					if(humanObject.rightUpperArmz<180.0f)
						humanObject.rightUpperArmz+=2.0f;
				}
				else if(mode == 8){
					if(humanObject.hipz < 45.0f)
						humanObject.hipz += 2.0f;
				}
				else if(mode == 9){
					if(humanObject.leftUpperLegz < 0.0f)
						humanObject.leftUpperLegz += 2.0f;
				}
				else if(mode == 11){
					if(humanObject.rightUpperLegz < 45.0f)
						humanObject.rightUpperLegz += 2.0f;
				}
			}
			glutPostRedisplay();
			break;
		}
		case 'Z':{
			if(mode>=0){
				if(mode == 0){
		          //Hip Translation
					humanObject.hipTranslatez -= 0.1f;
				}
				else if (mode == 1){
		          // Head Rotation
					if(humanObject.headz >= -45.0f)
						humanObject.headz -= 2.0f;
				}
				else if (mode == 2){
		          // Neck Rotation
					if(humanObject.neckz >= -25.0f)
						humanObject.neckz -= 2.0f;
				}
				else if (mode == 3){
		          // Neck Rotation
					if(humanObject.torsoz >= -25.0f)
						humanObject.torsoz -= 2.0f;
				}
				else if(mode == 4){
					if(humanObject.leftUpperArmz >= -180.0f)
						humanObject.leftUpperArmz -= 2.0f;
				}
				else if(mode == 6){
					if((((int)humanObject.rightLowerArmx)%360 < 20.0f || ((int)humanObject.rightLowerArmx)%360 > 340.0f ) && humanObject.rightUpperArmy < -30.0f){
						if(humanObject.rightUpperArmz > 0.0f && humanObject.rightUpperArmz > fabs(4.0/7.0*humanObject.rightLowerArmx)){
							humanObject.rightUpperArmz -= 2.0f;
						}
					}
					else{
						if(humanObject.rightUpperArmz > 0.0f){
							humanObject.rightUpperArmz -= 2.0f;
						}
					}
				}
				else if(mode == 8){
					if(humanObject.hipz > -45.0f)
						humanObject.hipz -= 2.0f;
				}
				else if(mode == 9){
					if(humanObject.leftUpperLegz > -45.0f)
						humanObject.leftUpperLegz -= 2.0f;
				}
				else if(mode == 11){
					if(humanObject.rightUpperLegz > 0.0f)
						humanObject.rightUpperLegz -= 2.0f;
				}
			}
			glutPostRedisplay();
			break;
		}
		case 'x':{
			if(mode >= 0){
				if(mode == 0){
		            //Hip Translation
					humanObject.hipTranslatex += 0.1f;
				}
				else if(mode == 1){
		            // Head Rotation
					if(humanObject.headx<=45.0f)
						humanObject.headx+=2.0f;
				}
				else if(mode == 2){
		            // Neck Rotation
					if(humanObject.neckx<=25.0f)
						humanObject.neckx+=2.0f;
				}
				else if(mode == 3){
		            // Neck Rotation
					if(humanObject.torsox<=25.0f)
						humanObject.torsox+=2.0f;
				}
				else if(mode == 4){
		            // Upper Arm Rotation
					humanObject.leftUpperArmx+=2.0f;
				}
				else if(mode == 5){
					if(humanObject.leftLowerArmx <= 0.0f)
						humanObject.leftLowerArmx +=2.0f;
				}
				else if(mode == 6){
		            // Upper Arm Rotation
					humanObject.rightUpperArmx+=2.0f;
				}
				else if(mode == 7){
					if(humanObject.rightLowerArmx <= 0.0f)
						humanObject.rightLowerArmx +=2.0f;
				}
				else if(mode == 8){
					if(humanObject.hipx < 45.0f)
						humanObject.hipx += 2.0f;
				}
				else if(mode == 9){
					if(humanObject.leftUpperLegx < 60.0f)
						humanObject.leftUpperLegx += 2.0f;
				}
				else if(mode == 10){
					if(humanObject.leftLowerLegx < 120.0f)
						humanObject.leftLowerLegx += 2.0f;
				}
				else if(mode == 11){
					if(humanObject.rightUpperLegx < 60.0f)
						humanObject.rightUpperLegx += 2.0f;
				}
				else if(mode == 12){
					if(humanObject.rightLowerLegx < 120.0f)
						humanObject.rightLowerLegx += 2.0f;
				}
			}
			glutPostRedisplay();
			break;
		}
		case 'X':{
			if(mode >= 0){
				if(mode == 0){
		            //Hip Translation
					humanObject.hipTranslatex -= 0.1f;
				}
				else if(mode == 1){
		            // Head Rotation
					if(humanObject.headx>=-45.0f)
						humanObject.headx-=2.0f;
				}
				else if(mode == 2){
		            // Head Rotation
					if(humanObject.neckx>=-25.0f)
						humanObject.neckx-=2.0f;
				}
				else if(mode == 3){
		            // Head Rotation
					if(humanObject.torsox>=-25.0f)
						humanObject.torsox-=2.0f;
				}
				else if(mode == 4){
		            //Upper Arm Rotation
					humanObject.leftUpperArmx-=2.0f;
				}
				else if(mode == 5){
					if((((int)humanObject.leftUpperArmx)%360 <= 20.0f || ((int)humanObject.leftUpperArmx)%360 >= 340.0f) && humanObject.leftUpperArmy >= 30.0f){
						if(humanObject.leftUpperArmz > -90.0f && humanObject.leftLowerArmx > -135.0f && humanObject.leftLowerArmx > 7.0/4.0*humanObject.leftUpperArmz){
							humanObject.leftLowerArmx -= 2.0f;
						}
						else if(humanObject.leftUpperArmz < -90.0f){
							if(humanObject.leftLowerArmx > -135.0f){
								humanObject.leftLowerArmx -= 2.0f;
							}
						}
					}
					else{
						if(humanObject.leftLowerArmx > -135.0f){
							humanObject.leftLowerArmx -= 2.0f;
						}
					}
				}
				else if(mode == 6){
		            //Upper Arm Rotation
					humanObject.rightUpperArmx-=2.0f;
				}
				else if(mode == 7){
					if((((int)humanObject.rightUpperArmx)%360 <= 20.0f || ((int)humanObject.rightUpperArmx)%360 >= 340.0f) && humanObject.rightUpperArmy < -30.0f){
						if(humanObject.rightUpperArmz < 90.0f && humanObject.rightLowerArmx > -135.0f && humanObject.rightLowerArmx > -1.0*7.0/4.0*humanObject.rightUpperArmz){
							humanObject.rightLowerArmx -= 2.0f;
						}
						else if(humanObject.rightUpperArmz > 90.0f){
							if(humanObject.rightLowerArmx > -135.0f){
								humanObject.rightLowerArmx -= 2.0f;
							}
						}
					}
					else{
						if(humanObject.rightLowerArmx > -135.0f){
							humanObject.rightLowerArmx -= 2.0f;
						}
					}
				}
				else if(mode == 8){
					if(humanObject.hipx > -45.0f)
						humanObject.hipx -= 2.0f;         
				}
				else if(mode == 9){
					if(humanObject.leftUpperLegx > -90.0f)
						humanObject.leftUpperLegx -= 2.0f;
				}
				else if(mode == 10){
					if(humanObject.leftLowerLegx > 0.0f)
						humanObject.leftLowerLegx -= 2.0f;
				}
				else if(mode == 11){
					if(humanObject.rightUpperLegx > -90.0f)
						humanObject.rightUpperLegx -= 2.0f;
				}
				else if(mode == 12){
					if(humanObject.rightLowerLegx > 0.0f)
						humanObject.rightLowerLegx -= 2.0f;
				}
			}
			glutPostRedisplay();
			break;
		}
		case 'c':{
			if(mode >= 0){
				if(mode == 0){
		            //Hip Translation
					humanObject.hipTranslatey += 0.1f;
				}
				else if(mode == 1){
		            // Head Rotation
					if(humanObject.heady<=60.0f)
						humanObject.heady+=2.0f;
				}
				else if(mode == 2){
		            // Head Rotation
					if(humanObject.necky<=45.0f)
						humanObject.necky+=2.0f;
				}
				else if(mode == 3){
		            // Head Rotation
					if(humanObject.torsoy<=45.0f)
						humanObject.torsoy+=2.0f;
				}
				else if(mode == 4){
		            // Left Upper Arm Rotation
					if(((int)humanObject.rightUpperArmx )%360<= 20.0f || ((int)humanObject.rightUpperArmx)%360 >= 340.0f){
						if(humanObject.leftUpperArmz > 4.0/7.0*humanObject.leftLowerArmx){
							if(humanObject.leftUpperArmy < 30.0f)
								humanObject.leftUpperArmy += 2.0f;
						}else{
							if(humanObject.leftUpperArmy < 90.0f)
								humanObject.leftUpperArmy += 2.0f;
						}
					}
					else{
						if(humanObject.leftUpperArmy < 90.0f)
							humanObject.leftUpperArmy += 2.0f;
					}
				}
				else if(mode == 6){
		            // Head Rotation
					if(humanObject.rightUpperArmy<90.0f)
						humanObject.rightUpperArmy+=2.0f;
				}
				else if(mode == 8){
					if(humanObject.hipy < 30.0f)
						humanObject.hipy += 2.0f;
				}
				else if(mode == 9){
					if(humanObject.leftUpperLegy < 30.0f)
						humanObject.leftUpperLegy += 2.0f;
				}
				else if(mode == 11){
					if(humanObject.rightUpperLegy < 30.0f)
						humanObject.rightUpperLegy += 2.0f;
				}
			}
			glutPostRedisplay();
			break;  
		}
		case 'C':{
			if(mode >= 0){
				if(mode == 0){
		            //Hip Translation
					humanObject.hipTranslatey -= 0.1f;
				}
				else if(mode == 1){
		            // Head Rotation
					if(humanObject.heady>=-60.0f)
						humanObject.heady-=2.0f;
				}
				else if(mode == 2){
		            // Head Rotation
					if(humanObject.necky>=-45.0f)
						humanObject.necky-=2.0f;
				}
				else if(mode == 3){
		            // Head Rotation
					if(humanObject.torsoy>=-45.0f)
						humanObject.torsoy-=2.0f;
				}
				else if(mode == 4){
		            // Head Rotation
					if(humanObject.leftUpperArmy>=-90.0f)
						humanObject.leftUpperArmy-=2.0f;
				}
				else if(mode == 6){
		            // Right Upper Arm Rotation
					if(((int)humanObject.rightUpperArmx)%360 <= 20.0f || ((int)humanObject.rightUpperArmx)%360 >= 340.0f){
						if(humanObject.rightUpperArmz < fabs(4.0/7.0*humanObject.rightLowerArmx)){
							if(humanObject.rightUpperArmy > -30.0f){
								humanObject.rightUpperArmy -= 2.0f;
							}
						}
						else  if(humanObject.rightUpperArmy > -90.0f){
							humanObject.rightUpperArmy -= 2.0f;
						}
						else{
							if(humanObject.rightUpperArmy > -90.0f){
								humanObject.rightUpperArmy -= 2.0f;
							}
						}
					}
				}
				else if(mode == 8){
					if(humanObject.hipy > -30.0f)
						humanObject.hipy -= 2.0f;
				}
				else if(mode == 9){
					if(humanObject.leftUpperLegy > -30.0f)
						humanObject.leftUpperLegy -= 2.0f;
				}
				else if(mode == 11){
					if(humanObject.rightUpperLegy > -30.0f)
						humanObject.rightUpperLegy -= 2.0f;
				}
			}
			glutPostRedisplay();
			break;  
		}
		//
		default:
		{

		} 
	}
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   glutKeyboardFunc( keyboard );
   glutSpecialFunc(inputKey);
   glutMouseFunc( mouse );
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}