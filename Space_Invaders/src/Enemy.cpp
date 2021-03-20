#include "Enemy.h"
#include "..\include\Enemy.h"

void Enemy::InitEnemy()
{
	this->sprite.setSize(sf::Vector2f(37.f, 37.f));
	this->sprite.setFillColor(sf::Color::Red);
}

void Enemy::InitBullet()
{
	this->Bullet.setRadius(5.f);
	this->Bullet.setFillColor(sf::Color::Yellow);
}




Enemy::Enemy()
{
	this->InitEnemy();
	this->InitBullet();
}

Enemy::~Enemy()
{
}

