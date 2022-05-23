#pragma once

#include "Material.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include <glm.hpp>

#include <vector>

/**
 * Class designed to combine meshes, textures, and a material in a single model.
 */
class Model {
private:
	glm::vec3 position;
	std::vector<Mesh*> meshes;
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;

public:
	/**
	 * The constructor that sets up a Model object and makes it ready to be used and rendered.
	 * @param position A position of the model.
	 * @param meshes A vector containing meshes that are to be combined with other things.
	 * @param material A material that is to be combined with other things.
	 * @param orTexDif A diffuse texture that is to be combined with other things.
	 * @param orTexSpec A specular texture that is to be combined with other things.
	 */
	Model(
		glm::vec3 position,
		std::vector<Mesh*> meshes,
		Material* material,
		Texture* orTexDif,
		Texture* orTexSpec
	);

	/**
	 * The destructor that frees up dynamically allocated memory in a Model object.
	 */
	~Model();

	/**
	 * Renders the entile model that belongs to the Model object, on which
	 *     this method has been invoked, on the scene.
	 * @param program A shader program used to reference a bunch of uniforms.
	 */
	void render(Shader* program);
};
