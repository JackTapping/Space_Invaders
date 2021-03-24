#pragma once
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>


/// <summary>
/// This class holds all of the objects that are needed to crate the elements that are used to represent the
/// player in the Window class
/// 
///		--Object to represent the Enemy Ship 
///		--Object to represent the Enemy Bullets
///		--Vector to hold the Enemy Bullets 
/// </summary>
/// 
class Enemy
{
private:

	//Function to set up Player upon object creation 
	void InitEnemy();
	void InitBullet();


public:
	//Textures for enemis
	sf::Texture enemyShipTextureA1;
	sf::Texture enemyShipTextureA2;
	sf::Texture enemyShipTextureB1;
	sf::Texture enemyShipTextureB2;
	sf::Texture enemyShipTextureC1;
	sf::Texture enemyShipTextureC2;
	sf::Texture enemyBulletTexture;

	//Sprites to represent the enemy
	sf::Sprite enemySprite;
	sf::Sprite enemyBulletSprite;

	//when player shoots bullet objects will be put here 
	//std::vector<sf::CircleShape>    BulletsContainer;
	std::vector<sf::Sprite> EnemySpriteContainer;


	//Consturctor / Deconstuctor 
	Enemy();
	~Enemy();

};

