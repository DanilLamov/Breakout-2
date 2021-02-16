#include "Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>

#include <irrKlang/irrKlang.h>
using namespace irrklang;

ISoundEngine* soundEngine = createIrrKlangDevice();

#include "ResourceManager.h"
#include "Particle.h"

#include "TextRenderer.h"
TextRenderer* text;

//�������� ������������� ���������������
bool �heckCollision(std::shared_ptr<GameObject> first, std::shared_ptr<GameObject> second) {
	// ���������� �� ��� x?
	bool collisionX = first->getPositionX() - first->getSizeX() / 2 <= second->getPositionX() - second->getSizeX() / 2 
																	&&
					  second->getPositionX() - second->getSizeX() / 2 <= first->getPositionX() + first->getSizeX() / 2
																	||
					  second->getPositionX() - second->getSizeX() / 2 <= first->getPositionX() - first->getSizeX() / 2
																	&&
					  first->getPositionX() - first->getSizeX() / 2 <= second->getPositionX() + second->getSizeX() / 2;

	// ���������� �� ��� y?
	bool collisionY = first->getPositionY() - first->getSizeY() / 2 <= second->getPositionY() - second->getSizeY() / 2
																	&&
					  second->getPositionY() - second->getSizeY() / 2 <= first->getPositionY() + first->getSizeY() / 2
																	||
					  second->getPositionY() - second->getSizeY() / 2 <= first->getPositionY() - first->getSizeY() / 2
																	&&
					  first->getPositionY() - first->getSizeY() / 2 <= second->getPositionY() + second->getSizeY() / 2;

	// ���� ���������� ���������� ������������ ����� ����, �� �� ����� ������������
	return collisionX && collisionY;
}

