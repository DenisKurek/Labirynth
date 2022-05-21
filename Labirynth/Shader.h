#pragma once
#include<iostream>
#include <fstream>
#include <string>

#include<glew.h> //before glfw3 !!
#include<glfw3.h>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc\type_ptr.hpp>



class Shader {

public:

	Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile = "");

	~Shader();

	//Set uniform functions
	void use();

	void unuse();

	void set1i(GLint value, const GLchar* name);

	void set1f(GLfloat value, const GLchar* name);

	void setVec2f(glm::fvec2 value, const GLchar* name);

	void setVec3f(glm::fvec3 value, const GLchar* name);

	void setVec4f(glm::fvec4 value, const GLchar* name);

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);

	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);


private:
	GLuint id;

	std::string loadShaderSource(const char* fileName);

	GLuint loadShader(GLenum type, const char* fileName);

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);
};