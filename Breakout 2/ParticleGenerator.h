#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <vector>

#include"Particle.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

class ParticleGenerator {
public:
	ParticleGenerator() = delete;
	//текстура и максимальное количество данный партиклов
	ParticleGenerator(std::shared_ptr<Texture2D> texture, const unsigned int& amount);
	~ParticleGenerator();

	void draw();

	void update(const float& dt, std::shared_ptr<GameObject> gameObject, const unsigned int& amountNewParticles, const glm::vec2& velocity, const glm::vec2& offset = glm::vec2(0.0f, 0.0f));

private:
	std::shared_ptr<Texture2D> texture;
	ShaderProgram shaderProgram;
	GLuint VAO, VBO, EBO;

	std::vector<Particle> particles;
	unsigned int amount;

	//вспомогательная функция для нахождения индекса первого неиспользуемого партикла
	unsigned int firstUnusedParticle();

};

#endif