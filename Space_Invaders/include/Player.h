#pragma once


#include <iostream>
#include <SFML/Graphics.hpp>


/// <summary>
/// This class holds all of the objects that are needed to crate the elements that are used to represent the
/// player in the Window class
/// 
///		--Object to represent the players Ship 
///		--Object to represent the players Bullets
///		--Vector to hold the players Bullets 
/// </summary>
class Player
{
private:
	
	//Function to set up Player upon object creation 
	void InitPlayer();
	void InitBullet();

public:

	//sprites 
	sf::Texture playerShipTexture;
	sf::Texture playerBuletTexture;

	//Sprites to represent the player
	sf::Sprite playerSprite;
	sf::Sprite playerBulletSprite;



	//Consturctor / Deconstuctor 
	Player();
	~Player();


};

