#include "GameObject.h"

GameObject::GameObject(const glm::vec2& position, const glm::vec2& size, const float& rotation, std::shared_ptr<Sprite> sprite)
	: position(position), size(size), rotation(rotation), sprite(sprite) {}

void GameObject::draw() { 
	sprite->draw(position, size, rotation); 
}

float GameObject::getPositionX() const {
	return position.x;
}

void GameObject::setPositionX(const float& positionX) {
	position.x = positionX;
}

float GameObject::getPositionY() const {
	return position.y;
}

void GameObject::setPositionY(const float& positionY) {
	position.y = positionY;
}

glm::vec2 GameObject::getPosition() const {
	return position;
}

void GameObject::setPosition(const glm::vec2& position) {
	this->position = position;
}

float GameObject::getSizeX() const {
	return size.x;
}

void GameObject::setSizeX(const float& sizeX) {
	size.x = sizeX;
}

float GameObject::getSizeY() const {
	return size.y;
}

void GameObject::setSizeY(const float& sizeY) {
	size.y = sizeY;
}

glm::vec2 GameObject::getSize() const {
	return size;
}

void GameObject::setSize(const glm::vec2& size) {
	this->size = size;
}