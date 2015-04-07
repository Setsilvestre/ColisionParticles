#include "Sphere.h"


Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}
Sphere::Sphere(Point center, float radius){
	this->center = center;
	this->radius = radius;
}
//functions
bool Sphere::InsideorOut(vec3 p){
	cout << length(p - center.coord)<<endl;
	if (length(p - center.coord) > radius){
		return false;
	}
	else if (length(p - center.coord) <= radius){
		return true;
	}
}
float Sphere::ComputeArea(){
	
	return  4 * M_PI*radius*radius;
}
float Sphere::ComputeVolume(){
	return (4 / 3)*M_PI*radius*radius*radius;
}

Point Sphere::returnCenter(){
	return center;
}

float Sphere::returnRadius(){
	return radius;
}

float Sphere::intersectionwithSphere(Point pAnt, Point pAct){
	vec3 vector = (pAct.coord - pAnt.coord);
	float a, b, c;
	a = dot(vector, vector);
	b = 2 * dot(vector, pAnt.coord - center.coord);
	c = dot(pAnt.coord, pAnt.coord) - (2 * dot(center.coord, pAnt.coord)) - (radius*radius) + dot(center.coord, center.coord);
	float alpha1 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);
	float alpha2 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
	if (alpha1 >= 0 && alpha1 <= 1){
		return alpha1;
	}
	else if (alpha2 >= 0 && alpha2 <= 1){
		return alpha2;
	}
}

Plane Sphere::returnPlane(Point p){
	Plane myPlane;
	vec3 normal(p.coord.x - center.coord.x, p.coord.y - center.coord.y, p.coord.z - center.coord.z);
	myPlane.setPlaneNormal(normal.x,normal.y,normal.z);
	myPlane.setDirectFromNormal();
	myPlane.computeD();
	myPlane.normalizeNormal();
	return myPlane;
}