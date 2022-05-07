#include"libs.h"

Vertex vertices[] = {
	//position						//color							//Texcoords				//Normals
	glm::vec3(-0.5f,0.5f,0.f),		glm::vec3(1.f,0.f,0.f),			glm::vec2(0.f,1.f),		glm::vec3(0.f,0.f,-1.f),
	glm::vec3(-0.5f,-0.5f,0.f),		glm::vec3(0.f,1.f,0.f),			glm::vec2(0.f,0.f),		glm::vec3(0.f,0.f,-1.f),
	glm::vec3(0.5f,-0.5f,0.f),		glm::vec3(0.f,0.f,1.f),			glm::vec2(1.f,0.f),		glm::vec3(0.f,0.f,-1.f),
	glm::vec3(0.5f,0.5f,0.f),		glm::vec3(0.f,1.f,0.f),			glm::vec2(1.f,1.f),		glm::vec3(0.f,0.f,-1.f)
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

void updateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position.z -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position.z += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position.x -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position.x += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		rotation.y -= 1.f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		rotation.y += 1.f;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		scale -= 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		scale += 0.1f;
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

	//VAO
	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //use dynamic_draw if you want to change it often
	//EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//INPUT ASSEMBLY
	//GLuint attribloc = glGetAttribLocation(core_program, "vertex_position");
	//Poaition
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex,position));
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	//Texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	//unbind
	glBindVertexArray(0);

	//TEXTURE INIT
	int image_width = 0;
	int image_height = 0;
	unsigned char* image = SOIL_load_image("images/2.png",&image_width,&image_height,NULL,SOIL_LOAD_RGBA);

	GLuint texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image) {
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image_width,image_height,0,GL_RGBA,GL_UNSIGNED_BYTE,image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR::TEXTURE_LOADING_FAILED" << "\n";
	}
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image); //remove data (important)!!

	//INIT MATRICIES works right to left
	glm::vec3 position(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);


	glm::mat4 ModelMatrix(1.f);
	ModelMatrix = glm::translate(ModelMatrix,position);
	ModelMatrix = glm::rotate(ModelMatrix,glm::radians(rotation.x),glm::vec3(1.f,0.f,0.f));
	ModelMatrix = glm::rotate(ModelMatrix,glm::radians(rotation.y),glm::vec3(0.f,1.f,0.f));
	ModelMatrix = glm::rotate(ModelMatrix,glm::radians(rotation.z),glm::vec3(0.f,0.f,1.f));
	ModelMatrix = glm::scale(ModelMatrix,scale);

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
	core_program.setMat4fv(ModelMatrix, "ModelMatrix");
	core_program.setMat4fv(ViewMatrix, "ViewMatrix");
	core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	core_program.setVec3f(lightPos0,"lightPos0");
	core_program.setVec3f(camPosition,"camPosition");

	//MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
		//UPDATE INPUT
		glfwPollEvents();
		updateInput(window, position, rotation, scale);

		//UPDATE
		updateInput(window);
		//DRAW
		//CLEAR
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);


		//Update uniform
		core_program.set1i(0, "texture0");

		//move rotate and scale
		ModelMatrix = glm::mat4(1.f);
		ModelMatrix = glm::translate(ModelMatrix, position);
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		ModelMatrix = glm::scale(ModelMatrix, scale);

		core_program.setMat4fv(ModelMatrix, "ModelMatrix");
		
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
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);

		//bind vertex array
		glBindVertexArray(VAO);

		//DRAW
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);
		//END DRAW
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}