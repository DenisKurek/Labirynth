#pragma once
#include<iostream>
#include <string>

#include<glew.h> //before glfw3 !!
#include<glfw3.h>

#include<SOIL2.h>

class Texture {

public:
	Texture(const char* fileName, GLenum type);

	~Texture();

	GLuint getID() const ;

	void loadFromFile(const char* fileName);

	void bind(const GLint texture_unit);

	void unbind();

private:
	GLuint id;
	int width;
	int height;
	unsigned int type;

};
