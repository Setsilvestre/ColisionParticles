#include <iostream>
#include "Particle.h"
#include "Sphere.h"
#include <time.h>

void main(){
	double start=clock();
	double end=0.0,diff;
	Point Center(1, 0, 1);
	Sphere mySphere(Center, 0.5);
	//Particle p[128];
	
	Particle p(1.0f, 10.0f, 0.9f);
	p.setFixed(false);
	p.addForce(0.0 , -9.8, 0.0);
	p.setBouncing(1.0f);
	p.setLifetime(2);



	float dt = 0.01f;
	float tini = 0.0f;
	float tfinal = 20.0f;
	int counter = 0;
	//p.setVelocity(0.1, 0, 0);
	Plane planeFront, planeLeft, planeRight, planeBack,planeBottom;
	Point f1(0,0,0), f2(2,0,0), f3(0,2,0),f4(2,2,0),b1(0,0,2),b2(2,0,2),b3(0,2,2),b4(2,2,2);
	planeFront.setPlaneFrom3Points(f1, f3, f2);
	planeLeft.setPlaneFrom3Points(f1, f3, b1);
	planeRight.setPlaneFrom3Points(f2, b2, f4);
	planeBack.setPlaneFrom3Points(b1, b2, b3);
	planeBottom.setPlaneFrom3Points(f1, b1, f2);
	int count = 0;
	bool afterSphere = true, beforeSphere = true;
	for (float t = tini; t <= tfinal; t += dt){
		p.updateParticle(dt, Particle::UpdateMethod::EulerSemi);
		//Check Floor collisions
		if (planeFront.useEquation(p.getCurrentPosition())*planeFront.useEquation(p.getPreviousPosition()) < 0){
			p.collisionWithPlane(planeFront);
			std::cout << "rebot FrontPlane = " << count++ << std::endl;
			system("PAUSE");
		}
		else if (planeLeft.useEquation(p.getCurrentPosition())*planeLeft.useEquation(p.getPreviousPosition()) < 0){
			p.collisionWithPlane(planeLeft);
			std::cout << "rebot LeftPlane= " << count++ << std::endl;
			system("PAUSE");
		}
		else if (planeRight.useEquation(p.getCurrentPosition())*planeRight.useEquation(p.getPreviousPosition()) < 0){
			p.collisionWithPlane(planeRight);
			std::cout << "rebot RightPlane= " << count++ << std::endl;
			system("PAUSE");
		}
		else if (planeBack.useEquation(p.getCurrentPosition())*planeBack.useEquation(p.getPreviousPosition()) < 0){
			p.collisionWithPlane(planeBack);
			std::cout << "rebot BackPlane= " << count++ << std::endl;
			system("PAUSE");
		}
		else if (planeBottom.useEquation(p.getCurrentPosition())*planeBottom.useEquation(p.getPreviousPosition()) < 0){
			p.collisionWithPlane(planeBottom);
			std::cout << "rebot BottomPlane= " << count++ << std::endl;
			system("PAUSE");
		}


		else if (mySphere.InsideorOut(p.getCurrentPosition()) == true){
			cout << "La recta talla a l'esfera en: " << endl;
			cout << p.getCurrentPosition().x;
			cout << " ";
			cout << p.getCurrentPosition().y;
			cout << " ";
			cout << p.getCurrentPosition().z << endl;
			Point myPoint(p.getCurrentPosition().x, p.getCurrentPosition().y, p.getCurrentPosition().z);
			p.collisionWithPlane(mySphere.returnPlane(myPoint));
			system("pause");
		}
		//std::cout << "posicio = " << p[1].getCurrentPosition().x << "  " << p[1].getCurrentPosition().y
		//	<< "  " << p[1].getCurrentPosition().z << "  temps = " << t << std::endl;
		//start = clock();
		//diff = (start - end) / (double)CLOCKS_PER_SEC;
		//if (diff > 0.5){
		//	cout << counter << endl;
		//	system("PAUSE");
		//	p[counter].setPosition(0, 10, 0);
		//	p[counter].setFixed(false);
		//	p[counter].addForce(0.0 , -9.8, 0.0);
		//	p[counter].setBouncing(0.8);
		//	p[counter].setLifetime(2);
		//	p[counter].setVelocity(rand() % 5 - 2.5, rand() % 5 - 2.5, rand() % 5 - 2.5);
		//	counter++;
		//	end = start;
		//}
		//	
		//for (int i = 0; i <= counter; i++){
		//	p[i].updateParticle(dt, Particle::UpdateMethod::EulerSemi);
		//	//Check Floor collisions
		//	if (planeFront.useEquation(p[i].getCurrentPosition())*planeFront.useEquation(p[i].getPreviousPosition())<0){
		//		p[i].collisionWithPlane(planeFront);
		//		std::cout << "rebot FrontPlane = " << count++ << std::endl;
		//		system("PAUSE");
		//	}
		//	else if (planeLeft.useEquation(p[i].getCurrentPosition())*planeLeft.useEquation(p[i].getPreviousPosition())<0){
		//		p[i].collisionWithPlane(planeLeft);
		//		std::cout << "rebot LeftPlane= " << count++ << std::endl;
		//		system("PAUSE");
		//	}
		//	else if (planeRight.useEquation(p[i].getCurrentPosition())*planeRight.useEquation(p[i].getPreviousPosition())<0){
		//		p[i].collisionWithPlane(planeRight);
		//		std::cout << "rebot RightPlane= " << count++ << std::endl;
		//		system("PAUSE");
		//	}
		//	else if (planeBack.useEquation(p[i].getCurrentPosition())*planeBack.useEquation(p[i].getPreviousPosition())<0){
		//		p[i].collisionWithPlane(planeBack);
		//		std::cout << "rebot BackPlane= " << count++ << std::endl;
		//		system("PAUSE");
		//	}
		//	else if (planeBottom.useEquation(p[i].getCurrentPosition())*planeBottom.useEquation(p[i].getPreviousPosition())<0){
		//		p[i].collisionWithPlane(planeBottom);
		//		std::cout << "rebot BottomPlane= " << count++ << std::endl;
		//		system("PAUSE");
		//	}
		//Check Sphere collision
		/*else if (mySphere.InsideorOut(p[i].getCurrentPosition())==false){
			cout << "La recta talla a l'esfera en: " << endl;
			cout << p[i].getCurrentPosition().x;
			cout << " ";
			cout << p[i].getCurrentPosition().y;
			cout << " ";
			cout << p[i].getCurrentPosition().z<<endl;
			Point myPoint(p[i].getCurrentPosition().x, p[i].getCurrentPosition().y, p[i].getCurrentPosition().z);
			p[i].collisionWithPlane(mySphere.returnPlane(myPoint));
			system("pause");
			}*/




		std::cout << "posicio = " << p.getCurrentPosition().x << "  " << p.getCurrentPosition().y
			<< "  " << p.getCurrentPosition().z << "  temps = " << t << std::endl;
		std::cout << p.getVelocity().y << endl;
		//system("pause");
		/*std::cout << "posicio = " << p[counter].getCurrentPosition().x << "  " << p[counter].getCurrentPosition().y
						  << "  " << p[counter].getCurrentPosition().z << "  temps = " << t << std::endl;*/

	}
	system("PAUSE");
}