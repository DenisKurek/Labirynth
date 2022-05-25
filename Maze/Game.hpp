#pragma once

#include "Camera.hpp"
#include "Material.hpp"
#include "MazeGenerator.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Light.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"

#include <glew.h> // Before glfw3.h
#include <glfw3.h>
#include <glm.hpp>

#include <vector>

enum ShaderEnum;
enum TextureEnum;

/**
 * The main class of the entire game.
 */
class Game {
private:
	static constexpr int GL_VERSION_MAJOR = 4;
	static constexpr int GL_VERSION_MAINOR = 4;

	static constexpr unsigned WALL_VERTICES_NO = 12;

	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;

	static GLuint walls[5][6];
	static Vertex wallVertices[WALL_VERTICES_NO];

	Camera camera;
	GLFWwindow* window;

	MazeGenerator maze;

	int framebufferWidth;
	int framebufferHeight;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	float fov;
	float nearPlane;
	float farPlane;

	std::vector<Shader*> shaders;
	std::vector<Texture*> textures;
	std::vector<Material*> materials;
	std::vector<Mesh*> meshes;
	std::vector<Model*> models;
	std::vector<Light*> lights;

	float dt;
	float curTime;
	float lastTime;

	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

public:
	/**
	 * The constructor that sets up a Game instance so that it is ready to be played.
	 * @param title The title that is to be displayed in the title bar of the game window.
	 * @param width The width of the window (in pixels).
	 * @param height The height of the window (in pixels).
	 * @param isResizable Specifies, whether the window should be resizable or now.
	 * @note On failure, prints more details to the standard error output, and then terminates the game.
	 */
	Game(const char* title, const int width, const int height, bool isResizable);

	/**
	 * The destructor that frees up dynamically allocated memory for the
	 *     game and makes sure all game windows are closed at this point.
	 */
	virtual ~Game();

	/**
	 * Gets and returns a hint whether the game window should be closed or not.
	 * @return A hint whether the game window should be closed or not.
	 */
	int getWindowShouldClose() const;

	/**
	 * Sets the hint whether the game window should be closed or not.
	 */
	void setWindowShouldclose();

	/**
	 * Callback that is designed to be used when the framebuffer of the game window is resized.
	 * @param window The handle of the game window.
	 * @param width The new width after the resize (in pixels).
	 * @param height The new height after the resize (in pixels).
	 */
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	/**
	 * Deals with detecting and reacting to collisions with objects in the world.
	 */
	void collisionDetector();

	/**
	 * Updates the game according to various player input events (e.g. mouse movement,
	 *     keyboard key presses, interactions with window controls, etc.).
	 */
	void update();

	/**
	 * Calculates the elapsed time since the last game update.
	 *
	 * Thanks to the delta time, the player's movement speed can always
	 *     be the same, regardless of how often the game is updated.
	 */
	void updateDt();

	/**
	 * Tracks the movement of the mouse and reacts to it.
	 */
	void updateMouseinput();

	/**
	 * Checks if keyboard key press events have been sent and if so, reacts to them.
	 */
	void updateKeyboardInput();

	/**
	 * Renders a frame and sends it to the OpenGL front buffer to be displayed in the game window.
	 */
	void render();

private:
	/**
	 * Initializes the GLFW library so that it is ready to be used.
	 * @note On failure, prints more details to the standard error output, and then terminates the game.
	 */
	void initGLFW();

	/**
	 * Initializes a window for the game.
	 * @param title The title that is to be displayed in the title bar of the window.
	 * @param isResizable Specifies, whether the window should be resizable or now.
	 * @note On failure, prints more details to the standard error output, and then terminates the game.
	 */
	void initWindow(const char* title, bool isResizable);

	/**
	 * Initializes the GLEW library so that it is ready to be used.
	 * @note On failure, prints more details to the standard error output, and then terminates the game.
	 */
	void initGLEW();

	/**
	 * Initializes a few important OpenGL rendering options.
	 */
	void initOpenGLOptions();

	/**
	 * Initializes both the view matrix and the projection matrix used in the game.
	 */
	void initMatrices();

	/**
	 * Initializes all shaders used in the game.
	 */
	void initShaders();

	/**
	 * Initializes all textures used in the game.
	 */
	void initTextures();

	/**
	 * Initializes all materials used in the game.
	 */
	void initMaterials();

	/**
	 * Initializes all meshes used in the game.
	 */
	void initMeshes();

	/**
	 * Initializes all models used in the game.
	 */
	void initModels();

	/**
	 * Initializes all light sources used in the game.
	 */
	void initLights();

	/**
	 * Initializes uniforms from the shaders that are used in the game.
	 */
	void initUniforms();

	/**
	 * Updates uniforms from the shaders that are used in the game.
	 */
	void updateUniforms();
};
