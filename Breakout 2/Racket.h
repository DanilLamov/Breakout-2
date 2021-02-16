#ifndef RACKET_H
#define RACKET_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>

#include "GameObject.h"

class Racket : public GameObject {
public:
    Racket() = delete;
    Racket(const glm::vec2& position, std::shared_ptr<Sprite> sprite);
    ~Racket() = default;

    virtual void draw();

    float getVelocity() const;
    void setVelocity(const float& x);

private:
    glm::vec2 velocity = glm::vec2(.8f, .0f);

};

#endif