/*
//�������� ������������ �������������� � ������
bool �heckCollision(std::shared_ptr<GameObject> gameObject, std::shared_ptr<Ball> ball, const size_t& countToLine = 5, const bool& fill = false) {
	/* ������ ������ �������� ����������� �������� 
	float distance = std::sqrt((gameObject->getPositionX() - ball->getPositionX()) * (gameObject->getPositionX() - ball->getPositionX()) +
		(gameObject->getPositionY() - ball->getPositionY()) * (gameObject->getPositionY() - ball->getPositionY())),
		sinus = std::abs(gameObject->getPositionY() - ball->getPositionY()) / distance,
		cosinus = std::abs(gameObject->getPositionX() - ball->getPositionX()) / distance,
		distance1 = ball->getSizeX() * ball->getSizeY() / 2 /
		std::sqrt(ball->getSizeX() * ball->getSizeX() * sinus * sinus + ball->getSizeY() * ball->getSizeY() * cosinus * cosinus),

		sinusG = gameObject->getSizeY() / std::sqrt(gameObject->getSizeY() * gameObject->getSizeY() + gameObject->getSizeX() * gameObject->getSizeX()),
		distance2 = (sinus > sinusG ? gameObject->getSizeY() / 2 / sinus : gameObject->getSizeX() / 2 / cosinus);
	
	return distance1 + distance2 >= distance;
	

	float x = gameObject->getPositionX() - gameObject->getSizeX(), y = gameObject->getPositionY() + gameObject->getSizeY(), 
		  stepX = gameObject->getSizeX() * 2 / countToLine, stepY = gameObject->getSizeY() * 2 / countToLine, distance, sinus, cosinus, radius;

	//�������� � �����������
	if (fill) {
		for (size_t i = 0; i < countToLine; ++i, y += stepY, x = gameObject->getPositionX() - gameObject->getSizeX()) {
			for (size_t j = 0; j < countToLine; ++j, x += stepX) {
				//������� ���������� �� ����� �� ������ �������
				distance = std::sqrt((x - ball->getPositionX()) * (x - ball->getPositionX()) + (y - ball->getPositionY()) * (y - ball->getPositionY()));
				//����� � ������� ���� �������, ������������� �� ������ ������ � �����
				sinus = std::abs(y - ball->getPositionY()) / distance;
				cosinus = std::abs(x - ball->getPositionX()) / distance;
				//������� ������
				radius = ball->getSizeX() * ball->getSizeY() /
					std::sqrt(ball->getSizeX() * ball->getSizeX() * sinus * sinus + ball->getSizeY() * ball->getSizeY() * cosinus * cosinus);
				if (distance <= radius) return true;
			}
		}
	}
	//��������� ��� ����������
	else {
		//�������� �� ������� � ������ ������ ��������������
		for (size_t i = 0; i < countToLine; ++i, x += stepX) {
			//������� ���������� �� ����� �� ������ �������
			distance = std::sqrt((x - ball->getPositionX()) * (x - ball->getPositionX()) + (y - ball->getPositionY()) * (y - ball->getPositionY()));
			//����� � ������� ���� �������, ������������� �� ������ ������ � �����
			sinus = std::abs(y - ball->getPositionY()) / distance;
			cosinus = std::abs(x - ball->getPositionX()) / distance;
			//������� ������
			radius = ball->getSizeX() * ball->getSizeY() /
				std::sqrt(ball->getSizeX() * ball->getSizeX() * sinus * sinus + ball->getSizeY() * ball->getSizeY() * cosinus * cosinus);
			if (distance <= radius) return true;

			//������� ���������� �� ����� �� ������ �������
			distance = std::sqrt((x - ball->getPositionX()) * (x - ball->getPositionX()) + (y - gameObject->getSizeY() * 2 - ball->getPositionY()) * (y - gameObject->getSizeY() * 2 - ball->getPositionY()));
			//����� � ������� ���� �������, ������������� �� ������ ������ � �����
			sinus = std::abs(y - gameObject->getSizeY() * 2 - ball->getPositionY()) / distance;
			cosinus = std::abs(x - ball->getPositionX()) / distance;
			//������� ������
			radius = ball->getSizeX() * ball->getSizeY() /
				std::sqrt(ball->getSizeX() * ball->getSizeX() * sinus * sinus + ball->getSizeY() * ball->getSizeY() * cosinus * cosinus);
			if (distance <= radius) return true;
		}

		//�������� �� ������� ������
		y -= stepY;
		for (size_t i = 2; i < countToLine; ++i, y -= stepY) {
			//������� ���������� �� ����� �� ������ �������
			distance = std::sqrt((x - ball->getPositionX()) * (x - ball->getPositionX()) + (y - ball->getPositionY()) * (y - ball->getPositionY()));
			//����� � ������� ���� �������, ������������� �� ������ ������ � �����
			sinus = std::abs(y - ball->getPositionY()) / distance;
			cosinus = std::abs(x - ball->getPositionX()) / distance;
			//������� ������
			radius = ball->getSizeX() * ball->getSizeY() /
				std::sqrt(ball->getSizeX() * ball->getSizeX() * sinus * sinus + ball->getSizeY() * ball->getSizeY() * cosinus * cosinus);
			if (distance <= radius) return true;

			//������� ���������� �� ����� �� ������ �������
			distance = std::sqrt((x - gameObject->getSizeX() * 2- ball->getPositionX()) * (x - gameObject->getSizeX() * 2 - ball->getPositionX()) + (y - ball->getPositionY()) * (y - ball->getPositionY()));
			//����� � ������� ���� �������, ������������� �� ������ ������ � �����
			sinus = std::abs(y - ball->getPositionY()) / distance;
			cosinus = std::abs(x - gameObject->getSizeX() * 2 - ball->getPositionX()) / distance;
			//������� ������
			radius = ball->getSizeX() * ball->getSizeY() /
				std::sqrt(ball->getSizeX() * ball->getSizeX() * sinus * sinus + ball->getSizeY() * ball->getSizeY() * cosinus * cosinus);
			if (distance <= radius) return true;
		}
	}

	return false;
}
*/

enum direction {
	UP,
	DOWN,
	RIGHT,
	LEFT
};

