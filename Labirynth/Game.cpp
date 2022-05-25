#include "Game.hpp"

enum ShaderEnum {
	SHADER_CORE_PROGRAM = 0
};

enum TextureEnum {
	TEX_FACE = 0,
	TEX_FACE_SPECULAR,
	TEX_CONTAINER,
	TEX_CONTAINER_SPECULAR
};

GLuint Game::walls[5][6] = {
	// Right
	{0, 1, 2, 0, 2, 3},

	// Back
	{7, 6, 1, 7, 1, 0},

	// Left
	{4, 5, 6, 4, 6, 7},

	// Up
	{3, 2, 5, 3, 5, 4},

	// Floor 8,9, 10,
	{ 11,10,9,8,9, 10}
};

Vertex Game::wallVertices[WALL_VERTICES_NO] = {
	// Position							// Color						// Texture coords			// Normals
	glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f), //0
	glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f), //1
	glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f), //2
	glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f), //3

	glm::vec3(0.5f, 0.5f, -0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f), //4
	glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f), //5
	glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f), //6
	glm::vec3(-0.5f, 0.5f, -0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f), //7

	glm::vec3(-0.5f, -0.5f,0.5f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f), //8
	glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f), //9
	glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f), //10
	glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f)  //11
};

Game::Game(const char* title, const int width, const int height, bool isResizable)
	: WINDOW_WIDTH(width), WINDOW_HEIGHT(height), maze(MazeGenerator()),
	camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f)) {

	this->window = nullptr;
	this->framebufferWidth = width;
	this->framebufferHeight = height;

	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);
	this->viewMatrix = glm::mat4(1.f); // It is important to initialize this

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 100.f;

	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->mouseOffsetX = 0.0;
	this->mouseOffsetY = 0.0;
	this->firstMouse = true;

	this->initGLFW();
	this->initWindow(title, isResizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initMeshes();
	this->initModels();
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
	for (size_t i = 0; i < this->models.size(); i++) { delete this->models[i]; }
	for (size_t i = 0; i < this->lights.size(); i++) { delete this->lights[i]; }
}

int Game::getWindowShouldClose() const {
	return glfwWindowShouldClose(this->window);
}

void Game::setWindowShouldclose() {
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

void Game::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Game::collisionDetector() {
	float x = this->camera.getPosition().x;
	float z = this->camera.getPosition().z;

	int maze_size = maze.getSize();

	int i = (int)((-4 + this->camera.getPosition().x) / -8);
	int j = (int)((4 + this->camera.getPosition().z) / 8);

	int block = i * maze_size + j;

	bool exR = this->maze.getWall(i, j, WRIGHT); // U R L D
	bool exL = this->maze.getWall(i, j, WLEFT); // U R L D
	bool exU = this->maze.getWall(i, j, WUP); // U R L D
	bool exD = this->maze.getWall(i, j, WDOWN); // U R L D

	if ((z) > (meshes[block]->getPosition().z + 3.5)
		&& (z) <= (meshes[block]->getPosition().z + 4.15)
		&& exR
		) {
		camera.setPosition(glm::vec3(this->camera.getPosition().x, 0, meshes[block]->getPosition().z + 3.5f));
	}

	if ((z) < (meshes[block]->getPosition().z - 3.5)
		&& (z) >= (meshes[block]->getPosition().z - 4.15)
		&& exL
		) {
		camera.setPosition(glm::vec3(this->camera.getPosition().x, 0, meshes[block]->getPosition().z - 3.5f));
	}

	if ((x) > (meshes[block]->getPosition().x + 3.5)
		&& (x) <= (meshes[block]->getPosition().x + 4.15)
		&& exU
		) {
		camera.setPosition(glm::vec3(meshes[block]->getPosition().x + 3.5f, 0, this->camera.getPosition().z));
	}

	if ((x) < (meshes[block]->getPosition().x - 3.5)
		&& (x) >= (meshes[block]->getPosition().x - 4.15)
		&& exD
		) {
		camera.setPosition(glm::vec3(meshes[block]->getPosition().x - 3.5f, 0, this->camera.getPosition().z));
	}

	// Top right
	if (x > meshes[block]->getPosition().x + 3.5 && z > meshes[block]->getPosition().z + 3.5) {
		camera.setPosition(glm::vec3(meshes[block]->getPosition().x + 3.5, 0, meshes[block]->getPosition().z + 3.3));
	}

	// Bottom right
	if (x < meshes[block]->getPosition().x - 3.5 && z > meshes[block]->getPosition().z + 3.5) {
		camera.setPosition(glm::vec3(meshes[block]->getPosition().x - 3.5, 0, meshes[block]->getPosition().z + 3.3));
	}

	// Top left
	if (x > meshes[block]->getPosition().x + 3.5 && z < meshes[block]->getPosition().z - 3.5) {
		camera.setPosition(glm::vec3(meshes[block]->getPosition().x + 3.5, 0, meshes[block]->getPosition().z - 3.3));
	}

	// Bottom left
	if (x < meshes[block]->getPosition().x - 3.5 && z < meshes[block]->getPosition().z - 3.5) {
		camera.setPosition(glm::vec3(meshes[block]->getPosition().x - 3.5, 0, meshes[block]->getPosition().z - 3.3));
	}
}

void Game::update() {
	glfwPollEvents();

	this->collisionDetector();
	this->updateDt();

	this->updateKeyboardInput();
	this->updateMouseinput();
}

void Game::updateDt() {
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void Game::updateMouseinput() {
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse) {
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	// Calculate offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;

	this->camera.updateMouseInput(dt, this->mouseOffsetX, this->mouseOffsetY);

	// Set last X and Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;

	this->lights[0]->setPosition(glm::vec3(
		this->camera.getPosition().x,
		this->camera.getPosition().y,
		this->camera.getPosition().z + 1.f)
	);
}

void Game::updateKeyboardInput() {
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		this->setWindowShouldclose();
	}

	// Camera
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
		if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			this->camera.move(this->dt, FORWARD_RUN);
		} else {
			this->camera.move(this->dt, FORWARD);
		}
	}

	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {
		this->camera.move(this->dt, BACKWARD);
	}

	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
		this->camera.move(this->dt, LEFT);
	}

	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {
		this->camera.move(this->dt, RIGHT);
	}

	if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void Game::render() {
	// DRAW
	// CLEAR
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	this->updateUniforms();

	// Render models
	for (auto& i : this->models) {
		i->render(this->shaders[SHADER_CORE_PROGRAM]);
	}

	// END DRAW
	glfwSwapBuffers(this->window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::initGLFW() {
	if (glfwInit() == GLFW_FALSE) {
		std::cerr << "ERROR::GAME::GLFW_INIT_FAILED\n";
		glfwTerminate();
	}
}

void Game::initWindow(const char* title, bool isResizable) {
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MAINOR);
	glfwWindowHint(GLFW_RESIZABLE, isResizable);

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);
	if (this->window == nullptr) {
		std::cerr << "ERROR::GAME::GLFW_WINDOW_INIT_FAILED\n";
		glfwTerminate();
	}

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(this->window, Game::framebufferResizeCallback);

	glfwMakeContextCurrent(this->window); // Important for GLEW
}

