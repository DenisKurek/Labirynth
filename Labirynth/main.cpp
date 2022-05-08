#include"libs.h"

Vertex vertices[] = {
	//position						//color							//Texcoords				//Normals
	glm::vec3(-0.5f,0.5f,0.f),		glm::vec3(1.f,0.f,0.f),			glm::vec2(0.f,1.f),		glm::vec3(0.f,0.f,1.f),
	glm::vec3(-0.5f,-0.5f,0.f),		glm::vec3(0.f,1.f,0.f),			glm::vec2(0.f,0.f),		glm::vec3(0.f,0.f,1.f),
	glm::vec3(0.5f,-0.5f,0.f),		glm::vec3(0.f,0.f,1.f),			glm::vec2(1.f,0.f),		glm::vec3(0.f,0.f,1.f),
	glm::vec3(0.5f,0.5f,0.f),		glm::vec3(0.f,1.f,0.f),			glm::vec2(1.f,1.f),		glm::vec3(0.f,0.f,1.f)
};
unsigned nrOFVertices = sizeof(vertices) / sizeof(Vertex); // does not work on pointers

GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint); // does not work on pointers

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void updateInput(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}


void updateInput(GLFWwindow* window,Mesh &mesh) {
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

	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
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
	Shader core_program("vertex_core.glsl", "fragment_core.glsl");

	//MODEL
	Primitive* tmp = new Triangle();
	Mesh mesh(tmp);
	delete tmp;

	//TEXTURE INIT

	Texture texture0("images/smiley_face.png", GL_TEXTURE_2D,0);
	Texture texture1("images/container.png", GL_TEXTURE_2D,1);

	//MATERIAL 0
	Material material0(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture0.getTextureUnit(), texture1.getTextureUnit());

	//INIT MATRICIES works right to left
	glm::vec3 position(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);

	glm::vec3 camPosition(0.f,0.f,1.f);
	glm::vec3 worldUp(0.f,1.f,0.f);
	glm::vec3 camFront(0.f,0.f,-1.f);
	glm::mat4 ViewMatrix(1.f); //its important to initialize it
	ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 100.f;
	glm::mat4 ProjectionMatrix(1.f);
	ProjectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float>(framebufferWidth)/framebufferHeight,
		nearPlane,
		farPlane
	);

	//LIGHTS
	glm::vec3 lightPos0(0.f, 0.f, 1.f);

	//INIT UNIFORMS
	core_program.setMat4fv(ViewMatrix, "ViewMatrix");
	core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	core_program.setVec3f(lightPos0,"lightPos0");
	core_program.setVec3f(camPosition,"camPosition");

	//MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
		//UPDATE INPUT
		glfwPollEvents();
		updateInput(window, mesh);

		//UPDATE
		updateInput(window);
		//DRAW
		//CLEAR
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		material0.sendToShader(core_program);

		//Update frame buffer size
		glfwGetFramebufferSize(window,&framebufferWidth,&framebufferHeight);
		ProjectionMatrix = glm::mat4(1.f);
		ProjectionMatrix = glm::perspective(
			glm::radians(fov),
			static_cast<float>(framebufferWidth) / framebufferHeight,
			nearPlane,
			farPlane
		);

		core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

		//Use a program
		core_program.use();

		//Activate texture
		texture0.bind();
		texture1.bind();

		//Draw
		mesh.render(&core_program);

		//END DRAW
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		texture0.unbind();
		texture0.unbind();
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}