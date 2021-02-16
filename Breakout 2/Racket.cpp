#include "Racket.h"

Racket::Racket(const glm::vec2& position, std::shared_ptr<Sprite> sprite)
	: GameObject(position, glm::vec2(100.f / 800.f, 20.f / 600.f), .0f, sprite) {}

void Racket::draw() {
	GameObject::draw();
}

float Racket::getVelocity() const {
	return velocity.x;
}

void Racket::setVelocity(const float& x) {
	velocity.x = x;
}