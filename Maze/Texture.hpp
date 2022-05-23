#pragma once

#include <glew.h>
#include <SOIL2.h>

#include <iostream>

/**
 * Class designed to be used to create various textures.
 */
class Texture {
private:
	GLuint id;
	GLint textureUnit;

	int width;
	int height;
	unsigned int type;

public:
	/**
	 * The constructor that loads a particular texture from the
	 *     specified file and makes it ready to be used.
	 * @param filePath A file path from which the texture is to be loaded.
	 * @param type A predefined type of the texture.
	 * @note On failure, prints more details to the standard error output.
	 */
	Texture(const char* filePath, GLenum type);

	/**
	 * The destructor that deletes the texture that is no longer needed.
	 */
	~Texture();

	/**
	 * Gets and returns the loaded texture ID.
	 * @return The loaded texture ID.
	 */
	GLuint getID() const;

	/**
	 * Gets and returns the texture unit to which the texture is currently bound.
	 * @return The texture unit to which the texture is currently bound.
	 */
	GLuint getTextureUnit() const;

	/**
	 * Loads a particular texture from the specified file.
	 * @param filePath A file path from which the texture is to be loaded.
	 * @note On failure, prints more details to the standard error output.
	 */
	void loadFromFile(const char* filePath);

	/**
	 * Binds the texture that belongs to the Texture object, on which this
	 *     method has been invoked, to the specified texture unit.
	 * @param textureUnit A texture unit ID to which this texture is to be bound.
	 */
	void bind(const GLint textureUnit);

	/**
	 * Unbinds the texture that belongs to the Texture object, on which this
	 *     method has been invoked, from the texture unit it is currently bound to.
	 */
	void unbind();
};
