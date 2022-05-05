#include"libs.h"

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void updateInput(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

bool loadShaders(GLuint &program) {
	bool load_success = true;
	char infolog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";
	std::ifstream in_file;
	//vertex
	in_file.open("vertex_core.glsl");
	if (in_file.is_open()) {
		while (std::getline(in_file, temp)) {
			src += temp + '\n';
		}
	}
	else {
		load_success = false;
		std::cout << "ERROR::LODSHADERS::COULD_NOT_OPEN_VERTEX_FILE" << '\n';
	}
	in_file.close();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		load_success = false;
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "ERROR::LODSHADERS::COULD_NOT_COMPILE_VERTEX_SHADER" << '\n';
		std::cout << infolog << '\n';
	}
	temp = "";
	src = "";

	//Fragment
	in_file.open("fragment_core.glsl");
	if (in_file.is_open()) {
		while (std::getline(in_file, temp)) {
			src += temp + '\n';
		}
	}
	else {
		load_success = false;
		std::cout << "ERROR::LODSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << '\n';
	}
	in_file.close();
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		load_success = false;
		std::cout << "ERROR::LODSHADERS::COULD_NOT_COMPILE_FRAGMENT_SHADER" << '\n';
		std::cout << infolog << '\n';
	}
	//Program
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infolog);
		load_success = false;
		std::cout << "ERROR::LODSHADERS::COULD_NOT_LINK_PROGRAM" << '\n';
		std::cout << infolog << '\n';
	}

	//End
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return load_success;

}

int main() {
	//INIT GLFW
	glfwInit();

	//CREATE WINDOW
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE) // for MAC OS
	

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"LABIRYNTH",NULL,NULL);

	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	//glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(window); //important for glew

	//INIT GLEW (needs window)
	glewExperimental = GL_TRUE; //enable modern openGL
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::MAIN>CPP::GLEW_INIT_FAILED" << '\n';
		glfwTerminate();
	}

	//OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	//SHADER INIT

	GLuint core_program;
	if (!loadShaders(core_program)) {
		glfwTerminate();
	}



	//MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
		//UPDATE INPUT
		glfwPollEvents();

		//UPDATE
		updateInput(window);
		//DRAW
		//CLEAR
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
		//DRAW
		//END DRAW
		glfwSwapBuffers(window);
		glFlush();
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();

	//Delete program
	glDeleteProgram(core_program);
	return 0;
}