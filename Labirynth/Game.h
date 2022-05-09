#pragma once

#include "libs.h"

enum shader_enum {SHADER_CORE_PROGRAM =0};
enum texture_enum {TEX_FACE = 0, TEX_FACE_SPECULAR,
	TEX_CONTAINER, TEX_CONTAINER_SPECULAR};
enum material_enum {MAT_1 = 0};
enum mesh_enum {MESH_QUAD = 0};

class Game {
public:
	//Variables
	Camera camera;
		//Window
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	//OpenGL Context
	const int GL_VERSION_MAJOR = 4;
	const int GL_VERSION_MAINOR = 4;

	//Matrices
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;
	float fov;
	float nearPlane;
	float farPlane;

	//Shaders
	std::vector<Shader*> shaders;

	//Textures
	std::vector<Texture*> textures;

	//Materials
	std::vector<Material*> materials;

	//Meshes
	std::vector<Mesh*> meshes;

	//Models
	std::vector<Model*> models;

	//Lights
	std::vector<PointLight*> pointLights;



	//Constructors and Destructors
	Game(
		const char* title,
		const int width, const int height,
		bool resizable
	);

	virtual ~Game();

	//Accessors
	int getWindowShouldClose();

	//Modifiers
	void setWindowShouldclose();

	//Functions

	void update();
	void updateDt();
	void updateMouseinput();
	void updateKeyboardInput();
	void updateInput();
	void render();

	static void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

private:
	//Variables
	// 
	//Delta time
	float dt;
	float curTime;
	float lastTime;

	//Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	//Static Variables

	//Functions
	void initGLFW();
	void initWindow(const char* title, bool resizable);
	void initGLEW();//AFTER CONTEXT CREATION
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();
	void initMeshes();
	void initModels();
	void initPointLights();
	void initLights();
	void initUniforms();

	void updateUniforms();
};

