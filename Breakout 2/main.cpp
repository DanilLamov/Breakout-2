#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "ResourceManager.h"
#include "Game.h"

// Константы
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Game breakout(SCR_WIDTH, SCR_HEIGHT);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // Когда пользователь нажимает клавишу Escape, мы устанавливаем для свойства WindowShouldClose значение true, закрывая приложение
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
        if (action == GLFW_PRESS) breakout.pressKey(key);
        else if (action == GLFW_RELEASE) breakout.releaseKey(key);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.
    // Обратите внимание, ширина и высота будут значительно больше, чем указано, на Retina-дисплеях
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv) {
    //glfw: инициализация и конфигурирование    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfw: создание окна
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Breakout 2", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: загрузка всех указателей на OpenGL-функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Конфигурация OpenGL
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ResourceManager::setExecutablePath(*argv);

    breakout.init();

    float deltaTime = 0.f, lastFrame = 0.f;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Цикл рендеринга
    while (!glfwWindowShouldClose(window)) {
        // Вычисление дельты времени
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Обрабатываем пользовательский ввод с клавиатуры
        breakout.input(deltaTime);

        // Обновляем состояние игры
        breakout.update(deltaTime);


        // Рендеринг
        glClear(GL_COLOR_BUFFER_BIT);

        breakout.render();

        // glfw: обмен содержимым front- и back- буферов. Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: завершение, освобождение всех выделенных ранее GLFW-реурсов
    glfwTerminate();
    return 0;
}