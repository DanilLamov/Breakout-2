#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "TextRenderer.h"
//#include "resource_manager.h"

const char* vertexShader =
"#version 330 core\n"

"layout (location = 0) in vec4 vertex;"

"out vec2 TexCoords;"

"uniform mat4 model;"

"void main() {"
    "gl_Position = model * vec4(vertex.xy, 0.0, 1.0);"
    "TexCoords = vertex.zw;"
"}";

const char* fragmentShader =
"#version 330 core\n"

"in vec2 TexCoords;"

"out vec4 color;"

"uniform sampler2D text;"
"uniform vec3 textColor;"

"void main() {"
    "vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);"
    "color = vec4(textColor, 1.0) * sampled;"
"}";

TextRenderer::TextRenderer(unsigned int width, unsigned int height)
    : textShaderProgram(vertexShader, fragmentShader) {
    // �������� � ��������� �������
    textShaderProgram.use();
    textShaderProgram.setMatrix4("model", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f));
    textShaderProgram.setInt("text", 0);

    // �������� VAO/VBO ��� ���������� ���������������
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::load(std::string font, unsigned int fontSize) {
    // ������� ������� ����� ����������� �������
    characters.clear();

    // ����� �������������� � ��������� ���������� FreeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) // ��� ������� � ������ ������ ���������� ��������, �������� �� 0
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    // �������� ������ � �������� face
    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // ������������� ������ ����������� ������
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    // ��������� ����������� �� ������������ ������
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // �������������� ���������/����������� ������� ������ � ��������� ��
    for (GLubyte c = 0; c < 255; c++) {
        // �������� ������� �����
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // ��������� ��������
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // ��������� ���������� �������
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // ������ ��������� ������� ��� �� ����������� �������������
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    // ����� ���������, ����������� ������� FreeType
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::renderText(std::string text, float x, float y, float scale, glm::vec3 color) {
    // ���������� ��������������� ��������� �������
    textShaderProgram.use();
    textShaderProgram.setVec3("textColor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // ���� �� ���� ��������
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y + (characters['H'].Bearing.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        // ��������� VBO ��� ������� �������
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };

        // �������� �� ������������� �������� �����
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        // ��������� ���������� ������ VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // ����������� ����������� ������� glBufferSubData(), � �� ������� glBufferData()
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // �������� �������������
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // ������ ������� ������ � ���������� �����
        x += (ch.Advance >> 6) * scale; // ������� ����� �� 6, ����� �������� �������� � �������� (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}