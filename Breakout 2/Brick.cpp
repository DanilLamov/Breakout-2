#include "Brick.h"

Brick::Brick(const glm::vec2& position, const glm::vec2& size, std::shared_ptr<Sprite> sprite, const bool& destrodestroyed, const unsigned int& life)
	: GameObject(position, size, .0f, sprite), destrodestroyed(destrodestroyed), life(life) {}

void Brick::draw() {
	GameObject::draw();
}

bool Brick::isDestroyed() const {
	return destrodestroyed;
}