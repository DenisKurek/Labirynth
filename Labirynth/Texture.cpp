#include "Texture.hpp"

Texture::Texture(const char* filePath, GLenum type)
	: id(0), textureUnit(404), type(type) {

	this->loadFromFile(filePath);
}

Texture::~Texture() {
	glDeleteTextures(1, &this->id);
}

GLuint Texture::getID() const {
	return this->id;
}

GLuint Texture::getTextureUnit() const {
	return this->textureUnit;
}

void Texture::loadFromFile(const char* filePath) {
	if (this->id) {
		glDeleteTextures(1, &this->id);
	}

	unsigned char* image = SOIL_load_image(filePath, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

	glGenTextures(1, &this->id);
	glBindTexture(this->type, this->id);

	glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image) {
		glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(this->type);
	} else {
		std::cerr << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED: " << filePath << '\n';
	}

	glActiveTexture(0);
	glBindTexture(this->type, 0);
	SOIL_free_image_data(image);
}

void Texture::bind(const GLint textureUnit) {
	this->textureUnit = textureUnit;
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(this->type, this->id);
}

void Texture::unbind() {
	glActiveTexture(0);
	glBindTexture(this->type, 0);
}
