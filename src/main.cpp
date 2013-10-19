
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

#define _USE_MATH_DEFINES

/* Global variables */
char title[] = "3D Shapes";
float degree = 0.0f;
float verticalDegree = 0.0f;
// Box boxObject;
float lidAngle=0.0;
float eyex=0.0f,eyey=0.0f;
float eyez=30.0f;
// Human humanObject;
int mode = -1;
/* Initialize OpenGL Graphics */
Cuboid cuboidObject(3.0,3.0);
Table tableObject(5.0,6.0,1.0f);
Chair chairObject(3.0,6.0,0.6);
Room roomObject(10.0);

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

   vector<Point> v;
   v.push_back(Point(0.0,0.0, 0.0));
   v.push_back(Point(1.0,0.0, 0.0));
   v.push_back(Point(2.0,0.0, 0.0));
   Bezier b(v);
   Point p=b.findCurvePoint(0.75);
   cout<< p.x << " "<<p.y<<endl;

   cuboidObject.createAllLists();
   tableObject.createAllLists();
   chairObject.createAllLists();
   roomObject.createAllLists();
}
 
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   //glEnable(GL_TEXTURE_2D);
   //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
   
   glLoadIdentity();
   gluLookAt(eyex, eyey, eyez, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
   glRotatef(degree, 0.0f, 1.0f, 0.0f);
   glRotatef(verticalDegree, 0.0f, 0.0f, 1.0f);
   glColor3f(1.0f, 1.0f, 1.0f);   

   glTranslatef(-25.0f,-2.0,0.0);
   /*cuboidObject.drawCuboid();

   glTranslatef(10.0,0.0,-20.0f);
   tableObject.drawTable();

   glTranslatef(20.0f,-2.0,10.0);
   chairObject.drawChair();*/

   roomObject.drawRoom();
   //glDisable(GL_TEXTURE_2D);
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
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
   gluPerspective(60.0f, aspect, 0.1f, 100.0f);
}
 
void mouse(int button, int state, int x, int y){
    glutPostRedisplay();
}

void inputKey(int key, int x, int y) 
{
  switch (key) {
  case GLUT_KEY_LEFT : degree-= 5.0f;glutPostRedisplay();break;
  case GLUT_KEY_RIGHT : degree+=5.0f ;glutPostRedisplay();break;
  case GLUT_KEY_UP : eyez-=1.0f; glutPostRedisplay(); break;
  case GLUT_KEY_DOWN : eyez+=1.0f;glutPostRedisplay(); break;
  }
}

void keyboard(unsigned char key, int x, int y){
  switch(key){
    case 27:
    {
         exit(0);
         break;
    }
    case 'w':
    {
         verticalDegree-=3.0f;
         glutPostRedisplay();
         break;
      }
    case 's':
    {
       verticalDegree+=3.0f;
       glutPostRedisplay();
       break;
    }
    case '=':
    {
      cuboidObject.lidAngle+=1.0f;
      glutPostRedisplay();
       break;
    }
    case '-':
    {
      cuboidObject.lidAngle-=1.0f;
      glutPostRedisplay();
      break;
    }
    case 'd':
    {
      roomObject.doorAngle+=1.0f;
      glutPostRedisplay();
      break;
    }
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