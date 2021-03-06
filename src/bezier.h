#ifndef BEZ_H
#define BEZ_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "point.h"
#include "vector"
using namespace std;


class Bezier{
public:
	Bezier(vector<Point> v);
	vector<Point> controlPoints;
	void drawCurve(vector<Point> v);
	vector<Point> findCurve();
	Bezier();
private:
	Point findCurvePointHelper(float t, 
	vector<Point> newControlPoints, int length);
	Point findCurvePoint(float t);  // t = parameter
};

#endif