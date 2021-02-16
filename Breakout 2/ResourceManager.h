#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <map>
#include <memory>

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Sprite.h"
#include "Level.h"
#include "Racket.h"
#include "Background.h"
#include "Ball.h"
#include "ParticleGenerator.h"

class ResourceManager {
public:
	//конструктор по умолчанию
	ResourceManager() = delete;
	//деструктор
	~ResourceManager() = delete;
	//конструктор копирования
	ResourceManager(const ResourceManager&) = delete;
	//конструктор присваивания
	ResourceManager& operator = (const ResourceManager&) = delete;
	//конструктор перемещения
	ResourceManager(ResourceManager&&) = delete;
	//конструктор присваивания перемещением
	ResourceManager& operator = (ResourceManager&&) = delete;

	//установка пути до исполняемого файла
	static void setExecutablePath(const std::string& executablePath);
	//получение пути исполняемого файла
	static std::string getExecutablePath();

	//удаление всех ресурсов
	static void clearResources();

	//возвращает содержимое текстового файла по указанному пути
	static std::string getFileString(const std::string& relativeFilePath);

	//создает шейдерную программу
	static std::shared_ptr<ShaderProgram> createShaderProgram(const std::string& shaderProgramName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	//возвращает шейдерную программу по ее имени
	static std::shared_ptr<ShaderProgram> getShaderProgram(const std::string& shaderProgramName);

	//созает 2Д текстуру
	static std::shared_ptr<Texture2D> createTexture2D(const std::string& textureName, const std::string& texturePath);
	//возвращает текстуру по ее имени
	static std::shared_ptr<Texture2D> getTexture2D(const std::string& textureName);

	//создает спрайт
	static std::shared_ptr<Sprite> createSprite(const std::string& spriteName, const std::string& shaderProgramName, const std::string& textureName);
	//возвращает спрайт по его имени
	static std::shared_ptr<Sprite> getSprite(const std::string& spriteName);

	//создает уровень
	static std::shared_ptr<Level> createLevel(const std::string& levelName, const std::string& levelPath, const unsigned int& screenWidth, const unsigned int& screenHeight);
	//возвращает уровень по его имени
	static std::shared_ptr<Level> getLevel(const std::string& levelName);
	//удаляет все уровни
	static void clearLevels();

	//создает ракетку
	static std::shared_ptr<Racket> createRacket(const std::string& racketName, const std::string& spriteName);
	//возвращает ракетку по ее имени
	static std::shared_ptr<Racket> getRacket(const std::string& racketName);

	//создает фон
	static std::shared_ptr<Background> createBackground(const std::string& backgroundName, const std::string& textureName);
	//возвращает фон по имени
	static std::shared_ptr<Background> getBackground(const std::string& backgroundName);

	//создает мяч
	static std::shared_ptr<Ball> createBall(const std::string& ballName, const std::string& spriteName);
	//возвращает мяч по его имени
	static std::shared_ptr<Ball> getBall(const std::string& ballName);

	//создание генератора частиц
	static std::shared_ptr<ParticleGenerator> createParticleGenerator(const std::string& particleGeneratorName, const std::string& textureName, const unsigned int& amount);
	//возвращает генератора частиц по его имени
	static std::shared_ptr<ParticleGenerator> getParticleGenerator(const std::string& particleGeneratorName);

private:
	//карта шейдерных программ
	static std::map<std::string, std::shared_ptr<ShaderProgram>> shaderProgramMap;
	static std::map<std::string, std::shared_ptr<Texture2D>> texture2DMap;
	static std::map<std::string, std::shared_ptr<Sprite>> spriteMap;
	static std::map<std::string, std::shared_ptr<Level>> levelMap;
	static std::map<std::string, std::shared_ptr<Racket>> racketMap;
	static std::map<std::string, std::shared_ptr<Background>> backgroundMap;
	static std::map<std::string, std::shared_ptr<Ball>> ballMap;
	static std::map<std::string, std::shared_ptr<ParticleGenerator>> particleGeneratorMap;
	static std::string exePath;

};

#endif