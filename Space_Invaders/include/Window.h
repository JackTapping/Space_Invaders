#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <Player.h>
#include <Enemy.h>


/// <summary>
/// This class is in change of everything to do with the game window and objects that will be shown on it  
///		
///		--Contorles the size, style and name of the window 
///		--Initializes all values for on screen elements
///		--Renders Sprites 
///		
/// </summary>
class Window
{

private:

	
	
	//Functions for Object Setp up
	void InitVariables();
	void InitWindow();
	void InitPlayer();
	void InitEnemies();

	

public:
	//Variables for Game window and Events
	sf::RenderWindow* gameWindow;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Game Objects 
	Player player;
	Enemy enemy;

	//Constructor / Deconstructor
	Window();
	~Window();

	//Function to Darw individual elements 
	void RenderPlayer();
	void RenederBullet();

	void RenderEnemy();

	//Functions to update the game state and Draw all of the elements 
	void Render();
};

