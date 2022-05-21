#pragma once
#include<iostream>

#include<glew.h>
#include<glfw3.h>

#include<glm.hpp>
#include<vec3.hpp>
#include<mat4x4.hpp>
#include<gtc\matrix_transform.hpp>

enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT };

class Camera{
private:
	glm::mat4 ViewMatrix;

	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	void updateCameraVectors();

public:
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);

	//Accessors
	const glm::mat4 getViewMatrix();

	const glm::vec3 getPosition() const {return this->position;}

	//Functions
	void move(const float& dt, const int direction);
	
	void setPosition(glm::vec3 pos){this->position = pos;}

	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY);

	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY){
		this->updateMouseInput(dt, offsetX, offsetY);
	}

};