#include "bezier.h"

Bezier::Bezier(vector<Point> v){
	controlPoints = v;
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