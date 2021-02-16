#ifndef BALL_H
#define BALL_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>

#include "GameObject.h"

class Ball : public GameObject {
public:
	Ball() = delete;
	Ball(const glm::vec2& position, const float& radius, std::shared_ptr<Sprite> sprite);
	~Ball() = default;

	virtual void draw();

	void move(const float& dt, const unsigned int& window_width);

	void reset(const glm::vec2& position, const glm::vec2& velocity);

	glm::vec2 getVelocity() const;
	void setVelocity(const glm::vec2& velocity);

	float getVelocityX() const;
	void setVelocityX(const float& velocityX);

	float getVelocityY() const;
	void setVelocityY(const float& velocityY);

	bool isStuck() const;
	void setStuck(const bool& stuck);

private:
	glm::vec2 velocity = glm::vec2(.2f, .5f);
	float radius;
	bool stuck;

};

#endif
