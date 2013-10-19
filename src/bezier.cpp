#include "bezier.h"

Bezier::Bezier(vector<Point> v){
	controlPoints = v;
}

Bezier::Bezier(){
	Point p(0,0,0);
	controlPoints =  vector<Point>(0,p);
}
// finds the corresponding point on the curve using de-castlo algorithm
Point Bezier::findCurvePoint(float t){
	return findCurvePointHelper(t, controlPoints, controlPoints.size());
} 

Point Bezier::findCurvePointHelper(float t, vector<Point> newControlPoints, int length){
	if (length==1) return newControlPoints[0];
	for ( int i=0; i<length-1; i++){
		float newx = newControlPoints[i].x*(1-t) + newControlPoints[i+1].x*t;
		float newy = newControlPoints[i].y*(1-t) + newControlPoints[i+1].y*t;
		float newz = newControlPoints[i].z*(1-t) + newControlPoints[i+1].z*t;
		Point p(newx, newy, newz);
		newControlPoints[i]=p;
	}
	length--;
	return findCurvePointHelper(t, newControlPoints, length);
}

vector<Point> Bezier::findCurve(){
	float t=0.0;
	vector<Point> curvePoints;
	Point prevPoint = findCurvePoint(0.0);
	curvePoints.push_back(prevPoint);
	
	while(t<1.0){
		t+=0.01;
		Point nextPoint = findCurvePoint(t);
		curvePoints.push_back(nextPoint);
		prevPoint = nextPoint;
	}
	return curvePoints;
}

void Bezier::drawCurve(vector<Point> points){
	if(points.size()==0) return;
	glBegin(GL_LINES);
	for(int i=0;i<points.size()-1;i++){
		glVertex3f(points[i].x, points[i].y, points[i].z);
		glVertex3f(points[i+1].x, points[i+1].y, points[i+1].z);
	}
	glEnd();
}