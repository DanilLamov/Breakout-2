#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "ShaderProgram.h"

// ���������� � ��������� �������, ������������ � ������� ���������� FreeType
struct Character {
    unsigned int TextureID; // ID �������� �����
    glm::ivec2 Size; // ������ �����
    glm::ivec2 Bearing; // �������� �� ����� ������ �� �������� ������ ���� �����
    unsigned int Advance; // �������������� �������� ��� �������� � ���������� �����
};

// ����� TextRenderer ������������ ��� ���������� ������, ������������� �������, 
// ����������� � ������� ���������� FreeType. ����������� ����� �������������� � 
// ����������� ��� ������������ ���������� � ���� ������ ��������
class TextRenderer {
public:
    // ������ �������������� ���������������� ��������
    std::map<char, Character> characters;
    // ������, ������������ ��� ���������� ������
    ShaderProgram textShaderProgram;

    // �����������
    TextRenderer(unsigned int width, unsigned int height);

    // ������ �������������� ���������������� �������� �� ��������� ������
    void load(std::string font, unsigned int fontSize);

    // ��������� ������ ������ � �������������� �������������� ����������������� ������ ��������
    void renderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
private:

    // ��������� ����������
    unsigned int VAO, VBO;
};

#endif