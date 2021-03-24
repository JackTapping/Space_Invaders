#pragma once

#include <Window.h>

/// <summary>
/// This class is used to contorl all of the logic that will be used in the game
///		
///		--Updates the Game State: 		
/// 
///			--Checks to see if the game window is still open 	
/// 
///			--Player Inputs: 	
///				--Player can Move left and Right 
///				--Player can not move of the screen 	
///				--Player can Shoot a bullet 
///				--Timer to Control how offten a player can Shoot 	
/// 
///			--Enemy Actions: 	
///				--Enemy can move left and right and down 	
///				--If Enemy hits one side of the screen it moves down then goes the oppiset direction 	
///				--Enemy Will Shoot Bullets down at set intervales 	
/// 
///			--Object Collsion Detetion:	
///				-- If bullet goes of screen it is deleted 	
///				-- If bullet hits an enemy they are both deleted 	
///				-- If bullet hits cover cover takes damge and bullet is deleted<	
///				-- If bullet hits Player they lose a life 	
///				-- If enemy hits cover the cover is deleted 	
///  
///     
///			--Win/Loose Condition: 	
///				--If player kills all enemys they win 
///				--If player runs out of lives they loose 
///				--Reset the games Logic if eather of these happens 	
///
/// </summary>
class GameLogic : public Window
{
private:

	//Variables 
	bool leftOrRight;
	bool playerBulletTraveling;
	bool enemyBulletTraveling;
	bool getNewSensorOffSet;
	bool SensorStopGrowing;

	float bulletSpeed;

	float sensorSize;
	float SensorSpeed;
	float SensorYlocation;
	int	  SensorOffSet;
	
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	bool updateMainMenu;
	bool updateMainGame;
	bool updateEndScreen;

	int  mouseClickTimer;
	int swapTextureTimer;

	//Functions for set up
	void InitVeriables();

public:

	//functions for the window 
	void WindowEvents();
	const bool isWindowOpen() const;

	//Functions to Update Game Objects 
	void UpdatePlayer();

	void ShootBullet();
	void UpdatePlayerBullet();
	void UpdateEnemyBullet();

	void UpdateEnemy();
	void UpdateEnemySensor();

	void UpdateScore();
	void UpdateLives();

	void UpdateMousePosition();

	void UpdateMousClickTimer();
	void UpdateSwapTextureTimer();

	void ResetGameLogic();

	void Update();

	GameLogic();
	~GameLogic();
};

