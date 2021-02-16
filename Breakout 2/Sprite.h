#ifndef SPRITE_H
#define SPRITE_H

#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.h"
#include "Texture2D.h"


class Sprite {
public:
    //конструктор по умолчанию
    Sprite() = delete;
    //конструктор
    Sprite(std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Texture2D> texture);
    //деструктор
    ~Sprite();
    //конструктор копирования
    Sprite(const Sprite&) = delete;
    //конструктор присваивания
    Sprite& operator = (const Sprite&) = delete;
    //конструктор перемещения
    Sprite(Sprite&&) noexcept;
    //конструктор присваиввания перемещением
    Sprite& operator = (Sprite&) noexcept;
     
    //рендерит текстурированный прямоугольник
    void draw(const glm::vec2& position, const glm::vec2& size = glm::vec2(10.0f, 10.0f), const float& rotate = 0.0f);

private:
    std::shared_ptr <ShaderProgram> shaderProgram;
    std::shared_ptr <Texture2D> texture;
    unsigned int VAO, VBO, EBO;

    // Инициализируем и настраиваем атрибуты буфера и атрибуты вершин
    //void initRenderData();
};

#endif