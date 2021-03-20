#include "Player.h"

void Player::InitPlayer()
{
	this->sprite.setSize(sf::Vector2f(50.f,50.f));
	this->sprite.setFillColor(sf::Color::Green);
}

void Player::InitBullet()
{
	this->Bullet.setRadius(5.f);
	this->Bullet.setFillColor(sf::Color::Blue);
}

Player::Player()
{
	this->InitPlayer();
	this->InitBullet();
}

Player::~Player()
{
}
