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
	//����������� �� ���������
	ResourceManager() = delete;
	//����������
	~ResourceManager() = delete;
	//����������� �����������
	ResourceManager(const ResourceManager&) = delete;
	//����������� ������������
	ResourceManager& operator = (const ResourceManager&) = delete;
	//����������� �����������
	ResourceManager(ResourceManager&&) = delete;
	//����������� ������������ ������������
	ResourceManager& operator = (ResourceManager&&) = delete;

	//��������� ���� �� ������������ �����
	static void setExecutablePath(const std::string& executablePath);
	//��������� ���� ������������ �����
	static std::string getExecutablePath();

	//�������� ���� ��������
	static void clearResources();

	//���������� ���������� ���������� ����� �� ���������� ����
	static std::string getFileString(const std::string& relativeFilePath);

	//������� ��������� ���������
	static std::shared_ptr<ShaderProgram> createShaderProgram(const std::string& shaderProgramName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	//���������� ��������� ��������� �� �� �����
	static std::shared_ptr<ShaderProgram> getShaderProgram(const std::string& shaderProgramName);

	//������ 2� ��������
	static std::shared_ptr<Texture2D> createTexture2D(const std::string& textureName, const std::string& texturePath);
	//���������� �������� �� �� �����
	static std::shared_ptr<Texture2D> getTexture2D(const std::string& textureName);

	//������� ������
	static std::shared_ptr<Sprite> createSprite(const std::string& spriteName, const std::string& shaderProgramName, const std::string& textureName);
	//���������� ������ �� ��� �����
	static std::shared_ptr<Sprite> getSprite(const std::string& spriteName);

	//������� �������
	static std::shared_ptr<Level> createLevel(const std::string& levelName, const std::string& levelPath, const unsigned int& screenWidth, const unsigned int& screenHeight);
	//���������� ������� �� ��� �����
	static std::shared_ptr<Level> getLevel(const std::string& levelName);
	//������� ��� ������
	static void clearLevels();

	//������� �������
	static std::shared_ptr<Racket> createRacket(const std::string& racketName, const std::string& spriteName);
	//���������� ������� �� �� �����
	static std::shared_ptr<Racket> getRacket(const std::string& racketName);

	//������� ���
	static std::shared_ptr<Background> createBackground(const std::string& backgroundName, const std::string& textureName);
	//���������� ��� �� �����
	static std::shared_ptr<Background> getBackground(const std::string& backgroundName);

	//������� ���
	static std::shared_ptr<Ball> createBall(const std::string& ballName, const std::string& spriteName);
	//���������� ��� �� ��� �����
	static std::shared_ptr<Ball> getBall(const std::string& ballName);

	//�������� ���������� ������
	static std::shared_ptr<ParticleGenerator> createParticleGenerator(const std::string& particleGeneratorName, const std::string& textureName, const unsigned int& amount);
	//���������� ���������� ������ �� ��� �����
	static std::shared_ptr<ParticleGenerator> getParticleGenerator(const std::string& particleGeneratorName);

private:
	//����� ��������� ��������
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