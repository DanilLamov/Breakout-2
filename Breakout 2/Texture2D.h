#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <string>
#include <map>

class Texture2D {
public:
	//консттруктор по умолчанию
	Texture2D() = delete;
	//конструктор
	Texture2D(const GLuint& width, const GLuint& height, const unsigned char* data,
		const unsigned int& channels = 4, const GLenum& filter = GL_LINEAR, const GLenum& wrapMode = GL_CLAMP_TO_EDGE);
	//деструктор
	~Texture2D();
	//конструктор копирования
	Texture2D(const Texture2D&) = delete;
	//конструктор присваивания
	Texture2D& operator = (const Texture2D&) = delete;
	//конструктор пермещения
	Texture2D(Texture2D&&) noexcept;
	//конструктор присвааивания перемещением
	Texture2D& operator = (Texture2D&&) noexcept;

	//возвращает ширину
	unsigned getWidth() const;
	//возвращает высоту
	unsigned getHeight() const;

	//подключает тектсуру
	void bind() const;

private:
	GLuint ID;
	GLenum mode;
	unsigned int width, height;

};

#endif