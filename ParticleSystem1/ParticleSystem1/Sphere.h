#pragma once
#include "Line.h"
#include "Plane.h"
class Sphere
{
	Point center;
	float radius;
public:
	Sphere();
	~Sphere();
	Sphere(Point center, float radius);
	//functions
	bool InsideorOut(vec3 p);
	float ComputeArea();
	float ComputeVolume();
	Point returnCenter();
	float returnRadius();
	float intersectionwithSphere(Point pAnt, Point pAct);
	Plane returnPlane(Point p);
};

