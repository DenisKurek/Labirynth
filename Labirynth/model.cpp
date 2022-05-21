#include"Model.h"

Model::Model(
	glm::vec3 position,
	Material* material,
	Texture* orTexDif,
	Texture* orTexSpec,
	std::vector<Mesh*>& meshes
	) {
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = orTexDif;
		this->overrideTextureSpecular = orTexSpec;

		for (auto* i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}

		for (auto& i : this->meshes)
		{
			i->move(this->position);
			i->setOrigin(this->position);
		}
}

Model::~Model(){
	for (auto*& i : this->meshes)
		delete i;
}


void Model::render(Shader* shader)
{
	this->material->sendToShader(*shader);

	//Use a program
	shader->use();

	//Activate texture
	this->overrideTextureDiffuse->bind(0);
	this->overrideTextureSpecular->bind(1);

	//Draw
	for (auto& i : this->meshes)
		i->render(shader);
}

