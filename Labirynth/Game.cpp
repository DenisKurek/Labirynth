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
	//std::cout << this->camera.getPosition().x << " " << this->camera.getPosition().z << std::endl;
	//this->meshes[1]->showPosition();
	this->collisionDetector();
	this->updateDt();
	this->updateInput();
}

void Game::collisionDetector() {
	float x = this->camera.getPosition().x;
	float z = this->camera.getPosition().z;
	int maze_size = 20;
	int i = (-4 + this->camera.getPosition().x )/ -8;
	int j = ( 4 + this->camera.getPosition().z )/  8;
			int block = i * maze_size + j;
			bool exR = this->maze.getWall(i, j, 'R'); // U R L D
			bool exL = this->maze.getWall(i, j, 'L'); // U R L D
			bool exU = this->maze.getWall(i, j, 'U'); // U R L D
			bool exD = this->maze.getWall(i, j, 'D'); // U R L D
			//std::cout << i << "  " << j << std::endl;
			if ((z ) > (meshes[block]->Position().z + 3.5)
				&& (z ) <= (meshes[block]->Position().z + 4.15)
				&& exR
				) {
				camera.setPosition(glm::vec3(this->camera.getPosition().x, 0, meshes[block]->Position().z + 3.5f));
				//std::cout << "kolizja R" << exR << std::endl;
				//this->kolizja = 1;

			}
			if ((z ) < (meshes[block]->Position().z - 3.5)
				&& (z ) >= (meshes[block]->Position().z - 4.15)
				&& exL
				) {
				camera.setPosition(glm::vec3(this->camera.getPosition().x, 0, meshes[block]->Position().z - 3.5f));
				//std::cout << "kolizja L" << exL << std::endl;
				//this->kolizja = 1;
			}
			if ((x ) > (meshes[block]->Position().x + 3.5)
				&& (x) <= (meshes[block]->Position().x + 4.15)
				&& exU
				) {
				camera.setPosition(glm::vec3(meshes[block]->Position().x + 3.5f, 0, this->camera.getPosition().z));
				//std::cout << "kolizja U" << exU << std::endl;
				//this->kolizja = 1;
			}
			if ((x ) < (meshes[block]->Position().x - 3.5)
				&& (x ) >= (meshes[block]->Position().x - 4.15)
				&& exD
				) {
				camera.setPosition(glm::vec3(meshes[block]->Position().x - 3.5f, 0, this->camera.getPosition().z));
				//std::cout << "kolizja B" << exD << std::endl;
				//this->kolizja = 1;
			}
			//prawy g�rny
			if ( x > meshes[block]->Position().x + 3.5 && z > meshes[block]->Position().z + 3.5) {
				camera.setPosition(glm::vec3(meshes[block]->Position().x + 3.5, 0, meshes[block]->Position().z + 3.3));
			}
			//prawy dolny
			if ( x < meshes[block]->Position().x - 3.5 && z > meshes[block]->Position().z + 3.5) {
				camera.setPosition(glm::vec3(meshes[block]->Position().x - 3.5, 0, meshes[block]->Position().z + 3.3));
			}
			//lewy g�rny
			if ( x > meshes[block]->Position().x + 3.5 && z < meshes[block]->Position().z - 3.5) {
				camera.setPosition(glm::vec3(meshes[block]->Position().x + 3.5, 0, meshes[block]->Position().z - 3.3));
			}
			//lewy dolny
			if (x < meshes[block]->Position().x - 3.5 && z < meshes[block]->Position().z - 3.5) {
				camera.setPosition(glm::vec3(meshes[block]->Position().x - 3.5, 0, meshes[block]->Position().z - 3.3));
			}
}


