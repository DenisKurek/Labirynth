#pragma once

#include "Shader.hpp"
#include "Vertex.hpp"

#include <glew.h>
#include <glm.hpp>

/**
 * Class responsible for generating and dealing with polygon meshes.
 */
class Mesh {
private:
	unsigned noOfVertices;
	unsigned noOfIndices;
	Vertex* vertexArray;
	GLuint* indexArray;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 origin;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

public:
	/**
	 * The constructor that sets up a Mesh object and makes it ready to be used and rendered.
	 * @param noOfVertices The number of vertices that make up the mesh.
	 * @param noOfIndices The number of indices that specify which vertices should be together.
	 * @param vertexArray A pointer to the array that contains the vertices.
	 * @param indexArray A pointer to the array that contains the indices.
	 * @param position An initial position of the mesh.
	 * @param origin An initial origin of the mesh.
	 * @param rotation An initial rotation of the mesh.
	 * @param scale An initial scale of the mesh.
	 */
	Mesh(
		const unsigned& noOfVertices,
		const unsigned& noOfIndices,
		Vertex* vertexArray,
		GLuint* indexArray,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 origin = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f)
	);

	/**
	 * The copy constructor that creates a copy of an existing Mesh object.
	 */
	Mesh(const Mesh& other);

	/**
	 * The destructor that frees up dynamically allocated memory in a Mesh
	 *     object and deletes the VAO, VBO, and EBO that are no longer needed.
	 */
	~Mesh();

	/**
	 * Gets and returns the vector that contains the position.
	 * @return The vector that contains the position.
	 */
	const glm::vec3 getPosition() const;

	/**
	 * Sets the position using the provided vector.
	 * @param position A new position vector.
	 */
	void setPosition(const glm::vec3 position);

	/**
	 * Sets the origin using the provided vector.
	 * @param origin A new origin vector.
	 */
	void setOrigin(const glm::vec3 origin);

	/**
	 * Sets the rotation using the provided vector.
	 * @param rotation A new rotation vector.
	 */
	void setRotation(const glm::vec3 rotation);

	/**
	 * Sets the scale using the provided vector.
	 * @param scale A new scale vector.
	 */
	void setScale(const glm::vec3 scale);

	/**
	 * Moves the mesh based on the provided motion vector.
	 * @param motionVec A motion vector.
	 */
	void move(const glm::vec3 motionVec);

	/**
	 * Rotates the mesh based on the provided rotation vector.
	 * @param rotationVec A rotation vector.
	 */
	void rotate(const glm::vec3 rotationVec);

	/**
	 * Scales the mesh based on the provided scaling vector.
	 * @param scalingVec A scaling vector.
	 */
	void scaleUp(const glm::vec3 scalingVec);

	/**
	 * Renders the mesh that belongs to the Mesh object, on which
	 *     this method has been invoked, on the scene.
	 * @param program A shader program used to reference
	 *     the uniform to which the model matrix is to be send.
	 */
	void render(Shader* program);

private:
	/**
	 * Initializes the Vertex Array Object (VAO) (including the Vertex
	 *     Buffer Object (VBO) and Element Buffer Object (EBO)).
	 */
	void initVAO();

	/**
	 * Updates the model matrix with the new translation, rotation, and scale values.
	 */
	void updateModelMatrix();

	/**
	 * Sends the model matrix to the corresponding uniform in a particular shader program.
	 * @param program A shader program used to reference
	 *     the uniform to which the model matrix is to be send.
	 */
	void updateUniform(Shader* program);
};
