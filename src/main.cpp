
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

#define _USE_MATH_DEFINES


/* Global variables */
char title[] = "3D Shapes";
float degree = 0.0f;
float verticalDegree = 0.0f;
// Box boxObject;
float lidAngle=0.0;
float eyex=0.0f,eyey=0.0f;
float eyez=1.0f;
// Human humanObject;
int mode = -1;
/* Initialize OpenGL Graphics */
Cuboid cuboidObject(2.0,1.0);
Table tableObject(5.0,6.0,1.0f);
Chair chairObject(3.0,6.0,0.6);
float roomSize=35.0;
Room roomObject(roomSize);
Point clickedPoint;
vector<Point> controlPoints;
Bezier b;
vector<Point> curvePoints;
int i=0;
float zParam=0.0;
vector<Point> v;

void initGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClearDepth(1.0f);                   // Set background depth to farthest
  //glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
  //glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
  glShadeModel(GL_SMOOTH);   // Enable smooth shading
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

  GLfloat light_ambient[] =
    {1.0, 0.0, 1.0, 1.0};
    GLfloat light_diffuse[] =
    {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] =
    {1.0, 1.0, 1.0, 1.0};
/* light_position is NOT default value */
    GLfloat light_position[] =
    {roomSize,-roomSize,-roomSize, 1.0};
    // {0.0,0.0,0.0,1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);



  cuboidObject.createAllLists();
  tableObject.createAllLists();
  chairObject.createAllLists();
  roomObject.createAllLists();

  v.push_back(Point(0,0,0));
  v.push_back(Point(10.-5.0,0,0));
  v.push_back(Point(2.0,14.0,10));
  b.controlPoints=v;
  curvePoints=b.findCurve();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f); 
    glPointSize(50.0f);
    glBegin(GL_POINTS);
      glVertex3f(roomSize,-roomSize,-roomSize);
    glEnd();
    gluLookAt(eyex, eyey, eyez, 0.0f, -20.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
    glRotatef(degree, 0.0f, 1.0f, 0.0f);
    glRotatef(verticalDegree, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f); 
    glPointSize(50.0f);
    glBegin(GL_POINTS);
      glVertex3f(roomSize,-roomSize,-roomSize);
    glEnd();

    //glTranslatef(-5.0f,8.0,10.0);
    glPushMatrix();
      
      Texture tex;
      GLuint boxTexture;


      roomObject.drawRoom();
      glPushMatrix();
        glTranslatef(0.0,-2*roomSize/3,-roomSize/2.0);
        tableObject.drawTable();
        boxTexture = tex.loadBMP_custom("./images/wood2.bmp");
        glTranslatef(0.0,2.0,0.0);
        cuboidObject.drawCuboid();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(roomSize/2.0,-2*roomSize/3.0,0.0);
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
    // gluUnProject( winX, winY, 0, modelview, projection, viewport, &posX, &posY, &posZNear);
    // gluUnProject( winX, winY, 1, modelview, projection, viewport, &posX, &posY, &posZFar);
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    
    /*posZNear=10.0f;
    posZFar=-20.0f;
    posZ = (1- zParam)*posZNear + zParam*posZFar;*/
    // cout<<posZNear<<" "<<posZFar<<endl;
    cout<<posZ<<endl;
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
  case GLUT_KEY_LEFT : degree-= 5.0f;glutPostRedisplay();break;
  case GLUT_KEY_RIGHT : degree+=5.0f ;glutPostRedisplay();break;
  case GLUT_KEY_UP : eyez-=1.0f; glutPostRedisplay(); break;
  case GLUT_KEY_DOWN : eyez+=1.0f;glutPostRedisplay(); break;
  }
}

void keyboard(unsigned char key, int x, int y){
  switch(key){
    case 't':
    {
      zParam+=0.1;
      cout<<zParam<<":"<<endl;
      if(zParam>1.0) zParam=1.0;
      break;
    }
    case 'T':
    {
      zParam-=0.1;
      if(zParam<0.0) zParam=0.0;
      break;
    }
    case '1':
    {
      mode=1;
      glutPostRedisplay();
      break;
    }
    case 'n':
    {
      int len = curvePoints.size();
      if(len!=0){
        eyex=curvePoints[i%len].x;
        eyey=curvePoints[i%len].y;
        eyez=curvePoints[i%len].z;
      }
      glutPostRedisplay();
      i++;
      break;
    }

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