void Game::updateDt(){
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void Game::updateMouseinput(){

	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	//Calc offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;

	//Set last X and Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;

	this->pointLights[0]->setPosition(this->camera.getPosition());
	

}

void Game::updateKeyboardInput(){
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		this->setWindowShouldclose();
	}

	//Camera
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS )
	{
		this->camera.move(this->dt, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera.move(this->dt, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera.move(this->dt, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera.move(this->dt, RIGHT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	
}

void Game::updateInput(){
	glfwPollEvents();
	this->updateKeyboardInput();
	this->updateMouseinput();
	this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);

}

void Game::render() {
	//DRAW
	//CLEAR
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	this->updateUniforms();

	//Render models
	for (auto& i : this->models)
		i->render(this->shaders[SHADER_CORE_PROGRAM]);

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
) : WINDOW_WIDTH(width), WINDOW_HEIGHT(height),
	camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f)) {
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
	this->initWindow(title, resizable);
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
	for (size_t i = 0; i < this->pointLights.size(); i++)
					delete this->pointLights[i];
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
	glFrontFace(GL_CW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatrices(){

	//this->ViewMatrix = glm::mat4(2.f);
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
	//face
	this->textures.push_back(new Texture("images/smiley_face.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("images/smiley_face_specular.png", GL_TEXTURE_2D));

	//container
	this->textures.push_back(new Texture("images/container.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("images/container_specular.png", GL_TEXTURE_2D));
}

void Game::initMaterials(){
	this->materials.push_back( new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),0, 1));
}

GLuint walls[5][6] =
{
	//right
	{0, 1, 2, 0, 2, 3},
	
	//back
	{7, 6, 1, 7, 1, 0},

	//left
	{4, 5, 6, 4, 6, 7},

	//up
	{3, 2, 5, 3, 5, 4},

	{1, 6, 5, 1, 5, 2}
};

Vertex wallVertices[] = {
	//Position								//Color							//Texcoords					//Normals
	glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

	glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)
};
unsigned nrOfWallVertices = sizeof(wallVertices) / sizeof(Vertex);

void Game::initMeshes(){

	constexpr int ROOM_SIZE = 8.f;

	for(int i=0;i<20;i++){
		for (int j = 0; j < 20; j++) {
			std::vector<GLuint>indices;
			for (int point = 0; point < 6; point++) {
				if (maze.getWall(i, j, 'L')) {
					indices.push_back(walls[2][point]);
				}
			}
			for (int point = 0; point < 6; point++) {
				if (maze.getWall(i, j, 'R')) {
					indices.push_back(walls[0][point]);
				}
			}
			for (int point = 0; point < 6; point++) {
				if (maze.getWall(i, j, 'U')) {
					indices.push_back(walls[3][point]);
				}
			}
			for (int point = 0; point < 6; point++) {
				if (maze.getWall(i, j, 'D')) {
					indices.push_back(walls[1][point]);
				}
			}
			for (int point = 0; point < 6; point++) {
				indices.push_back(walls[4][point]);
			}
			
			this->meshes.push_back(new Mesh(wallVertices,nrOfWallVertices,indices.data(),indices.size(),
				glm::vec3(-i*ROOM_SIZE,0,j*ROOM_SIZE),glm::vec3(0), glm::vec3(0), glm::vec3(ROOM_SIZE)));
		}
	}
}

void Game::initModels(){
	this->models.push_back(new Model(
		glm::vec3(0.f),
		this->materials[0],
		this->textures[TEX_CONTAINER],
		this->textures[TEX_CONTAINER_SPECULAR],
		this->meshes
	)
	);

}

void Game::initPointLights()
{
	this->pointLights.push_back(new PointLight(glm::vec3(0.f)));
}

void Game::initLights()
{
	this->initPointLights();
}

void Game::initUniforms(){
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");

	for (PointLight* pl : this->pointLights)
	{
		pl->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
	}

}

void Game::updateUniforms(){

	//Update camera
	this->ViewMatrix = this->camera.getViewMatrix();

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

	for (PointLight * pl : this->pointLights)
	{
		pl->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
	}


	//Update frame buffer size
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");

}
