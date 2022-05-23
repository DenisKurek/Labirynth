#include "Model.hpp"

Model::Model(
	glm::vec3 position,
	std::vector<Mesh*> meshes,
	Material* material,
	Texture* orTexDif,
	Texture* orTexSpec
) : position(position), material(material),
	overrideTextureDiffuse(orTexDif), overrideTextureSpecular(orTexSpec) {

	for (auto* i : meshes) {
		this->meshes.push_back(new Mesh(*i));
	}

	for (auto& i : this->meshes) {
		i->move(this->position);
		i->setOrigin(this->position);
	}
}

Model::~Model() {
	for (auto*& i : this->meshes) {
		delete i;
	}
}

void Model::render(Shader* program) {
	this->material->sendToShader(*program);

	// Use a program
	program->use();

	// Activate texture
	this->overrideTextureDiffuse->bind(0);
	this->overrideTextureSpecular->bind(1);

	// Draw
	for (auto& i : this->meshes) {
		i->render(program);
	}
}
