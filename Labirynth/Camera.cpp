#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp)
	: position(position), worldUp(worldUp), up(worldUp) {
	this->ViewMatrix = glm::mat4(1.f);

	this->movementSpeed = 8.f;
	this->sensitivity = 5.f;

	this->right = glm::vec3(0.f);

	this->pitch = 0.f;
	this->yaw = -90.f;
	this->roll = 0.f;

	this->updateCameraVectors();
}

const glm::mat4 Camera::getViewMatrix() {
	this->updateCameraVectors();

	this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

	return this->ViewMatrix;
}

const glm::vec3 Camera::getPosition() const {
	return this->position;
}

void Camera::setPosition(glm::vec3 position) {
	this->position = position;
}

void Camera::move(const float& dt, Direction direction) {
	// Update the position vector
	switch (direction) {
		case FORWARD:
			this->position += this->front * this->movementSpeed * dt;
			break;
		case FORWARD_RUN:
			this->position += this->front * (1.5f * this->movementSpeed) * dt;
			break;
		case BACKWARD:
			this->position -= this->front * this->movementSpeed * dt;
			break;
		case LEFT:
			this->position -= this->right * this->movementSpeed * dt;
			break;
		case RIGHT:
			this->position += this->right * this->movementSpeed * dt;
			break;
	}
}

void Camera::updateMouseInput(const float& dt, const double& offsetX, const double& offsetY) {
	// Update pitch, yaw and roll
	this->pitch += static_cast<GLfloat>(offsetY) * this->sensitivity * dt;
	this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;

	if (this->pitch > 80.f) {
		this->pitch = 80.f;
	} else if (this->pitch < -80.f) {
		this->pitch = -80.f;
	}

	if (this->yaw > 360.f || this->yaw < -360.f) {
		this->yaw = 0.f;
	}
}

void Camera::updateCameraVectors() {
	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}
