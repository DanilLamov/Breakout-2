#include "Texture2D.h"

Texture2D::Texture2D(const GLuint& width, const GLuint& height, const unsigned char* data,
	const unsigned int& channels, const GLenum& filter, const GLenum& wrapMode)
	: width(width), height(height) {
	switch (channels) {
	case 4:
		mode = GL_RGBA;
		break;

	case 3:
		mode = GL_RGB;
		break;

	default:
		mode = GL_RGBA;
		break;
	}

	glGenTextures(1, &ID);
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
	//загрузка данных в память видеокарты
	glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &ID);
}

Texture2D::Texture2D(Texture2D&& texture2d) noexcept
	: mode(texture2d.mode), height(texture2d.height), width(texture2d.width) {
	glDeleteTextures(1, &ID);

	ID = texture2d.ID;
	texture2d.ID = 0;
}

Texture2D& Texture2D::operator = (Texture2D&& texture2d) noexcept {
	glDeleteTextures(1, &ID);

	ID = texture2d.ID;
	texture2d.ID = 0;

	mode = texture2d.mode;
	width = texture2d.width;
	height = texture2d.height;

	return *this;
}

unsigned Texture2D::getWidth() const {
	return width;
}

unsigned Texture2D::getHeight() const {
	return height;
}

void Texture2D::bind() const {
	glBindTexture(GL_TEXTURE_2D, ID);
}