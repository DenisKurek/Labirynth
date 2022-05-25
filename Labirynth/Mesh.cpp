#include "Mesh.hpp"

Mesh::Mesh(
	const unsigned& noOfVertices,
	const unsigned& noOfIndices,
	Vertex* vertexArray,
	GLuint* indexArray,
	glm::vec3 position,
	glm::vec3 origin,
	glm::vec3 rotation,
	glm::vec3 scale
) : noOfVertices(noOfVertices), noOfIndices(noOfIndices),
	position(position), origin(origin), rotation(rotation), scale(scale) {

	this->vertexArray = new Vertex[this->noOfVertices];
	for (size_t i = 0; i < this->noOfVertices; i++) {
		this->vertexArray[i] = vertexArray[i];
	}

	this->indexArray = new GLuint[this->noOfIndices];
	for (size_t i = 0; i < this->noOfIndices; i++) {
		this->indexArray[i] = indexArray[i];
	}

	this->initVAO();
	this->updateModelMatrix();
}

Mesh::Mesh(const Mesh& other)
	: noOfVertices(other.noOfVertices), noOfIndices(other.noOfIndices),
	position(other.position), origin(other.origin), rotation(other.rotation), scale(other.scale) {

	this->vertexArray = new Vertex[this->noOfVertices];
	for (size_t i = 0; i < this->noOfVertices; i++) {
		this->vertexArray[i] = other.vertexArray[i];
	}

	this->indexArray = new GLuint[this->noOfIndices];
	for (size_t i = 0; i < this->noOfIndices; i++) {
		this->indexArray[i] = other.indexArray[i];
	}

	this->initVAO();
	this->updateModelMatrix();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);

	if (this->noOfIndices > 0) {
		glDeleteBuffers(1, &this->EBO);
	}

	delete[] this->vertexArray;
	delete[] this->indexArray;
}

const glm::vec3 Mesh::getPosition() const {
	return this->position;
}

void Mesh::setPosition(const glm::vec3 position) {
	this->position = position;
}

void Mesh::setOrigin(const glm::vec3 origin) {
	this->origin = origin;
}

void Mesh::setRotation(const glm::vec3 rotation) {
	this->rotation = rotation;
}

void Mesh::setScale(const glm::vec3 scale) {
	this->scale = scale;
}

void Mesh::move(const glm::vec3 motionVec) {
	this->position += motionVec;
}

void Mesh::rotate(const glm::vec3 rotationVec) {
	this->rotation += rotationVec;
}

void Mesh::scaleUp(const glm::vec3 scalingVec) {
	this->scale += scalingVec;
}

void Mesh::render(Shader* program) {
	// Update uniforms
	this->updateModelMatrix();
	this->updateUniform(program);

	program->use();

	// Bind VAO
	glBindVertexArray(this->VAO);

	// Render
	if (this->noOfIndices == 0) {
		glDrawArrays(GL_TRIANGLES, 0, this->noOfVertices);
	} else {
		glDrawElements(GL_TRIANGLES, this->noOfIndices, GL_UNSIGNED_INT, 0);
	}

	// Clean up
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::initVAO() {
	// Create VAO
	glCreateVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	// Gen VBO, then bind and send data
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->noOfVertices * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW);

	// Gen EBO, then bind and send data
	if (this->noOfIndices > 0) {
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->noOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);
	}

	// SET VERTEX ATTRIB POINTERS AND ENABLE (INPUT ASSEMBLY)
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// Texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	// Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	// Unbind VAO
	glBindVertexArray(0);
}

void Mesh::updateModelMatrix() {
	this->ModelMatrix = glm::mat4(1.f);

	this->ModelMatrix = glm::translate(this->ModelMatrix, this->origin);
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->origin);
	this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

void Mesh::updateUniform(Shader* program) {
	program->setMat4fv(this->ModelMatrix, "ModelMatrix");
}
