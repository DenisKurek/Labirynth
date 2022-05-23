#pragma once

#include "Shader.hpp"

#include <glew.h>
#include <glm.hpp>

/**
 * Class designed to be used to create various materials
 *     (which may alter the light behavior on textures).
 */
class Material {
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLint diffuseTex;
	GLint specularTex;

public:
	/**
	 * The constructor that sets up a Material object and makes it ready to be used.
	 * @param ambient A vector with RGB values to specify the color of the ambient light.
	 * @param diffuse A vector with RGB values to specify the color of the diffuse light.
	 * @param specular A vector with RGB values to specify the color of the specular light.
	 * @param diffuseTex The texture unit to which the diffuse texture is currently bound.
	 * @param specularTex The texture unit to which the specular texture is currently bound.
	 */
	Material(
		glm::vec3 ambient,
		glm::vec3 diffuse,
		glm::vec3 specular,
		GLint diffuseTex,
		GLint specularTex
	);

	/**
	 * Sends material data to a bunch of uniforms in a particular shader program.
	 * @param program A shader program used to reference
	 *     uniforms to which the material data is to be send.
	 */
	void sendToShader(Shader& program);
};
