#include "ShaderProgram.h"

#include <iostream>

//вспомогательная функция для создания шейдера заданного типа
bool createShader(const std::string& shaderSource, const GLenum shaderType, GLuint& shaderID) {
	shaderID = glCreateShader(shaderType);
	const char* code = shaderSource.c_str();
	glShaderSource(shaderID, 1, &code, nullptr);
	glCompileShader(shaderID);

	//проверка ошибок
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
		std::cerr << "ERROR::SHADER: compile time error:" << std::endl
			<< infoLog << std::endl;
		return false;
	}

	return true;
}

ShaderProgram::ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
	//создание вертексного шейдера
	GLuint vertexShaderID;
	if (!createShader(vertexShaderSource, GL_VERTEX_SHADER, vertexShaderID)) {
		std::cerr << "VERTEX_SHADER compile time error" << std::endl;
		return;
	}

	//создание фрагментного шейдера
	GLuint fragmentShaderID;
	if (!createShader(fragmentShaderSource, GL_FRAGMENT_SHADER, fragmentShaderID)) {
		std::cerr << "FRAGMENT_SHADER compile time error" << std::endl;
		glDeleteShader(vertexShaderID);
		return;
	}

	//создание шейдернй программы
	ID = glCreateProgram();
	glAttachShader(ID, vertexShaderID);
	glAttachShader(ID, fragmentShaderID);
	glLinkProgram(ID);

	//проверка линковки на ошибки
	GLint success;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024];
		glGetShaderInfoLog(ID, 1024, nullptr, infoLog);
		std::cerr << "ERROR::SHADER_ROGRAM: Link time error:" << std::endl
			<< infoLog << std::endl;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(ID);
}

ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	: ID(shaderProgram.ID) {
	shaderProgram.ID = 0;
}

ShaderProgram& ShaderProgram::operator = (ShaderProgram&& shaderProgram) noexcept {
	glDeleteProgram(ID);
	ID = shaderProgram.ID;
	shaderProgram.ID = 0;

	return *this;
}

void ShaderProgram::use() const  {
	glUseProgram(ID);
}

void ShaderProgram::setInt(const std::string& name, const GLint& value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void ShaderProgram::setVec2(const std::string& name, const glm::vec2& value) {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec2(const std::string& name, const float& x, const float& y) {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &glm::vec2(x, y)[0]);
}
void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec3(const std::string& name, const float& x, const float& y, const float& z) {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &glm::vec3(x, y, z)[0]);
}
void ShaderProgram::setVec4(const std::string& name, const glm::vec4& value) {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w) {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &glm::vec4(x, y, z, w)[0]);
}
void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}