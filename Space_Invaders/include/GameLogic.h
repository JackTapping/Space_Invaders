#pragma once

#include <Window.h>

/// <summary>
/// This class is used to contorl all of the logic that will be used in the game
///		
///		X = Need doing
///		O = Done
/// 
///		--Updates the Game State: <-- X		
/// 
///			--Checks to see if the game window is still open  <-- O	
/// 
///			--Player Inputs: <-- O	
///				--Player can Move left and Right <-- O	
///				--Player can not move of the screen <-- O	
///				--Player can Shoot a bullet <-- O
///				--Timer to Control how offten a player can Shoot <--O	
/// 
///			--Enemy Actions: <-- X	
///				--Enemy can move left and right and down <-- O	
///				--If Enemy hits one side of the screen it moves down then goes the oppiset direction <-- O	
///				--Enemy Will Shoot Bullets down at ransom intervales <-- X	
/// 
///			--Object Collsion Detetion: <-- X	
///				-- If bullet goes of screen it is deleted <-- 0	
///				-- If bullet hits an enemy they are both deleted <-- X	
///				-- If bullet hits cover cover takes damge and bullet is deleted<-- X	
///				-- If bullet hits Player they lose a life <-- X	
///				-- If enemy hits cover the cover is deleted <-- X	
///  
///     
///			--Win/Loose Condition: <-- X	
///				--If player kills all enemys they win <-- X	
///				--If player runs out of lives they loose <-- X	
///
/// </summary>
class GameLogic : public Window
{
private:
	
	//Variables 
	int BulletCoolDown;
	bool leftOrRight;

	//Functions for set up
	void InitVeriables();

public:
	
	//functions for the window 
	void WindowEvents();
	const bool isWindowOpen() const;

	//Functions to Update Game Objects 
	void UpdatePlayer();

	void ShootBullet();
	void UpdateBullets();
	void BulletTimer();

	void UpdateEnemy();

	void Update();

	GameLogic();
	~GameLogic();
};

