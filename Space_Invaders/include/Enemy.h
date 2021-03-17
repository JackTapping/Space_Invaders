#pragma once
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

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

	//Shapes to represent the player
	sf::RectangleShape sprite;
	sf::CircleShape    Bullet;

	//when player shoots bullet objects will be put here 
	std::vector<sf::CircleShape>    BulletsContainer;
	std::vector<sf::RectangleShape> EnemyContainer;

	//Consturctor / Deconstuctor 
	Enemy();
	~Enemy();

};
