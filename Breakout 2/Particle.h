#ifndef PARTICLE_H
#define PARTICLE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"

class Particle {
public:
    Particle();
    Particle(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity, const glm::vec4& color, const float& life);
    ~Particle() = default;

    glm::vec2 getPosition() const;
    void setPosition(const glm::vec2& position);

    glm::vec2 getSize() const;
    void setSize(const glm::vec2& size);

    glm::vec2 getVelocity() const;
    void setVelocity(const glm::vec2& velocity);

    glm::vec4 getColor() const;
    void setColor(const glm::vec4& color);

    float getLife() const;
    void setLife(const float& life);
    
private:
    glm::vec2 position, size, velocity;
    glm::vec4 color;
    float life;

};

#endif