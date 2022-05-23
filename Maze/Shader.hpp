#pragma once

#include <glew.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

class Shader {
private:
	GLuint id;

public:
	/**
	 * The constructor that initializes a new Shader object and makes it ready to be used.
	 *
	 * This process involves a few stages. The shader source codes are read from the files, then they are
	 *     compiled, linked together, attached, and a complete shader program is created as a result.
	 * @param vertexFile The name of the file that stores the vertex shader source code.
	 * @param fragmentFile The name of the file that stores the fragment shader source code.
	 * @note On failure, prints more details to the standard error output.
	 */
	Shader(const char* vertexFile, const char* fragmentFile);

	/**
	 * The destructor that deletes the shader program that is no longer needed.
	 */
	~Shader();

	/**
	 * Sets the shader program that belongs to the Shader object, on which this
	 *     method has been invoked, as the one that will be used from now on.
	 */
	void use();

	/**
	 * Sets the shader program that belongs to the Shader object, on which this
	 *     method has been invoked, as the one that will no longer be used.
	 */
	void unuse();

	/**
	 * Sets the content of a particular uniform using an integer number.
	 * @param value An integer number that will be used as a data source.
	 * @param name Name of an uniform variable in a shader source code.
	 */
	void set1i(GLint value, const GLchar* name);

	/**
	 * Sets the content of a particular uniform using a float number.
	 * @param value A float number that will be used as a data source.
	 * @param name Name of an uniform variable in a shader source code.
	 */
	void set1f(GLfloat value, const GLchar* name);

	/**
	 * Sets the contents of a particular uniform using a 2-element vector with float numbers.
	 * @param value A 2-element vector with float numbers that will be used as a data source.
	 * @param name Name of an uniform variable in a shader source code.
	 */
	void setVec2f(glm::fvec2 value, const GLchar* name);

	/**
	 * Sets the contents of a particular uniform using a 3-element vector with float numbers.
	 * @param value A 3-element vector with float numbers that will be used as a data source.
	 * @param name Name of an uniform variable in a shader source code.
	 */
	void setVec3f(glm::fvec3 value, const GLchar* name);

	/**
	 * Sets the contents of a particular uniform using a 4-element vector with float numbers.
	 * @param value A 4-element vector with float numbers that will be used as a data source.
	 * @param name Name of an uniform variable in a shader source code.
	 */
	void setVec4f(glm::fvec4 value, const GLchar* name);

	/**
	 * Sets the contents of a particular uniform using a 3x3 matrix with float numbers.
	 * @param value A 3x3 matrix with float numbers that will be used as a data source.
	 * @param name Name of an uniform variable in a shader source code.
	 * @param transpose Specifies whether to transpose the matrix or not.
	 */
	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);

	/**
	 * Sets the contents of a particular uniform using a 4x4 matrix with float numbers.
	 * @param value A 4x4 matrix with float numbers that will be used as a data source.
	 * @param name Name of an uniform variable in a shader source code.
	 * @param transpose Specifies whether to transpose the matrix or not.
	 */
	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);

private:
	/**
	 * Reads a particular shader source code from the given file.
	 * @param fileName The name of the file, from which the shader code is to be read.
	 * @return A standard string that contains the shader code that has been read.
	 * @note On failure, prints more details to the standard error output.
	 */
	std::string readShaderSource(const char* fileName);

	/**
	 * Loads a particular shader, compiles it, and then returns the compilation results.
	 * @param type A predefined type of the shader that is to be loaded.
	 * @param fileName The name of the file that stores the shader source code.
	 * @return The compiled shader.
	 * @note On failure, prints more details to the standard error output.
	 */
	GLuint loadShader(GLenum type, const char* fileName);

	/**
	 * Creates a complete shader program by linking the provided sharders together and attaching them.
	 * @param vertexShader The compiled vertex shader.
	 * @param fragmentShader The compiled fragment shader.
	 * @note On failure, prints more details to the standard error output.
	 */
	void linkProgram(GLuint vertexShader, GLuint fragmentShader);
};
