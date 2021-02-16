#include "Particle.h"

Particle::Particle() : position(glm::vec2(0.f)), size(glm::vec2(0.f)), velocity(glm::vec2(0.f, 0.f)), color(glm::vec4(0.f)), life(0.f) {}

Particle::Particle(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity, const glm::vec4& color, const float& life)
	: position(position), size(size), velocity(velocity), color(color), life(life) {}

glm::vec2 Particle::getPosition() const {
	return position;
}

void Particle::setPosition(const glm::vec2& position) {
	this->position = position;
}

glm::vec2 Particle::getSize() const {
	return size;
}

void Particle::setSize(const glm::vec2& size) {
	this->size = size;
}

glm::vec2 Particle::getVelocity() const {
	return velocity;
}

void Particle::setVelocity(const glm::vec2& velocity) {
	this->velocity = velocity;
}

glm::vec4 Particle::getColor() const {
	return color;
}

void Particle::setColor(const glm::vec4& color) {
	this->color = color;
}

float Particle::getLife() const {
	return life;
}

void Particle::setLife(const float& life) {
	this->life = life;
}