#include <iostream>
#include "Particle.h"
#include <time.h>

void main(){
	double start=clock();
	double end=0.0,diff;
	Particle p[128];
	float dt = 0.01f;
	float tini = 0.0f;
	float tfinal = 20.0f;
	int counter = 0;
	//p.setVelocity(0.1, 0, 0);
	Plane planeFront, planeLeft, planeRight, planeBack,planeBottom;
	Point f1(0,0,0), f2(2,0,0), f3(0,2,0),f4(2,2,0),b1(0,0,2),b2(2,0,2),b3(0,2,2),b4(2,2,2);
	planeFront.setPlaneFrom3Points(f1, f3, f2);
	planeLeft.setPlaneFrom3Points(f1, b1, f3);
	planeRight.setPlaneFrom3Points(f2, f4, b2);
	planeBack.setPlaneFrom3Points(b1, b2, b3);
	planeBottom.setPlaneFrom3Points(f1, f2, b1);
	int count = 0;
	for (float t = tini; t <= tfinal; t += dt){
		start = clock();
		diff = (start - end) / (double)CLOCKS_PER_SEC;
		if (diff > 0.5){
			cout << counter << endl;
			system("PAUSE");
			p[counter].addForce(0.0 , -9.8, 0.0);
			p[counter].setBouncing(0.8);
			p[counter].setLifetime(2);
			p[counter].setVelocity(rand() % 5 - 2.5, rand() % 5 - 2.5, rand() % 5 - 2.5);
			counter++;
			end = start;
		}
			
		for (int i = 0; i <= counter; i++){
			p[i].updateParticle(dt, Particle::UpdateMethod::EulerSemi);
			//Check Floor collisions
			if (planeFront.useEquation(p[i].getCurrentPosition())*planeFront.useEquation(p[i].getPreviousPosition())<0){
				p[i].collisionWithPlane(planeFront);
				std::cout << "rebot = " << count++ << std::endl;
				system("PAUSE");
			}
			else if (planeLeft.useEquation(p[i].getCurrentPosition())*planeLeft.useEquation(p[i].getPreviousPosition())<0){
				p[i].collisionWithPlane(planeLeft);
				std::cout << "rebot = " << count++ << std::endl;
				system("PAUSE");
			}
			else if (planeRight.useEquation(p[i].getCurrentPosition())*planeRight.useEquation(p[i].getPreviousPosition())<0){
				p[i].collisionWithPlane(planeRight);
				std::cout << "rebot = " << count++ << std::endl;
				system("PAUSE");
			}
			else if (planeBack.useEquation(p[i].getCurrentPosition())*planeBack.useEquation(p[i].getPreviousPosition())<0){
				p[i].collisionWithPlane(planeBack);
				std::cout << "rebot = " << count++ << std::endl;
				system("PAUSE");
			}
			else if (planeBottom.useEquation(p[i].getCurrentPosition())*planeBottom.useEquation(p[i].getPreviousPosition())<0){
				p[i].collisionWithPlane(planeBottom);
				std::cout << "rebot = " << count++ << std::endl;
				system("PAUSE");
			}

			
		}
		
		std::cout << "posicio = " << p[counter].getCurrentPosition().x << "  " << p[counter].getCurrentPosition().y 
			              << "  " << p[counter].getCurrentPosition().z << "  temps = " << t << std::endl;
		
	}
	system("PAUSE");
}