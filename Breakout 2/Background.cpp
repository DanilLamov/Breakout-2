#include "Background.h"

const char* vertexShaderSource =
"#version 330 core\n"

"layout(location = 0) in vec2 position;"
"layout(location = 1) in vec2 textureCoord;"

"out vec2 TexCoord;"

"void main() {"
	"gl_Position = vec4(position, 0., 1.);"
	"TexCoord = textureCoord;"
"}";


const char* fragmentShaderSource =
"#version 330 core\n"

"in vec2 TexCoord;"

"out vec4 FragColor;"

"uniform sampler2D texture;"

"void main() {"
	"FragColor = texture(texture, TexCoord);"
"}";

Background::Background(std::shared_ptr<Texture2D> texture)
	: texture(texture), shaderProgram(std::make_shared<ShaderProgram>(vertexShaderSource, fragmentShaderSource)) {
	// ”казание вершин (и буфера(ов)) и настройка вершинных атрибутов
	float vertices[] = {
		//координаты    //текстурные координаты
		 1.f,  1.f,     1.f, 1.f, // верхн€€ права€ вершина
		 1.f, -1.f,     1.f, .0f, // нижн€€ права€ вершина
		-1.f, -1.f,     .0f, .0f, // нижн€€ лева€ вершина
		-1.f,  1.f,     .0f, 1.f  // верхн€€ лева€ вершина 
	};

	unsigned int indices[] = {
		0, 1, 3, // первый треугольник
		1, 2, 3  // второй треугольник
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//  оординатные атрибуты
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// јтрибуты текстурных координат
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

Background::~Background() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

Background::Background(Background&& background) noexcept
	: shaderProgram(background.shaderProgram), texture(background.texture), VAO(background.VAO), VBO(background.VBO), EBO(background.EBO) {}

Background& Background::operator = (Background& background) noexcept {
	shaderProgram = background.shaderProgram;
	texture = background.texture;
	VAO = background.VAO;
	VBO = background.VBO;
	EBO = background.EBO;

	texture = nullptr;
	shaderProgram = nullptr;
	VAO = VBO = EBO = 0;

	return *this;
}

void Background::draw() {
	glActiveTexture(GL_TEXTURE0);
	texture->bind();
	shaderProgram->use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}