#include "Level.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "ResourceManager.h"

Level::Level(std::string& data, const unsigned int& screenWidth, const unsigned int& screenHeight)
	: win(false) {
	//удаляем все пробелы из строки 
	for (std::string::iterator iter = data.begin(); iter < data.end(); ++iter)
		if (*iter == ' ') data.erase(iter);

	//вычисляем количество кирпичиков в ширину и высоту уровня
	const unsigned int widthBrick = data.find('\n'), heightBrick = data.length() / widthBrick;

	//удаляем все символы переноса строки
	for (std::string::iterator iter = data.begin(); iter < data.end(); ++iter)
		if (*iter == '\n') data.erase(iter);

	const float stepWidth = 2 / static_cast<float>(widthBrick), stepHeight = 1 / static_cast<float>(heightBrick),
		sizeWidth = 1.f / widthBrick, sizeHight = 0.5f / heightBrick;

	float posWidth = stepWidth / 2.f - 1, posHeight = 1 - stepHeight / 2.f;

	char codeBrick;

	for (unsigned int i = 0; i < heightBrick; ++i) {
		for (unsigned int j = 0; j < widthBrick; ++j, posWidth += stepWidth) {
			codeBrick = *(data.begin() + i * widthBrick + j);
			switch (codeBrick) {
				//простой кирпичик с двумя жизнями
				case '1':
					bricks.push_back(std::make_shared<Brick>(glm::vec2(posWidth, posHeight), glm::vec2(sizeWidth, sizeHight), ResourceManager::getSprite("simple brick sprite with 2 lifes"), true, 2));
				break;

				//простой кирпичик с одной жизнью
				case '2':
					bricks.push_back(std::make_shared<Brick>(glm::vec2(posWidth, posHeight), glm::vec2(sizeWidth, sizeHight), ResourceManager::getSprite("simple brick sprite with 1 life"), true, 1));
				break;

				//неразрушаемый кирпич
				case '3':
					bricks.push_back(std::make_shared<Brick>(glm::vec2(posWidth, posHeight), glm::vec2(sizeWidth, sizeHight), ResourceManager::getSprite("unbreakable brick sprite"), false));
				break;
			}
		}
		posHeight -= stepHeight;
		posWidth = stepWidth / 2.f - 1.f;
	}
}

void Level::draw() {
	for (std::shared_ptr<Brick> brick : bricks) brick->draw();
}

bool Level::complete() const {
	return win;
}

size_t Level::getBrickCount() const {
	return bricks.size();
}

std::shared_ptr<Brick> Level::getBrickByNumber(const size_t& number) const {
	return bricks[number];
}

void Level::deleteBrickByNumber(const size_t& number) {
	bricks.erase(bricks.begin() + number);
}