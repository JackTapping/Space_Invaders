#include "Player.h"

void Player::InitPlayer()
{
	
	if(this->playerShipTexture.loadFromFile("..\\assets\\images\\Ship.png"))
	{
		std::cout << "Player Ship Texture Loaded\n";
	}
	this->playerSprite.setTexture(this->playerShipTexture);
}

void Player::InitBullet()
{
	if (this->playerBuletTexture.loadFromFile("..\\assets\\images\\Bullet.png"))
	{
		std::cout << "Player Bullet Texture Loaded\n";
	}
	this->playerBulletSprite.setTexture(this->playerBuletTexture);
}

Player::Player()
{
	this->InitPlayer();
	this->InitBullet();
}

Player::~Player()
{
}
