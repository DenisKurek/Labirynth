#pragma once
#include<vector>
#include"Vertex.h"

#include<glew.h> //before glfw3 !!
#include<glfw3.h>

class Primitive {
public:
	Primitive() {

	}
	virtual ~Primitive(){

	}

	//functions
	void set(
		const Vertex* vertices,
		const unsigned nrOfVertices,
		const GLuint* indices,
		const unsigned nrOfIndices
		) {
		for (size_t i = 0; i < nrOfVertices; i++) {
			this->vertices.push_back(vertices[i]);
		}
		for (size_t i = 0; i <nrOfIndices; i++) {
			this->indices.push_back(indices[i]);
		}
	}

	inline Vertex* getVertices() {return this->vertices.data();}

	inline GLuint* getIndices() {return this->indices.data();}

	inline const unsigned getNrOfVertices() { return vertices.size();}
	inline const unsigned getNrOfIndices() { return indices.size();}

private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};

class Quad : public Primitive {
public:
	Quad() {
		Vertex vertices[] = {
			//position						//color							//Texcoords				//Normals
			glm::vec3(-0.5f,0.5f,0.f),		glm::vec3(1.f,0.f,0.f),			glm::vec2(0.f,1.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(-0.5f,-0.5f,0.f),		glm::vec3(0.f,1.f,0.f),			glm::vec2(0.f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,-0.5f,0.f),		glm::vec3(0.f,0.f,1.f),			glm::vec2(1.f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,0.5f,0.f),		glm::vec3(0.f,1.f,0.f),			glm::vec2(1.f,1.f),		glm::vec3(0.f,0.f,1.f)
		};
		unsigned nrOFVertices = sizeof(vertices) / sizeof(Vertex); // does not work on pointers

		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint); // does not work on pointers
		this->set(vertices, nrOFVertices, indices, nrOfIndices);
	}

private:
};

class Triangle : public Primitive {
public:
	Triangle() {
		Vertex vertices[] = {
			//position						//color							//Texcoords				//Normals
			glm::vec3(-0.5f,0.5f,0.f),		glm::vec3(1.f,0.f,0.f),			glm::vec2(0.f,1.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(-0.5f,-0.5f,0.f),		glm::vec3(0.f,1.f,0.f),			glm::vec2(0.f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,-0.5f,0.f),		glm::vec3(0.f,0.f,1.f),			glm::vec2(1.f,0.f),		glm::vec3(0.f,0.f,1.f),
		};
		unsigned nrOFVertices = sizeof(vertices) / sizeof(Vertex); // does not work on pointers

		GLuint indices[] = {
			0, 1, 2,
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint); // does not work on pointers
		this->set(vertices, nrOFVertices, indices, nrOfIndices);
	}

private:
};

