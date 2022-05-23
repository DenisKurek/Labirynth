#include "Material.hpp"

Material::Material(
	glm::vec3 ambient,
	glm::vec3 diffuse,
	glm::vec3 specular,
	GLint diffuseTex,
	GLint specularTex
) : ambient(ambient), diffuse(diffuse), specular(specular),
	diffuseTex(diffuseTex), specularTex(specularTex) {}

void Material::sendToShader(Shader& program) {
	program.setVec3f(this->ambient, "material.ambient");
	program.setVec3f(this->diffuse, "material.diffuse");
	program.setVec3f(this->specular, "material.specular");
	program.set1i(this->diffuseTex, "material.diffuseTex");
	program.set1i(this->specularTex, "material.specularTex");
}
