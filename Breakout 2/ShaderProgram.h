#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
public:
	//конструктор по умолчанию
	ShaderProgram() = delete;
	//конструктор
	ShaderProgram(const std::string&, const std::string&);
	//деструктор
	~ShaderProgram();

	//конструктор копирования
	ShaderProgram(ShaderProgram&) = delete;
	//конструктор присваивания
	ShaderProgram& operator = (const ShaderProgram&) = delete;
	//конуструкто перемещения
	ShaderProgram(ShaderProgram&&) noexcept;
	//конструкто присваивания перемещением
	ShaderProgram& operator = (ShaderProgram&&) noexcept;

	//активирует шейдерную программму
	void use() const;
	//установка значения юниформ переменной типа int
	void setInt(const std::string& name, const GLint& value);
	//установка значения юниформ переменной типа vec2 переменной типа vec2
	void setVec2(const std::string& name, const glm::vec2& value);
	//установка значения юниформ переменной типа vec2 двумя переменными типа float
	void setVec2(const std::string& name, const float& x, const float& y);
	//установка значения юниформ переменной типа vec3 переменной типа vec3
	void setVec3(const std::string& name, const glm::vec3& value);
	//установка значения юниформ переменной типа vec3 тремя переменными типа float
	void setVec3(const std::string& name, const float& x, const float& y, const float& z);
	//установка значения юниформ переменной типа vec4 переменной типа vec4
	void setVec4(const std::string& name, const glm::vec4& value);
	//установка значения юниформ переменной типа vec4 четырьмя переменными типа float
	void setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w);
	//установка значения юниформ переменной типа mat4
	void setMatrix4(const std::string& name, const glm::mat4& matrix);
	

private:
	GLuint ID = 0;

};

#endif