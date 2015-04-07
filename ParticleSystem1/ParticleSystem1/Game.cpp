#include "Game.h"


/**
* Constructor
* Note: It uses an initialization list to set the parameters
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS) :
	_windowTitle(windowTitle), 
	_screenWidth(screenWidth), 
	_screenHeight(screenHeight),
	_gameState(GameState::INIT), 
	_fpsLimiter(enableLimiterFPS, maxFPS, printFPS) {


}

/**
* Destructor
*/
Game::~Game()
{
}

/*
* Game execution
*/
void Game::run() {
		//System initializations
	initSystems();
		//Start the game if all the elements are ready
	gameLoop();
}

/*
* Initializes all the game engine components
*/
void Game::initSystems() {
	
		//Create an Opengl window using SDL
	_window.create(_windowTitle, _screenWidth, _screenHeight, 0);		
		//Compile and Link shader
	loadShaders();
		//Load the current scenario
	_openGLBuffers.initializeBuffers(_colorProgram);
		//Creates the camera
	_camera.create(0, _screenHeight, 0, 0.0f,30.0f,30.0f,30.0f);
		//Create several vertex
	createPrimitivesToRender();
}

/*
* Compiles, sets the variables between C++ and the Shader program and links the shader program
*/
void Game::loadShaders() {
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
void Game::createPrimitivesToRender() {
	//Read the txt file and sotre data
	_myGeometry.LoadScene();
	//Initialize a random seed
	srand(unsigned(time(NULL)));
	
}

/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {	
	_gameState = GameState::PLAY;
	while (_gameState != GameState::EXIT) {		
			//Start synchronization between refresh rate and frame rate
		_fpsLimiter.startSynchronization();
			//Process the input information (keyboard and mouse)
		processInput();
			//Execute pending actions
		updateGameObjects();
			//Draw the objects on the screen
		drawGame();	
			//Force synchronization
		_fpsLimiter.forceSynchronization();
	}
}

/*
* Processes input with SDL
*/
void Game::processInput() {
	//Review https://wiki.libsdl.org/SDL_Event to see the different kind of events
	//Moreover, table show the property affected for each event type
	SDL_Event evnt;
	float x, y, i=0;
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
			case SDLK_DOWN:
				cout << "Key down pressed" << endl;
				_myGeometry.Move(0, 3);
				break;
			case SDLK_UP:
				cout << "Key up pressed" << endl;
				_myGeometry.Move(0, 2);
				break;
			case SDLK_LEFT:
				cout << "Key left pressed" << endl;
				_myGeometry.Move(0, 0);
				break;
			case SDLK_RIGHT:
				cout << "Key right pressed" << endl;
				_myGeometry.Move(0, 1);
				break;
			case SDLK_w:
				cout << "Key w pressed" << endl;
				_camera.updateCameraFront(0, 0, 0.1);
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
void Game::drawGame() {
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
	
	for (int i = 0; i < _myGeometry.returnPrimitives(); i++){
		glm::mat4 modelMatrix;
		modelMatrix = glm::translate(modelMatrix,_myGeometry.returnTranslate(i));
		modelMatrix = glm::rotate(modelMatrix, _myGeometry.returnAngle(i), _myGeometry.returnRotate(i));
		modelMatrix = glm::scale(modelMatrix, _myGeometry.returnScale(i));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
		//Send the matrix to the vertex shader
		GLuint modelMatrixUniform = _colorProgram.getUniformLocation("modelMatrix");
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		GLuint viewMatrixUniform = _colorProgram.getUniformLocation("viewMatrix");
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera.returnViewMatrix()));
		GLuint projectionMatrixUniform = _colorProgram.getUniformLocation("projectionMatrix");
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera.returnProjectionMatrix()));
		//Send data to GPU
		_openGLBuffers.sendDataToGPU(_myGeometry.ReturnData(i), MAX_VERTICES);
	}
		//Unbind the program
	_colorProgram.unuse();

		//Swap the display buffers (displays what was just drawn)
	_window.swapBuffer();
}

/*
* Execute the actions that must update the game objects
*/

void Game::updateGameObjects() {
	//Add a random movement each second
	double diff;
	start = clock();
	diff = (start - timer) / (double)CLOCKS_PER_SEC;
	if (diff >0.25){
		_myGeometry.moveAll();
	}
	
	_camera.lookAt();
}