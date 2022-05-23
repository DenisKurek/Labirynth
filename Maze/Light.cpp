#include "Light.hpp"

Light::Light(
	glm::vec3 position,
	glm::vec3 color,
	float intensity,
	float constant,
	float linear,
	float quadratic
) : position(position), color(color), intensity(intensity),
	constant(25), linear(linear), quadratic(quadratic) {}

void Light::setPosition(const glm::vec3 position) {
	this->position = position;
}

void Light::sendToShader(Shader& program) {
	program.setVec3f(this->position, "light.position");
	program.setVec3f(this->color, "light.color");
	program.set1f(this->intensity, "light.intensity");
	program.set1f(this->constant, "light.constant");
	program.set1f(this->linear, "light.linear");
	program.set1f(this->quadratic, "light.quadratic");
}