direction vectorDirection(glm::vec2 target) {
	glm::vec2 vectorDirection[] = {
		glm::vec2(0.0f, 1.0f),	// �����
		glm::vec2(0.0f, -1.0f), // ����
		glm::vec2(1.0f, 0.0f),	// ������
		glm::vec2(-1.0f, 0.0f)	// �����
	};
	float max = 0.0f;
	unsigned int best_match = 0;
	for (unsigned int i = 0; i < 4; ++i) {
		float dot_product = glm::dot(glm::normalize(target), vectorDirection[i]);
		if (dot_product > max) {
			max = dot_product;
			best_match = i;
		}
	}
	return (direction)best_match;
}

std::tuple<bool, direction, glm::vec2> �heckCollision(std::shared_ptr<GameObject> gameObject, std::shared_ptr<Ball> ball, const size_t& countToLine = 5, const bool& fill = false) {
	float x = gameObject->getPositionX() - gameObject->getSizeX(), y = gameObject->getPositionY() + gameObject->getSizeY(),
		stepX = gameObject->getSizeX() * 2 / countToLine, stepY = gameObject->getSizeY() * 2 / countToLine, distance, sinus, cosinus, radius;

	//�������� � �����������
	if (fill) {
		for (size_t i = 0; i < countToLine; ++i, y += stepY, x = gameObject->getPositionX() - gameObject->getSizeX()) {
			for (size_t j = 0; j < countToLine; ++j, x += stepX) {
				//������� ���������� �� ����� �� ������ �������
				distance = std::sqrt((x - ball->getPositionX()) * (x - ball->getPositionX()) + (y - ball->getPositionY()) * (y - ball->getPositionY()));
				//����� � ������� ���� �������, ������������� �� ������ ������ � �����
				sinus = std::abs(y - ball->getPositionY()) / distance;
				cosinus = std::abs(x - ball->getPositionX()) / distance;
				//������� ������
				radius = ball->getSizeX() * ball->getSizeY() /
					std::sqrt(ball->getSizeX() * ball->getSizeX() * sinus * sinus + ball->getSizeY() * ball->getSizeY() * cosinus * cosinus);
				if (distance <= radius) return std::make_tuple(true, vectorDirection(x - glm::vec2(ball->getPositionX(), y - ball->getPositionY())), glm::vec2(x - ball->getPositionX(), y - ball->getPositionY()));
			}
		}
	}
	//��������� ��� ����������
	else {
		//�������� �� ������� � ������ ������ ��������������
		for (size_t i = 0; i < countToLine; ++i, x += stepX) {
			//������� ���������� �� ����� �� ������ �������
			distance = std::sqrt((x - ball->getPositionX()) * (x - ball->getPositionX()) + (y - ball->getPositionY()) * (y - ball->getPositionY()));
			//����� � ������� ���� �������, ������������� �� ������ ������ � �����
			sinus = std::abs(y - ball->getPositionY()) / distance;
			cosinus = std::abs(x - ball->getPositionX()) / distance;
			//������� ������
			radius = ball->getSizeX() * ball->getSizeY() /
				std::sqrt(ball->getSizeX() * ball->getSizeX() * sinus * sinus + ball->getSizeY() * ball->getSizeY() * cosinus * cosinus);
			if (distance <= radius) return std::make_tuple(true, vectorDirection(glm::vec2(ball->getPositionX() - x, ball->getPositionY() - y)), glm::vec2(ball->getPositionX() - x, ball->getPositionY() - y));

			//������� ���������� �� ����� �� ������ �������
			distance = std::sqrt((x - ball->getPositionX()) * (x - ball->getPositionX()) + (y - gameObject->getSizeY() * 2 - ball->getPositionY()) * (y - gameObject->getSizeY() * 2 - ball->getPositionY()));
			//����� � ������� ���� �������, ������������� �� ������ ������ � �����
			sinus = std::abs(y - gameObject->getSizeY() * 2 - ball->getPositionY()) / distance;
			cosinus = std::abs(x - ball->getPositionX()) / distance;
			//������� ������
			radius = ball->getSizeX() * ball->getSizeY() /
				std::sqrt(ball->getSizeX() * ball->getSizeX() * sinus * sinus + ball->getSizeY() * ball->getSizeY() * cosinus * cosinus);
			if (distance <= radius) return std::make_tuple(true, vectorDirection(glm::vec2(ball->getPositionX() - x, ball->getPositionY() - y + gameObject->getSizeY() * 2)), glm::vec2(ball->getPositionX() - x, ball->getPositionY() - y + gameObject->getSizeY() * 2));
		}

		//�������� �� ������� ������
		y -= stepY;
		for (size_t i = 2; i < countToLine; ++i, y -= stepY) {
			//������� ���������� �� ����� �� ������ �������
			distance = std::sqrt((x - ball->getPositionX()) * (x - ball->getPositionX()) + (y - ball->getPositionY()) * (y - ball->getPositionY()));
			//����� � ������� ���� �������, ������������� �� ������ ������ � �����
			sinus = std::abs(y - ball->getPositionY()) / distance;
			cosinus = std::abs(x - ball->getPositionX()) / distance;
			//������� ������
			radius = ball->getSizeX() * ball->getSizeY() /
				std::sqrt(ball->getSizeX() * ball->getSizeX() * sinus * sinus + ball->getSizeY() * ball->getSizeY() * cosinus * cosinus);
			if (distance <= radius) return std::make_tuple(true, vectorDirection(glm::vec2(ball->getPositionX() - x, ball->getPositionY() - y)), glm::vec2(ball->getPositionX() - x, ball->getPositionY() - y));

			//������� ���������� �� ����� �� ������ �������
			distance = std::sqrt((x - gameObject->getSizeX() * 2 - ball->getPositionX()) * (x - gameObject->getSizeX() * 2 - ball->getPositionX()) + (y - ball->getPositionY()) * (y - ball->getPositionY()));
			//����� � ������� ���� �������, ������������� �� ������ ������ � �����
			sinus = std::abs(y - ball->getPositionY()) / distance;
			cosinus = std::abs(x - gameObject->getSizeX() * 2 - ball->getPositionX()) / distance;
			//������� ������
			radius = ball->getSizeX() * ball->getSizeY() /
				std::sqrt(ball->getSizeX() * ball->getSizeX() * sinus * sinus + ball->getSizeY() * ball->getSizeY() * cosinus * cosinus);
			if (distance <= radius) return std::make_tuple(true, vectorDirection(glm::vec2(ball->getPositionX() - x + gameObject->getSizeX() * 2, ball->getPositionY() - y)), glm::vec2(ball->getPositionX() - x + gameObject->getSizeX() * 2, ball->getPositionY() - y));
		}
	}

	return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

void Game::collisions() {
	//�������� ������������ ���� � �����������
	for (int i = ResourceManager::getLevel("level 1")->getBrickCount() - 1; i >= 0; --i) {
		std::tuple<bool, direction, glm::vec2> collision = �heckCollision(ResourceManager::getLevel("level 1")->getBrickByNumber(i), ResourceManager::getBall("ball"), 5);
		if (std::get<0>(collision)) {
			//��������� ������, ���� �� �� �������� �������������
			if (ResourceManager::getLevel("level 1")->getBrickByNumber(i)->isDestroyed()) {
				ResourceManager::getLevel("level 1")->deleteBrickByNumber(i);
				soundEngine->play2D("audio\\bleep.mp3", false);
			}
			//���� ������ �������
			else {
				soundEngine->play2D("audio\\solid.wav", false);
			}

			// ��������� ������������
			direction dir = std::get<1>(collision);
			glm::vec2 diff_vector = std::get<2>(collision);
			// �������������� ������������
			if (dir == LEFT || dir == RIGHT) {
				// �������� �������������� ��������
				ResourceManager::getBall("ball")->setVelocityX(-ResourceManager::getBall("ball")->getVelocityX());

				// �����������
				float penetration = ResourceManager::getBall("ball")->getSizeX() - std::abs(diff_vector.x);
				// ������� ��� ������� ������ ��� �����
				ResourceManager::getBall("ball")->setPositionX(dir == LEFT ? ResourceManager::getBall("ball")->getPositionX() + penetration : ResourceManager::getBall("ball")->getPositionX() - penetration);
			}
			// ������������ ������������
			else {
				// �������� ������������ ��������
				ResourceManager::getBall("ball")->setVelocityY(-ResourceManager::getBall("ball")->getVelocityY());
				
				// �����������
				float penetration = ResourceManager::getBall("ball")->getSizeY() - std::abs(diff_vector.y);
				// ������� ��� ������� ����� ��� ����
				ResourceManager::getBall("ball")->setPositionY(dir == UP ? ResourceManager::getBall("ball")->getPositionY() - penetration : ResourceManager::getBall("ball")->getPositionY() + penetration);
			}
		}
	}

	// �������� ������������ ��� ������� ������ (���� ��� �� ������������ �� ���)
	std::tuple<bool, direction, glm::vec2> collision = �heckCollision(ResourceManager::getRacket("racket 1"), ResourceManager::getBall("ball"));
	if (!ResourceManager::getBall("ball")->isStuck() && std::get<0>(collision)) {
		// �������, � ����� ����� ��� �������� � �����, � � ����������� �� ����� �������� ��������
		//float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
		float distance = ResourceManager::getBall("ball")->getPositionX() + ResourceManager::getBall("ball")->getSizeX() - ResourceManager::getRacket("racket 1")->getPositionX();
		//float distance = ResourceManager::getBall("ball")->getPositionX() - ResourceManager::getRacket("racket 1")->getPositionX();
		float percentage = distance / ResourceManager::getRacket("racket 1")->getSizeX();

		// � ��������������� ������� �����������
		float strength = .2f;
		glm::vec2 oldVelocity = ResourceManager::getBall("ball")->getVelocity();

		ResourceManager::getBall("ball")->setVelocityX(ResourceManager::getBall("ball")->getVelocityX() * percentage * strength);

		// ����� �������� ������� �������� �� ��������������� ��� ������ ���� ���������� (�������� �� �������� ������ ��������, ����� �������� �������� �� ��������)
		ResourceManager::getBall("ball")->setVelocity(glm::normalize(ResourceManager::getBall("ball")->getVelocity() * glm::length(oldVelocity)));

		// ������� �������� "������ �������"
		ResourceManager::getBall("ball")->setVelocityY(-abs(ResourceManager::getBall("ball")->getVelocityY()) + 1.f);

		soundEngine->play2D("audio\\bleep.wav", false);
	}

}

Game::Game(const unsigned int& windowWidth, const unsigned int& windowHeight)
	: gameState(GameState::GAME_ACTIVE), keys(), windowWidth(windowWidth), windowHeight(windowHeight) {}

void Game::init() {
	ResourceManager::createShaderProgram("shader program for sprite", "shaders\\spriteVertexShader.txt", "shaders\\spriteFragmentShader.txt");

	//�������� � �������� ����
	ResourceManager::createTexture2D("blue background", "textures\\background.png");
	ResourceManager::createBackground("background 1", "blue background");

	//�������� � �������� �������� ������
	ResourceManager::createTexture2D("simple brick with 2 lifes", "textures\\simple brick with 2 lifes.png");
	ResourceManager::createSprite("simple brick sprite with 2 lifes", "shader program for sprite", "simple brick with 2 lifes");
	
	ResourceManager::createTexture2D("simple brick with 1 life", "textures\\simple brick with 1 life.png");
	ResourceManager::createSprite("simple brick sprite with 1 life", "shader program for sprite", "simple brick with 1 life");

	ResourceManager::createTexture2D("unbreakable brick", "textures\\unbreakable brick.png");
	ResourceManager::createSprite("unbreakable brick sprite", "shader program for sprite", "unbreakable brick");

	//�������� � �������� ������
	ResourceManager::createLevel("level 1", "levels\\1.txt", windowWidth, windowHeight);

	//�������� � �������� �������
	ResourceManager::createTexture2D("racket", "textures\\racket.png");
	ResourceManager::createSprite("racket sprite", "shader program for sprite", "racket");
	ResourceManager::createRacket("racket 1", "racket sprite");

	//�������� � �������� ����
	ResourceManager::createTexture2D("ball texture", "textures\\awesomeface.png");
	ResourceManager::createSprite("ball sprite", "shader program for sprite", "ball texture");
	ResourceManager::createBall("ball", "ball sprite");

	//�������� � �������� ���������
	ResourceManager::createTexture2D("particle texture", "textures\\particle.png");
	ResourceManager::createParticleGenerator("ball particle", "particle texture", 500);

	//soundEngine->play2D((ResourceManager::getExecutablePath() + "audio\\breakout.mp3").c_str(), true);
	soundEngine->play2D("audio\\breakout.mp3", true);

	text = new TextRenderer(windowWidth, windowHeight);
	//text->load(ResourceManager::getExecutablePath() + "\\" + "fonts\\OCRAEXT.TTF", 24);
	text->load(ResourceManager::getExecutablePath() + "\\" + "fonts\\OCRAEXT.TTF", 24);
}

void Game::input(const float& dt) {
	if (gameState == GAME_ACTIVE) {
		float velocity = ResourceManager::getRacket("racket 1")->getVelocity() * dt;

		// ���������� �������
		if (keys[GLFW_KEY_A]) {
			float pos = ResourceManager::getRacket("racket 1")->getPositionX();
			if (pos >= -.87f) {
				ResourceManager::getRacket("racket 1")->setPositionX(pos - velocity);
				if (ResourceManager::getBall("ball")->isStuck())
					ResourceManager::getBall("ball")->setPositionX(ResourceManager::getBall("ball")->getPositionX() - velocity);
			}
		}
		if (keys[GLFW_KEY_D]) {
			float pos = ResourceManager::getRacket("racket 1")->getPositionX();
			//windowWidth - ResourceManager::getRacket("racket 1")->getSize()
			if (pos <= 0.87f) {
				ResourceManager::getRacket("racket 1")->setPositionX(pos + velocity);
				if (ResourceManager::getBall("ball")->isStuck())
					ResourceManager::getBall("ball")->setPositionX(ResourceManager::getBall("ball")->getPositionX() + velocity);
			}
		}
		if (keys[GLFW_KEY_SPACE])
			ResourceManager::getBall("ball")->setStuck(false);
	}
}

void Game::update(const float& dt) {
	ResourceManager::getBall("ball")->move(dt, windowWidth);

	// ���������� ������
	ResourceManager::getParticleGenerator("ball particle")->update(dt, ResourceManager::getBall("ball"), 2, ResourceManager::getBall("ball")->getVelocity());

	collisions();

	// �������� ������� ������ ��������� ����
	if (ResourceManager::getBall("ball")->getPositionY() <= -1) {
		ResourceManager::clearLevels();
		ResourceManager::createLevel("level 1", "levels\\1.txt", windowWidth, windowHeight);

		//ResourceManager::getBall("ball")->setPosition(glm::vec2(0, -.86f));
		ResourceManager::getBall("ball")->reset(glm::vec2(0, -.85f), glm::vec2(.2f, .5f));
		ResourceManager::getRacket("racket 1")->setPosition(glm::vec2(0, -.95f));
	}
}

void Game::render() {
	//ResourceManager::getSprite("smile sprite")->draw(glm::vec2(0, 0), glm::vec2(0.5f, 0.5f), 0.f);

	ResourceManager::getBackground("background 1")->draw();

	//ResourceManager::getSprite("simple brick sprite with 2 lifes")->draw(glm::vec2(-.93f, .9375f), glm::vec2(.133333f, .125f), 0.f);

	ResourceManager::getLevel("level 1")->draw();

	ResourceManager::getRacket("racket 1")->draw();

	ResourceManager::getParticleGenerator("ball particle")->draw();

	ResourceManager::getBall("ball")->draw();

	text->renderText("Press ENTER to start", 250.0f, 600 / 2, 1.0f);
	text->renderText("Press W or S to select level", 245.0f, 600 / 2 + 20.0f, 0.75f);
}

void Game::pressKey(const size_t& key) {
	keys[key] = true;
}

void Game::releaseKey(const size_t& key) {
	keys[key] = false;
}