#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <memory>

#include "Brick.h"

class Level {
public:
	Level() = delete;
	Level(std::string& data, const unsigned int& sreenWidth, const unsigned int& sreenHeight);

	void draw();

	bool complete() const;

	size_t getBrickCount() const;
	std::shared_ptr<Brick> getBrickByNumber(const size_t& number) const;
	void deleteBrickByNumber(const size_t& number);

private:
	std::vector<std::shared_ptr<Brick>> bricks;
	bool win;

};

#endif