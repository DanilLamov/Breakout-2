#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "ShaderProgram.h"

// Информация о состоянии символа, загруженному с помощью библиотеки FreeType
struct Character {
    unsigned int TextureID; // ID текстуры глифа
    glm::ivec2 Size; // размер глифа
    glm::ivec2 Bearing; // смещение от линии шрифта до верхнего левого угла глифа
    unsigned int Advance; // горизонтальное смещение для перехода к следующему глифу
};

// Класс TextRenderer предназначен для рендеринга текста, отображаемого шрифтом, 
// загруженным с помощью библиотеки FreeType. Загруженный шрифт обрабатывается и 
// сохраняется для последующего рендеринга в виде списка символов
class TextRenderer {
public:
    // Список предварительно скомпилированных символов
    std::map<char, Character> characters;
    // Шейдер, используемый для рендеринга текста
    ShaderProgram textShaderProgram;

    // Конструктор
    TextRenderer(unsigned int width, unsigned int height);

    // Список предварительно скомпилированных символов из заданного шрифта
    void load(std::string font, unsigned int fontSize);

    // Рендеринг строки текста с использованием предварительно скомпилированного списка символов
    void renderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
private:

    // Состояние рендеринга
    unsigned int VAO, VBO;
};

#endif