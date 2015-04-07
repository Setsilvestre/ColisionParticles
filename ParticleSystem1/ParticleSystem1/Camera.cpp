#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::create(int screenWidth, int screenHeight, bool type, float _near, float _far, float _projectionWidth, float _projectionHeight){
	//Creates a ortographic Camera
	if (type == 0){
		this->_near = _near;
		this->_far = _far;
		this->_projectionWidth = _projectionWidth;
		this->_projectionHeight = _projectionHeight;
		this->_cameraPos = glm::vec3(0, 0, 0);
		this->_cameraFront = glm::vec3(0, 0, -10);
		_projectionMatrix = glm::ortho(-_projectionWidth / 2, _projectionWidth / 2, -_projectionHeight / 2, _projectionHeight / 2, _near, _far);
	}
	//Creates a prespective Camera
	if (type != 0){
		this->_near = _near;
		this->_far = _far;
		this->_projectionWidth = _projectionWidth;
		this->_projectionHeight = _projectionHeight;
		this->_cameraPos = glm::vec3(0, 0, 10);
		this->_cameraFront = glm::vec3(0, 0, -10);
		this->_aspectRatio = screenWidth / screenHeight;
		_FOV = 45.0f;
		_projectionMatrix = glm::perspective(_FOV, _aspectRatio, _near, _far);
	}
}

glm::mat4 Camera::returnProjectionMatrix(){
	return _projectionMatrix;
}

void Camera::lookAt(){
	glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	_cameraUp = glm::cross(cameraDirection, cameraRight);
	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront, _cameraUp);
}

glm::mat4 Camera::returnViewMatrix(){
	return _viewMatrix;
}

void Camera::updateCameraPosition(float x, float y, float z){
	_cameraPos +=glm::vec3(x, y, z);
}

void Camera::updateCameraFront(float x, float y, float z){
	_cameraFront += glm::vec3(x, y, z);
}

void Camera::cameraSwapFPS(){
		_cameraPos = glm::vec3(-15, 0, 0);
		_cameraFront = glm::vec3(10, 0, 0);
	
	//	_projectionMatrix = glm::perspective(_FOV, _aspectRatio, _near, _far);
}

void Camera::defaultCamera(){
	_cameraPos = glm::vec3(0, 0, 10);
	_cameraFront = glm::vec3(0, 0, -10);
}