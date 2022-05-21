#pragma once
#include<iostream>
#include<vector>

#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Vertex.h"
#include "Primitives.h"

class Mesh
{

public:
	Mesh(
		Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndices,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 origin = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f));

	Mesh(const Mesh& obj);

	~Mesh();

	void showPosition(){
		std::cout << this->position.x << " " << this->position.y << " " << this->position.z << " " << std::endl;
	}

	const glm::vec3 Position() {return this->position;}

	void setPosition(const glm::vec3 position){this->position = position;}

	void setOrigin(const glm::vec3 origin){this->origin = origin;}

	void setRotation(const glm::vec3 rotation){this->rotation = rotation;}

	void setScale(const glm::vec3 setScale){this->scale = scale;}

	void move(const glm::vec3 position){this->position += position;}

	void rotate(const glm::vec3 rotation){this->rotation += rotation;}

	void scaleUp(const glm::vec3 scale){this->scale += scale;}

	void render(Shader* shader);


private:
	Vertex* vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 origin;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

	void initVAO();

	void updateUniforms(Shader* shader) { shader->setMat4fv(this->ModelMatrix, "ModelMatrix"); }

	void updateModelMatrix();
};                                      

