#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Cover
{
private:

	void InitCover();
public:

	//texture for cover
	sf::Texture coverTexture;
	//Sprite for cover 
	sf::Sprite coverSprite;

	sf::Sprite destuctableCoverContainer [138];


	Cover();
	~Cover();
};

