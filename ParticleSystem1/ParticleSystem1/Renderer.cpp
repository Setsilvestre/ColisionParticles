#include "Renderer.h"
/**
* Constructor
* Note: It uses an initialization list to set the parameters
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Renderer::Renderer(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS) :
_windowTitle(windowTitle),
_screenWidth(screenWidth),
_screenHeight(screenHeight),
_fpsLimiter(enableLimiterFPS, maxFPS, printFPS)
{

}

/**
* Destructor
*/
Renderer::~Renderer()
{
}

/*
* Game execution
*/
void Renderer::run() {
	//System initializations
	initSystems();
	//Start the game if all the elements are ready
	gameLoop();
}

/*
* Initializes all the game engine components
*/
void Renderer::initSystems() {

	//Create an Opengl window using SDL
	_window.create(_windowTitle, _screenWidth, _screenHeight, 0);
	//Compile and Link shader
	loadShaders();
	//Load the current scenario
	_openGLBuffers.initializeBuffers(_colorProgram);
	//Creates the camera
	_camera.create(0, _screenHeight, 0, 0.0f, 30.0f, 30.0f, 30.0f);
	//Create several vertex
	createPrimitivesToRender();

		p.setPosition(1.0f, 10.0f, 0.9f);
		p.setFixed(false);
		p.addForce(0.0 , -9.8, 0.0);
		p.setBouncing(1.0f);
		p.setLifetime(2);
	
		Point f1(0, 0, 0), f2(2, 0, 0), f3(0, 2, 0), f4(2, 2, 0), b1(0, 0, 2), b2(2, 0, 2), b3(0, 2, 2), b4(2, 2, 2);
	
	
		planeFront.setPlaneFrom3Points(f1, f3, f2);
		planeLeft.setPlaneFrom3Points(f1, f3, b1);
		planeRight.setPlaneFrom3Points(f2, b2, f4);
		planeBack.setPlaneFrom3Points(b1, b2, b3);
		planeBottom.setPlaneFrom3Points(f1, b1, f2);
		Point r(1, 0, 1);
		mySphere.set(r, 0.5);

		int count = 0;
		bool afterSphere = true, beforeSphere = true;
}

/*
* Compiles, sets the variables between C++ and the Shader program and links the shader program
*/
void Renderer::loadShaders() {
	//Compile the shaders
	_colorProgram.addShader(GL_VERTEX_SHADER, "./resources/shaders/vertex-shader.txt");
	_colorProgram.addShader(GL_FRAGMENT_SHADER, "./resources/shaders/fragment-shader.txt");
	_colorProgram.compileShaders();
	//Attributes must be added before linking the code
	_colorProgram.addAttribute("vertexPositionGame");
	_colorProgram.addAttribute("vertexColor");
	//Link the compiled shaders
	_colorProgram.linkShaders();
}

/**
* Initialize the position and the color of the different vertices that have to be rendered
*/
void Renderer::createPrimitivesToRender() {
	

	

}

/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Renderer::gameLoop() {
		//Start synchronization between refresh rate and frame rate
		_fpsLimiter.startSynchronization();
	
		//Execute pending actions
		updateGameObjects();




		for (float t = tini; t <= tfinal; t += dt){
			//Process the input information (keyboard and mouse)
			processInput();
			//Draw the objects on the screen
			drawGame();
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
				//system("PAUSE");
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
				//system("pause");
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
		
		//Force synchronization
		_fpsLimiter.forceSynchronization();
}


/*
* Processes input with SDL
*/
void Renderer::processInput() {
	//Review https://wiki.libsdl.org/SDL_Event to see the different kind of events
	//Moreover, table show the property affected for each event type
	SDL_Event evnt;
	float x, y, i = 0;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << "(" << evnt.motion.x << ", " << evnt.motion.y << ")" << endl;
			break;
		case SDL_MOUSEBUTTONUP:
			cout << "Button up" << endl;
			break;
		case SDL_MOUSEBUTTONDOWN:
			cout << "Button down" << endl;
			break;
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym){
			case SDLK_w:
				cout << "Key w pressed" << endl;
				_camera.updateCameraFront(0, 0, 0.1);
				system("pause");
				break;
			case SDLK_s:
				cout << "Key s pressed" << endl;
				_camera.updateCameraFront(0, 0, -0.1);
				break;
			case SDLK_a:
				cout << "Key a pressed" << endl;
				_camera.updateCameraFront(-0.1, 0, 0);
				break;
			case SDLK_d:
				cout << "Key d pressed" << endl;
				_camera.updateCameraFront(0.1, 0, 0);
				break;
			case SDLK_f:
				cout << "Key f pressed" << endl;
				_camera.cameraSwapFPS();
				break;
			case SDLK_g:
				cout << "Key g pressed" << endl;
				_camera.defaultCamera();
				break;

				/*case SDLK_PLUS:
				cout << "Key plus pressed" << endl;
				modelMatrix = glm::scale(modelMatrix, glm::vec3(1.25, 1.25, 1.25));
				break;
				case SDLK_MINUS:
				cout << "Key minus pressed" << endl;
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75, 0.75, 0.75));
				break;*/
			}

		default:
			break;
		}
	}
}

/**
* Draw the sprites on the screen
*/
void Renderer::drawGame() {
	//Set the base depth to 1.0
	glClearDepth(1.0);

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Bind the GLSL program. Only one code GLSL can be used at the same time
	_colorProgram.use();
	//GameElement currentElement;
	//Pass the matrix information to the shader
	//Get the uniform variable location
	//Pass the matrix
	//1st parameter: the location
	//2nd parameter: the number of matrices
	//3rd parameter: if we want to tranpose the matrix
	//4th parameter: the matrix data
	glPointSize(10.0f);//set point size to 10 pixels
	glBegin(GL_POINTS);
	glVertex3f(p.getCurrentPosition().x, p.getCurrentPosition().y, p.getCurrentPosition().z);
	glEnd();
	
	
		//_openGLBuffers.sendDataToGPU(glPoint, MAX_VERTICES);
	
	//Unbind the program
	_colorProgram.unuse();

	//Swap the display buffers (displays what was just drawn)
	_window.swapBuffer();
}


/*
* Execute the actions that must update the game objects
*/

void Renderer::updateGameObjects() {
	
	_camera.lookAt();
}