#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>

#include "Sprite.h"

class GameObject {
public:
    GameObject() = delete;
    GameObject(const glm::vec2& position, 
               const glm::vec2& size, 
               const float& rotation,
               std::shared_ptr<Sprite> sprite);
    ~GameObject() = default;

    virtual void draw();

    virtual float getPositionX() const;
    virtual void setPositionX(const float& positionX);

    virtual float getPositionY() const;
    virtual void setPositionY(const float& positionY);

    virtual glm::vec2 getPosition() const;
    virtual void setPosition(const glm::vec2& position);

    virtual float getSizeX() const;
    virtual void setSizeX(const float& sizeX);

    virtual float getSizeY() const;
    virtual void setSizeY(const float& sizeY);

    virtual glm::vec2 getSize() const;
    virtual void setSize(const glm::vec2& size);

private:
    glm::vec2 position, size;
    float rotation;
    std::shared_ptr<Sprite> sprite;

};


#endif