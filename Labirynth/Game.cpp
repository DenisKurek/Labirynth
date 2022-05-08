#include "Game.h"

	//Variables

	//Constructors and Destructors
	
	//Accessors
int Game::getWindowShouldClose() {
	return glfwWindowShouldClose(this->window);
}


	//Modifiers
void Game::setWindowShouldclose(){
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

	//Functions
void Game::update() {
	//UPDATE INPUT
	glfwPollEvents();

}

void Game::updateInput(GLFWwindow* window, Mesh& mesh) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.f, 0.f, -0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.f, 0.f, 0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		mesh.move(glm::vec3(-0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(0.f, -1.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(0.f, 1.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		mesh.scaleUp(glm::vec3(0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		mesh.scaleUp(glm::vec3(-0.01f));
	}
}

void Game::render() {
	updateInput(this->window,*this->meshes[MESH_QUAD]);

	//UPDATE
	updateInput(this->window);
	//DRAW
	//CLEAR
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	this->updateUniforms();

	this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

	//Use a program
	this->shaders[SHADER_CORE_PROGRAM]->use();

	//Activate texture
	this->textures[TEX_FACE]->bind(0);
	this->textures[TEX_CONTAINER]->bind(1);

	//Draw
	this->meshes[MESH_QUAD]->render(this->shaders[SHADER_CORE_PROGRAM]);

	//END DRAW
	glfwSwapBuffers(this->window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
	//Variables

	//Static Variables


Game::Game(
	const char* title,
	const int width, const int height,
	bool resizable
) : WINDOW_WIDTH(width), WINDOW_HEIGHT(height) {
	//Init variables
	this->window = nullptr;
	this->framebufferWidth = width;
	this->framebufferHeight = height;

	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);
	this->ViewMatrix = glm::mat4(1.f); //its important to initialize it
	
	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 100.f;

	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initMeshes();
	this->initLights();
	this->initUniforms();
}

Game::~Game() {
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++) { delete this->shaders[i]; }
	for (size_t i = 0; i < this->textures.size(); i++) { delete this->textures[i]; }
	for (size_t i = 0; i < this->materials.size(); i++) { delete this->materials[i]; }
	for (size_t i = 0; i < this->meshes.size(); i++) { delete this->meshes[i]; }
	for (size_t i = 0; i < this->lights.size(); i++) { delete this->lights[i]; }
}

//Private Functions
void Game::initGLFW() {
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "ERROR::GLFW_INIT_FAILED" << '\n';
		glfwTerminate();
	}
}

void Game::initWindow(const char* title,bool resizable){
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MAINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE) // for MAC OS


	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);
	if (this->window == nullptr) {
		std::cout << "ERROR::GLFW_WINDOW_INID_FAILED " << '\n';
		glfwTerminate();
	}
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(this->window, framebuffer_resize_callback);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(this->window); //important for glew

}

void Game::initGLEW() {
	glewExperimental = GL_TRUE; //enable modern openGL

	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << '\n';
		glfwTerminate();
	}
}

void Game::initOpenGLOptions(){

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Game::initMatrices(){

	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = glm::mat4(1.f);
	ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);

}

void Game::initShaders(){
	this ->shaders.push_back(new Shader("vertex_core.glsl", "fragment_core.glsl"));
}

void Game::initTextures(){
	this->textures.push_back(new Texture("images/smiley_face.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("images/container.png", GL_TEXTURE_2D));
}

void Game::initMaterials(){
	this->materials.push_back( new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),0, 1));
}

void Game::initMeshes(){
	Primitive* tmp = new Quad();
	this->meshes.push_back(new Mesh(tmp));
	delete tmp;
}

void Game::initLights() {
	this->lights.push_back( new glm::vec3(0.f, 0.f, 1.f));

}

void Game::initUniforms(){
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "camPosition");

}

void Game::updateUniforms(){
	//Update frame buffer size
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

}


