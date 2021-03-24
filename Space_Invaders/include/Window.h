#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <Player.h>
#include <Enemy.h>
#include <Cover.h>


/// <summary>
/// This class is in change of everything to do with the game window and objects that will be shown on it  
///		
///		--Contorles the size, style and name of the window 
///		--Initializes all values for on screen elements
///		--Holds Objects used for the Play and Back Button 
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
	void InitEnemySensor();
	void InitCover();
	void InitSound();
	void InitObjectsForText();
	void InitMusic();

public:
	//Variables for Game window to work
	sf::RenderWindow* gameWindow;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Bool used to choose if some element should be drawn 
	bool drawPlayerBullet;
	bool drawEnemyBullet;
	bool drawEnemySensor;
	bool drawMainMenu;
	bool drawMainGame;
	bool drawEndScreen;

	//Game Objects 
	Player player;
	Enemy enemy;
	Cover cover;

	//shapes used to sense were an enemy is 
	sf::RectangleShape enemySensor;
	sf::RectangleShape enemySensorLimiter;

	//Objects needed for Sound effects
	sf::SoundBuffer shipFireBuffer;
	sf::SoundBuffer shipHitBuffer;
	sf::SoundBuffer enemyFireBuffer;
	sf::SoundBuffer enemyHitBuffer;

	sf::Sound shipFireSound;
	sf::Sound shipHitSound;
	sf::Sound enemyFireSound;
	sf::Sound enemyHitSound;

	//Objects used to play the back ground music 
	sf::Music gameMusic;
	sf::Music mainMenuMusic;
	sf::Music endScreenMusic;

	//Objects that will be displayed on the window for UI & verables to be used to update the text 
	sf::RectangleShape Button;
	sf::Font gameFont;

	sf::Text menuButtonText;
	sf::Text menuHelpText;
	sf::Text scoreText;
	sf::Text livesText;
	sf::Text winLoseText;

	int lives;
	int score;

	
	


	//Constructor / Deconstructor
	Window();
	~Window();

	//Function to Darw individual elements 
	void RenderMenu();

	void RenderPlayer();
	void RenederPlayerBullet();

	void RenderEnemy();
	void RenderEnemySensor();
	void RenderEnemyBullet();

	void RenderGameText();

	void RenderCover();

	void RedrawGame();

	void PlayMusic();

	//Functions to update the game state and Draw all of the elements 
	void Render();
};