void Game::initGLEW() {
	glewExperimental = GL_TRUE; // Enable modern OpenGL

	if (glewInit() != GLEW_OK) {
		std::cerr << "ERROR::GAME::GLEW_INIT_FAILED\n";
		glfwTerminate();
	}
}

void Game::initOpenGLOptions() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatrices() {
	this->viewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->projectionMatrix = glm::mat4(1.f);
	projectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);
}

void Game::initShaders() {
	this->shaders.push_back(new Shader("shaders/vertex_core.glsl", "shaders/fragment_core.glsl"));
}

void Game::initTextures() {
	// Face
	this->textures.push_back(new Texture("images/smiley_face.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("images/smiley_face_specular.png", GL_TEXTURE_2D));

	// Container
	this->textures.push_back(new Texture("images/container.png", GL_TEXTURE_2D));
	textures[TEX_CONTAINER]->bind(0);

	this->textures.push_back(new Texture("images/container_specular.png", GL_TEXTURE_2D));
	textures[TEX_CONTAINER_SPECULAR]->bind(0);
}

void Game::initMaterials() {
	this->materials.push_back(
		new Material(
			glm::vec3(0.1f),
			glm::vec3(1.f),
			glm::vec3(1.f),
			textures[TEX_CONTAINER]->getTextureUnit(),
			textures[TEX_CONTAINER_SPECULAR]->getTextureUnit()
		)
	);
}

void Game::initMeshes() {
	constexpr int ROOM_SIZE = 8;

	for (int i = 0; i < this->maze.getSize(); i++) {
		for (int j = 0; j < this->maze.getSize(); j++) {
			std::vector<GLuint>indices;
			for (int point = 0; point < 6; point++) {
				if (maze.getWall(i, j, WLEFT)) {
					indices.push_back(walls[2][point]);
				}
			}

			for (int point = 0; point < 6; point++) {
				if (maze.getWall(i, j, WRIGHT)) {
					indices.push_back(walls[0][point]);
				}
			}

			for (int point = 0; point < 6; point++) {
				if (maze.getWall(i, j, WUP)) {
					indices.push_back(walls[3][point]);
				}
			}

			for (int point = 0; point < 6; point++) {
				if (maze.getWall(i, j, WDOWN)) {
					indices.push_back(walls[1][point]);
				}
			}

			for (int point = 0; point < 6; point++) {
				indices.push_back(walls[4][point]);
			}

			this->meshes.push_back(new Mesh(
				WALL_VERTICES_NO,
				indices.size(),
				wallVertices,
				indices.data(),
				glm::vec3(-i * ROOM_SIZE, 0, j * ROOM_SIZE),
				glm::vec3(0), glm::vec3(0), glm::vec3(ROOM_SIZE)
			));
		}
	}
}

void Game::initModels() {
	this->models.push_back(new Model(
		glm::vec3(0.f),
		this->meshes,
		this->materials[0],
		this->textures[TEX_CONTAINER],
		this->textures[TEX_CONTAINER_SPECULAR]
	));
}

void Game::initLights() {
	this->lights.push_back(new Light(glm::vec3(0.f)));
}

void Game::initUniforms() {
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->viewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->projectionMatrix, "ProjectionMatrix");

	for (Light* light : this->lights) {
		light->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
	}
}

void Game::updateUniforms() {
	// Update camera
	this->viewMatrix = this->camera.getViewMatrix();

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->viewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

	for (Light* light : this->lights) {
		light->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
	}

	// Update frame buffer size
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	this->projectionMatrix = glm::mat4(1.f);
	this->projectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->projectionMatrix, "ProjectionMatrix");
}
