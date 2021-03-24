#include "Enemy.h"
#include "..\include\Enemy.h"

void Enemy::InitEnemy()
{
	if (this->enemyShipTextureA1.loadFromFile("..\\assets\\images\\InvaderA1.png"))
	{
		std::cout << "enemy Ship Texture A1 Loaded\n";
	}
	if (this->enemyShipTextureB1.loadFromFile("..\\assets\\images\\InvaderB1.png"))
	{
		std::cout << "enemy Ship Texture B1 Loaded\n";
	}
	if (this->enemyShipTextureC1.loadFromFile("..\\assets\\images\\InvaderC1.png"))
	{
		std::cout << "enemy Ship Texture C1 Loaded\n";
	}
	if (this->enemyShipTextureA2.loadFromFile("..\\assets\\images\\InvaderA2.png"))
	{
		std::cout << "enemy Ship Texture A2 Loaded\n";
	}
	if (this->enemyShipTextureB2.loadFromFile("..\\assets\\images\\InvaderB2.png"))
	{
		std::cout << "enemy Ship Texture B2 Loaded\n";
	}
	if (this->enemyShipTextureC2.loadFromFile("..\\assets\\images\\InvaderC2.png"))
	{
		std::cout << "enemy Ship Texture C2 Loaded\n";
	}
	this->enemySprite.setTexture(this->enemyShipTextureA1);
	
}

void Enemy::InitBullet()
{
	if (this->enemyBulletTexture.loadFromFile("..\\assets\\images\\Bullet.png"))
	{
		std::cout << "enemy bullet Texture Loaded\n";
	}
	this->enemyBulletSprite.setTexture(this->enemyBulletTexture);
}




Enemy::Enemy()
{
	this->InitEnemy();
	this->InitBullet();
}

Enemy::~Enemy()
{
}

