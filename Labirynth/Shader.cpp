#include "Shader.hpp"

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath) {
	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;

	vertexShader = loadShader(GL_VERTEX_SHADER, vertexFilePath);
	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFilePath);

	this->linkProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(this->id);
}

void Shader::use() {
	glUseProgram(this->id);
}

void Shader::unuse() {
	glUseProgram(0);
}

void Shader::set1i(GLint value, const GLchar* name) {
	this->use();
	glUniform1i(glGetUniformLocation(this->id, name), value);
	this->unuse();
}

void Shader::set1f(GLfloat value, const GLchar* name) {
	this->use();
	glUniform1f(glGetUniformLocation(this->id, name), value);
	this->unuse();
}

void Shader::setVec2f(glm::fvec2 value, const GLchar* name) {
	this->use();
	glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
	this->unuse();
}

void Shader::setVec3f(glm::fvec3 value, const GLchar* name) {
	this->use();
	glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
	this->unuse();
}

void Shader::setVec4f(glm::fvec4 value, const GLchar* name) {
	this->use();
	glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
	this->unuse();
}

void Shader::setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose) {
	this->use();
	glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
	this->unuse();
}

void Shader::setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose) {
	this->use();
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
	this->unuse();
}

std::string Shader::readShaderSource(const char* filePath) {
	std::ifstream inFile;
	std::string src = "";
	std::string line = "";

	inFile.open(filePath);

	if (inFile.is_open()) {
		while (std::getline(inFile, line)) {
			src += line + '\n';
		}
	} else {
		std::cerr << "ERROR::SHADER::COULD_NOT_OPEN_FILE " << filePath << '\n';
	}
	inFile.close();

	return src;
}

GLuint Shader::loadShader(GLenum type, const char* filePath) {
	char infolog[512];
	GLint success;

	GLuint shader = glCreateShader(type);

	std::string strSrc = this->readShaderSource(filePath);
	const GLchar* src = strSrc.c_str();

	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infolog);
		std::cerr << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER " << filePath << '\n';
		std::cerr << infolog << '\n';
	}

	return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
	char infolog[512];
	GLint success;

	this->id = glCreateProgram();

	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragmentShader);

	glLinkProgram(this->id);

	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->id, 512, NULL, infolog);
		std::cerr << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << '\n';
		std::cerr << infolog << '\n';
	}

	glUseProgram(0);
}
