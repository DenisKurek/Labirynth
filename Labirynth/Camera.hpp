#pragma once

#include <ext/matrix_transform.hpp>
#include <glew.h>
#include <glm.hpp>

enum Direction {
	FORWARD = 0,
	FORWARD_RUN,
	BACKWARD,
	LEFT,
	RIGHT
};

/**
 * Class that represents the camera.
 */
class Camera {
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

public:
	/**
	 * The constructor that initializes a new Camera object and makes it ready to be used.
	 * @param position The initial position of the camera.
	 * @param worldUp A vector that specifies in what direction is the top of the world.
	 */
	Camera(glm::vec3 position, glm::vec3 worldUp);

	/**
	 * Prepares and then returns the camera view matrix.
	 * @return The camera view matrix.
	 */
	const glm::mat4 getViewMatrix();

	/**
	 * Gets and returns the vector that contains the camera position.
	 * @return The vector that contains the camera position.
	 */
	const glm::vec3 getPosition() const;

	/**
	 * Sets the camera position using the provided vector.
	 * @param position A new position vector.
	 */
	void setPosition(glm::vec3 position);

	/**
	 * Simulates a movement of the camera in some direction.
	 * @param dt A delta time that affects the movement speed.
	 * @param direction A predefined direction in which the camera movement is to be simulated.
	 */
	void move(const float& dt, Direction direction);

	/**
	 * Updates a pitch, yaw, and roll based on the mouse movement.
	 * @param dt A delta time that affects the movement speed.
	 * @param offsetX The difference between the previous
	 *     mouse position and the current one along the X axis.
	 * @param offsetY The difference between the previous
	 *     mouse position and the current one along the Y axis.
	 */
	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY);

private:
	/**
	 * Updates the camera vectors based on the current pitch, yaw, and roll.
	 */
	void updateCameraVectors();
};
