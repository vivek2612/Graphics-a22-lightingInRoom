#include "bezier.h"

Bezier::Bezier(vector<Point> v){
	controlPoints = v;
}

Bezier::Bezier(){

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

void Bezier::drawCurve(){
	float t=0.0;
	Point prevPoint = findCurvePoint(0.0);
	glBegin(GL_LINES);
	while(t<1.0){
		t+=0.01;
		Point nextPoint = findCurvePoint(t);
		    glVertex3f(prevPoint.x, prevPoint.y, prevPoint.z);
		    glVertex3f(nextPoint.x, nextPoint.y, nextPoint.z);
		prevPoint = nextPoint;
	}
	glEnd();
}