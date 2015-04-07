#pragma once


//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <time.h>
#include "Window.h"
#include "GLSLProgram.h"
#include "FPSLimiter.h"
#include "OpenGLBuffers.h"
#include "Vertex.h"
#include "Camera.h"
#include <iostream>
#include "Particle.h"
#include "Sphere.h"
#include <time.h>

//Game has three possible states: INIT (Preparing environment), PLAY (Playing) or EXIT (Exit from the game)
enum class GameState{ INIT, PLAY, EXIT };

class Renderer{
public:
	Renderer(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS);	//Constructor
	~Renderer();					//Destructor
	void run();					//Game execution
	double timer = 0;			//Time flow
	double start = 0;
private:
	//Attributes	
	std::string _windowTitle;		//Window Title
	int _screenWidth;				//Screen width in pixels				
	int _screenHeight;				//Screen height in pixels	
	GameState _gameState;			//It describes the game state
	Window _window;					//Manage the OpenGL context
	GLSLProgram _colorProgram;		//Manage the shaders
	FPSLimiter _fpsLimiter;			//Manage the synchronization between frame rate and refresh rate
	OpenGLBuffers _openGLBuffers;	//Manage the openGL buffers
	Camera _camera;					//Manage the camera
	//Internal methods
	void initSystems();
	void loadShaders();
	void createPrimitivesToRender();
	void gameLoop();
	void processInput();
	void updateGameObjects();
	void drawGame();

	

	Sphere mySphere;
	//Particle p[128];

	Particle p;
	float dt = 0.01f;
	float tini = 0.0f;
	float tfinal = 20.0f;
	int counter = 0;
	//p.setVelocity(0.1, 0, 0);
	Plane planeFront, planeLeft, planeRight, planeBack, planeBottom;
	int count = 0;
};