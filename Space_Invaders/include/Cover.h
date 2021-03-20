#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Cover
{
private:

	void InitCover();
public:

	sf::RectangleShape sprite;

	std::vector<sf::RectangleShape> destuctableCoverContainer;


	Cover();
	~Cover();
};

