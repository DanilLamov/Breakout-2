#ifndef BRICK_H
#define BRICK_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>

#include "GameObject.h"

class Brick : public GameObject {
public:
    Brick() = delete;
    Brick(const glm::vec2& position,
          const glm::vec2& size,
          std::shared_ptr<Sprite> sprite,
          const bool& destrodestroyed,
          const unsigned int& life = 0);
    ~Brick() = default;

    virtual void draw();

    bool isDestroyed() const;

private:
    bool destrodestroyed;
    unsigned int life;
    
};

#endif