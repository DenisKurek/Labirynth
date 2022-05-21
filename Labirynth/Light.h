#pragma once
#include"libs.h"

class Light
{
protected:
	float intensity;
	glm::vec3 color;

public:
	Light(float intensity, glm::vec3 color){
		this->intensity = intensity;
		this->color = color;
	}

	//Functions
	virtual void sendToShader(Shader& program) = 0;
};

class PointLight : public Light
{
protected:
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
public:
	PointLight(
		glm::vec3 position, float intensity = 1.f, 
		glm::vec3 color = glm::vec3(1.f),
		float constant = 5.f, float linear = 4.f, 
		float quadratic = 0.5f
	)
		: Light(intensity, color){
			this->position = position;
			this->constant =  25; // constant;
			this->linear = linear;
			this->quadratic = quadratic;
	}

	void setPosition(const glm::vec3 position){this->position = position;
}

	void sendToShader(Shader& program);
};