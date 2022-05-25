#pragma once

#include "Shader.hpp"

#include <glm.hpp>

/**
 * Class designed to create and represent light sources.
 */
class Light {
private:
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	float constant;
	float linear;
	float quadratic;

public:
	/**
	 * The constructor that initializes a new Light object and makes it ready to be placed in the world.
	 * @param position The initial position of the light source.
	 * @param color A vector with RGB values to specify the initial light color.
	 * @param intensity An intensity of the light source.
	 * @param constant A value used to calculate the constant light attenuation.
	 * @param linear A value used to calculate the linear light attenuation.
	 * @param quadratic A value used to calculate the quadratic light attenuation.
	 */
	Light(
		glm::vec3 position,
		glm::vec3 color = glm::vec3(1.f),
		float intensity = 5.f,
		float constant = 5.f,
		float linear = 5.f,
		float quadratic = 0.9f
	);

	/**
	 * Sets the position using the provided vector.
	 * @param position A new position vector.
	 */
	void setPosition(const glm::vec3 position);

	/**
	 * Sends light data to a bunch of uniforms in a particular shader program.
	 * @param program A shader program used to reference
	 *     uniforms to which the light data is to be send.
	 */
	void sendToShader(Shader& program);
};
