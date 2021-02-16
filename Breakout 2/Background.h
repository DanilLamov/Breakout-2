#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <memory>

#include "Texture2D.h"
#include "ShaderProgram.h"

class Background {
public:
	Background() = delete;
	Background(std::shared_ptr<Texture2D> texture);
	~Background();

	//����������� �����������
	Background(const Background&) = delete;
	//����������� ������������
	Background& operator = (const Background&) = delete;
	//����������� �����������
	Background(Background&&) noexcept;
	//����������� ������������� ������������
	Background& operator = (Background&) noexcept;

	void draw();

private:
	std::shared_ptr<ShaderProgram> shaderProgram;
	std::shared_ptr<Texture2D> texture;

	GLuint VAO, VBO, EBO;

};

#endif