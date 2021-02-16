#include "Sprite.h"

//вспомогательна€ функци€ дл€ инициализации и настройки атрибутов буфера и атрибутов вершин
void initRenderData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) {
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

Sprite::Sprite(std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Texture2D> texture) 
    : shaderProgram(shaderProgram), texture(texture) {
    initRenderData(VAO, VBO, EBO);
}

Sprite::~Sprite() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

Sprite::Sprite(Sprite&& sprite) noexcept 
    : shaderProgram(sprite.shaderProgram), texture(sprite.texture), VAO(sprite.VAO), VBO(sprite.VBO), EBO(sprite.EBO) {}

Sprite& Sprite::operator = (Sprite& sprite) noexcept {
    shaderProgram = sprite.shaderProgram;
    texture = sprite.texture;
    VAO = sprite.VAO;
    VBO = sprite.VBO;
    EBO = sprite.EBO;

    texture = nullptr;
    shaderProgram = nullptr;
    VAO = VBO = EBO = 0;

    return *this;
}

void Sprite::draw(const glm::vec2& position, const glm::vec2& size, const float& rotate) {
    //glActiveTexture(GL_TEXTURE0);
    //texture->bind();

    // ѕодготовка преобразований
    shaderProgram->use();
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, .0f));
    //перемещаем точку начала поворота в центр пр€моугольника
    //model = glm::translate(model, glm::vec3(.5f * size.x, .5f * size.y, .0f));
    //производим поворот
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    //возвращаем точку поворота в исходную позицию
    //model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    //выполн€ем масштабирование
    model = glm::scale(model, glm::vec3(size, 1.f));

    shaderProgram->setMatrix4("model", model);

    //рендерим текстурированный пр€моугольник
    glActiveTexture(GL_TEXTURE0);
    texture->bind();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}