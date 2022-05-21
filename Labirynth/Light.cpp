#include"Light.h"


void PointLight::sendToShader(Shader& program) {
	program.setVec3f(this->position, "pointLight.position");
	program.set1f(this->intensity, "pointLight.intensity");
	program.setVec3f(this->color, "pointLight.color");
	program.set1f(this->constant, "pointLight.constant");
	program.set1f(this->linear, "pointLight.linear");
	program.set1f(this->quadratic, "pointLight.quadratic");
}
