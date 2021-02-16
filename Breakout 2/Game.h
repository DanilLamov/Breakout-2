#ifndef GAME_H
#define GAME_H

class Game {
public:
    //конструктор по умолчанию
    Game() = delete;
    //конструктор
    Game(const unsigned int& windowWidth, const unsigned int& windowHeight);
    //деструктор
    ~Game() = default;
    //конструктор копирования
    Game(const Game&) = delete;
    //конструктор присваиваания
    Game& operator = (const Game&) = delete;
    //конструктор перемещения
    Game(Game&&) = delete;
    //конструктор присваиваания перемещением
    Game& operator = (Game&&) = delete;

    void init();
    void input(const float& dt);
    void update(const float& dt);
    void render();

    void pressKey(const size_t& key);
    void releaseKey(const size_t& key);

    void collisions();

private:
    enum GameState {
        GAME_ACTIVE,
        GAME_MENU,
        GAME_WIN,
        GAME_PAUSE
    };

    GameState gameState;
    unsigned int windowWidth, windowHeight;
    bool keys[1024];

};

#endif