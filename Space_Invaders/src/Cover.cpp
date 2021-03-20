#include "Cover.h"
#include "..\include\Cover.h"

void Cover::InitCover()
{
	this->sprite.setSize(sf::Vector2f( 10.f,10.f));
	this->sprite.setFillColor(sf::Color::White);

	this->destuctableCoverContainer.reserve(139);
}

Cover::Cover()
{
	InitCover();
}

Cover::~Cover()
{
}
