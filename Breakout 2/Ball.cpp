#include "Ball.h"

Ball::Ball(const glm::vec2& position, const float& radius, std::shared_ptr<Sprite> sprite)
	: GameObject(position, glm::vec2(radius, 800.f / 600.f * radius), .0f, sprite), stuck(true), radius(radius) {}

void Ball::draw() {
	GameObject::draw();
}

void Ball::move(const float& dt, const unsigned int& window_width) {
	// Если мяч не зафиксирован ракеткой,
	if (!stuck) {
		// то перемещаем мяч
		GameObject::setPosition(GameObject::getPosition() + velocity * dt);

		// Проверка, находится ли мяч за пределами границ окна; если – да, то изменяем его скорость и восстанавливаем правильное положение
		if (GameObject::getPositionX() <= -1.0001f + GameObject::getSizeX()) {
			velocity.x *= -1;
			GameObject::setPositionX(-1.0001f + GameObject::getSizeX());
		}
		else if (GameObject::getPositionX() >= 1.0001f - GameObject::getSizeX()) {
			velocity.x *= -1;
			GameObject::setPositionX(1.0001f - GameObject::getSizeX());
		}
		if (GameObject::getPositionY() >= 1.0001f - GameObject::getSizeX()) {
			velocity.y = -velocity.y;
			GameObject::setPositionY(1.0001f - GameObject::getSizeY());
		}

	}
}

void Ball::reset(const glm::vec2& position, const glm::vec2& velocity) {
	GameObject::setPosition(position);
	this->velocity = velocity;
	stuck = true;
}

bool Ball::isStuck() const {
	return stuck;
}

void Ball::setStuck(const bool& stuck) {
	this->stuck = stuck;
}

glm::vec2 Ball::getVelocity() const {
	return velocity;
}

void Ball::setVelocity(const glm::vec2& velocity) {
	this->velocity = velocity;
}

float Ball::getVelocityX() const {
	return velocity.x;
}

void Ball::setVelocityX(const float& velocityX) {
	velocity.x = velocityX;
}

float Ball::getVelocityY() const {
	return velocity.y;
}

void Ball::setVelocityY(const float& velocityY) {
	velocity.y = velocityY;
}