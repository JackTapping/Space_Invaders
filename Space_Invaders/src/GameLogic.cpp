#include "GameLogic.h"
#include "..\include\GameLogic.h"


void GameLogic::InitVeriables()
{
	/// <summary>
	/// Gives defalut values to all veriables befor the get used in the class
	/// </summary>
	 
	//Veriables for the player and Enemy
	this->leftOrRight = true;
	this->playerBulletTraveling = false;
	this->enemyBulletTraveling = false;
	this->bulletSpeed = 6.f;

	//Variables for the Sensor to work 
	this->sensorSize = 5;
	this->SensorSpeed = 10;
	this->SensorYlocation = Window::enemySensor.getPosition().y;
	this->SensorStopGrowing = false;
	this->SensorOffSet = 0;
	this->getNewSensorOffSet = true;

	//Veriables to deside what part of the game to update 
	this->updateMainGame = false;
	this->updateMainMenu = true;
	this->updateEndScreen = false;

	//Veriabls for the two timers used 
	this->mouseClickTimer = 0;
	this->swapTextureTimer = 0;
}

//Window
void GameLogic::WindowEvents()
{	
	// controls the events to make see if the player wants to close the game window 
	while (Window::gameWindow->pollEvent(Window::ev))
	{
		switch (Window::ev.type)
		{
		case sf::Event::Closed:
			Window::gameWindow->close();
			break;

		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
			{
				Window::gameWindow->close();
			}
			break;
		}
	}
}
const bool GameLogic::isWindowOpen() const
{
	/// <summary>
	/// Function is used in the Main cpp file, it job is to controll the main game loop 
	/// as long as the window is still open the loop will run
	/// </summary>
	/// <returns>If the game window is still open</returns>
	return Window::gameWindow->isOpen();
}

//Player 
void GameLogic::UpdatePlayer()
{
	/// <summary>
	/// This method handles the player controles
	/// 
	///			--Player can move left and right
	///			--player can not move of the edge of the windwo 
	///			--player can shoot 
	/// 
	///			--Player can show or hide the Sensor that is used to contorl the Emeny shooting 
	///				--being able to see the senor was for debuging perposes and is not intened to be
	///				  Used if a player was playing the game for real
	/// </summary>

	//if statment for controlling left and right movement 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Window::player.playerSprite.move(-5.f, 0.f);

		//resetting player if they move past the edge of the sreen
		if (Window::player.playerSprite.getPosition().x < 0)
		{
			Window::player.playerSprite.setPosition(
				static_cast<float>(0),
				static_cast<float>(Window::gameWindow->getSize().y - Window::player.playerSprite.getGlobalBounds().height));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Window::player.playerSprite.move(5.f, 0.f);

		//resetting player if they move past the edge of the sreen
		if (Window::player.playerSprite.getPosition().x > Window::gameWindow->getSize().x - Window::player.playerSprite.getGlobalBounds().width)
		{
			Window::player.playerSprite.setPosition(
				static_cast<float>(Window::gameWindow->getSize().x - Window::player.playerSprite.getGlobalBounds().width),
				static_cast<float>(Window::gameWindow->getSize().y - Window::player.playerSprite.getGlobalBounds().height));
		}
	}

	//if statment for calling the ShootBullet function when the player press Space  
	//and there is not a bullet all readyon screen 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->playerBulletTraveling == false)
	{
		
		this->ShootBullet();
	}

	//Pressing Q will show the enemy sensor 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{

		Window::drawEnemySensor = true;
	}

	//Pressing w wil stop the window from showing the enemy sensor 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{

		Window::drawEnemySensor = false;
	}
	
}
void GameLogic::ShootBullet()
{
	/// <summary>
	/// If the player press Space bar then a bullet object will be placed just above the player and the UpdateBullet 
	/// Function will make the bullet travle upwards from the player. 
	/// 
	///		--playerBulletTraveling boll is set to true 
	///		--Bullet object postion is set just above the player
	///		--Bullet Fireing sound is played
	/// </summary>

	this->playerBulletTraveling = true;
	Window::drawPlayerBullet = true;
	Window::player.playerBulletSprite.setPosition(
		static_cast<float>(Window::player.playerSprite.getPosition().x +26),
		static_cast<float>(Window::gameWindow->getSize().y - 50));
	Window::shipFireSound.play();
	

}
void GameLogic::UpdatePlayerBullet()
{
	/// <summary>
	/// Will update the players bullet if the player has fired a bullet
	/// 
	///		--Bullets will move upwards from players postion 
	///		--If the bullet hits the top of the screen it is "deleted" 
	/// 
	///		--If the bullet hits an emeny:
	///			--playerBulletTraveling is set to false 
	///			--UpdateScore Function is called 
	///			--Bullet is "Deleted"
	///			--Enemy hit sound is played
	///			--Enemy is poped form its vector 
	///			--Game checks to see if any enemys are still alive 
	/// 
	///		--If the bullet hits cover:
	///			--playerBulletTraveling is set to false 
	///			--Bullet is "Deletd"
	///			--Cover section is "Deletd"
	/// 
	///		--If something is "Deleted":
	/// 		--they get stop drawn by the window
	///			--There object position is moved of screen 
	/// 
	/// </summary>

	// used as an itorator for the EnemyColletion vector and Cover array 
	//(Used becase of an outof bounds error that was happening)
	int enemyIT = 0;
	int coverIT = 0;

	//moving the bullet upwards from the player 
	Window::player.playerBulletSprite.move(0.f, -this->bulletSpeed);

	//"deleting" the bullet if it hits the top of the screen 
	if (Window::player.playerBulletSprite.getPosition().y < -8)
	{
		this->playerBulletTraveling = false;
		Window::drawPlayerBullet = false;
		Window::player.playerBulletSprite.setPosition(0, 0);
	}

	//Cheking each enemy to see if the bullet has hit one of them 
	for (auto& enemy : Window::enemy.EnemySpriteContainer)
	{
		//seeing bullets global bounds and enemys intersect 
		if (Window::player.playerBulletSprite.getGlobalBounds().intersects(enemy.getGlobalBounds()))
		{
			this->playerBulletTraveling = false;
			this->UpdateScore();

			Window::drawPlayerBullet = false;
			Window::player.playerBulletSprite.setPosition(0, 0);
			Window::enemyHitSound.play();
			Window::enemy.EnemySpriteContainer.erase(Window::enemy.EnemySpriteContainer.begin() + enemyIT);

			//Checking to see if there are any more enemies left on screen 
			if (Window::enemy.EnemySpriteContainer.size() == 0) 
			{
				Window::drawMainGame = false;
				Window::drawEndScreen = true;

				this->updateMainGame = false;
				this->updateEndScreen = true;
			}

		}
		enemyIT++;
	}

	//looking to see if bullet hits cover
	for (auto& cover : Window::cover.destuctableCoverContainer)
	{
		if (Window::player.playerBulletSprite.getGlobalBounds().intersects(cover.getGlobalBounds()))
		{
			Window::cover.destuctableCoverContainer[coverIT].setPosition(-10.f, -10.f);

			this->playerBulletTraveling = false;
			Window::drawPlayerBullet = false;
			Window::player.playerBulletSprite.setPosition(0, 0);
		}
		coverIT++;
	}
}

//Enemy
void GameLogic::UpdateEnemy()
{
	/// <summary>
	/// Function will control:
	///		
	///		--LeftOrRight bool: 
	///			-- if bool is true enamies move to the left 
	///			-- if bool is true enamies move to the right
	/// 
	///		--enemy moves:
	///			--Left untill they hit the side of the screen
	///			--Then down a setp 
	///			--Then Right untill they hit the side of the screen
	///			--If enemy hits the side of the screen there Sprite texture is update
	/// 
	///		--Enemy Hits cover:
	///			--Cover gets "Deletd"
	///		
	///			
	/// </summary>
	int enemyIT = 0;
	for (auto& enemy : Window::enemy.EnemySpriteContainer)
	{

		//moving the enemy left to right
		if (leftOrRight)
		{
			enemy.move(2.f, 0);

			//Updateing sprites
			if (enemy.getTexture() == &Window::enemy.enemyShipTextureA1)
			{
				enemy.setTexture(Window::enemy.enemyShipTextureA2);
			}
			if (enemy.getTexture() == &Window::enemy.enemyShipTextureB1)
			{
				enemy.setTexture(Window::enemy.enemyShipTextureB2);
			}
			if (enemy.getTexture() == &Window::enemy.enemyShipTextureC1)
			{
				enemy.setTexture(Window::enemy.enemyShipTextureC2);
			}

		}
		else
		{
			enemy.move(-2.f, 0);

			if (enemy.getTexture() == &Window::enemy.enemyShipTextureA2)
			{
				enemy.setTexture(Window::enemy.enemyShipTextureA1);
			}
			if (enemy.getTexture() == &Window::enemy.enemyShipTextureB2)
			{
				enemy.setTexture(Window::enemy.enemyShipTextureB1);
			}
			if (enemy.getTexture() == &Window::enemy.enemyShipTextureC2)
			{
				enemy.setTexture(Window::enemy.enemyShipTextureC1);
			}
		}

		//looking to see if enemy hits cover
		int coverIT = 0;
		for (auto& cover : Window::cover.destuctableCoverContainer)
		{

			if (enemy.getGlobalBounds().intersects(cover.getGlobalBounds()))
			{
				std::cout << "Enemy ID: " << enemyIT << " " << "CoverID: " << coverIT << "\n";
				Window::cover.destuctableCoverContainer[coverIT].setPosition(-10.f, -10.f);

			}

			
			coverIT++;

		}

		//looking to see if the player touches an enemy
		if (Window::player.playerSprite.getGlobalBounds().intersects(enemy.getGlobalBounds()))
		{
			Window::lives = 0;
			Window::livesText.setString("Lives: " + std::to_string(this->lives));

			Window::drawMainGame = false;
			Window::drawEndScreen = true;

			this->updateMainGame = false;
			this->updateEndScreen = true;
		}

		enemyIT++;
	}



	for (auto& enemy : Window::enemy.EnemySpriteContainer)
	{

		if (enemy.getGlobalBounds().left > Window::gameWindow->getSize().x - enemy.getGlobalBounds().width)
		{
			this->leftOrRight = false;

			for (auto& e : Window::enemy.EnemySpriteContainer)
			{
				e.move(0, 3.f);
				
			}
			Window::enemySensorLimiter.move(0, 3.f);
		}
		else if (enemy.getPosition().x < 0)
		{
			this->leftOrRight = true;

			for (auto& e : Window::enemy.EnemySpriteContainer)
			{
				e.move(0, 3.f);
			}
			Window::enemySensorLimiter.move(0, 3.f);

		}
	}

	
}
void GameLogic::UpdateEnemySensor()
{
	/// <summary>
	/// Will Shoot a bullet down towards the player if the sensor hits an enemy
	///
	///		--A new random offset is picked for the sensor 
	///			--makes it hard for the player to know were the next bullet will spawn 
	/// 
	///		--Looks to see if the sensor has hit the enemySensorLimiter object:
	///			--used to make sure the sensor dosent go past the last enemy or bullets could spawn of screen 
	///			--if it hits the sensor is reset so player will not be able to use the limitier 
	///			  as a way guessing were a bullet will spawn 
	///		
	///		--Check if the offset is even or not:
	///			--If it is even then sensor will be place to the right of the payers center 
	///			--If it is odd then the sensro will be placed to the left 
	///			--used to make sure the player can not guess were a bullet will spawn 
	///			--Aslo because it is offset from the player it will allways make sure the bullet
	///			  spawns close to the player
	/// 
	///		--Senore has it size reste based on the Sensor Size + Sensor Speed veribles 
	/// 
	///		--If sensor hits an enemy:
	///			--Enemy Bullet object will be placed at the point were the intersect is firts detected 
	///			--Enemy bullet fire sound will be played 
	///			-- sensor will be reset 
	/// </summary>
	
	//looking to see if sensor touches its limmiter 
	if(this->getNewSensorOffSet)
	{
		this->SensorOffSet = rand() % 100;
		this->getNewSensorOffSet = false;
	}

	if (Window::enemySensor.getGlobalBounds().intersects(Window::enemySensorLimiter.getGlobalBounds()))
	{
		this->getNewSensorOffSet = true;
		this->sensorSize = 5;
	}

	if(this->SensorOffSet %2 == 0)
	{
		Window::enemySensor.setPosition(
			sf::Vector2f((Window::player.playerSprite.getPosition().x +20) + this->SensorOffSet,
				SensorYlocation - sensorSize));
	}
	else
	{
		Window::enemySensor.setPosition(
			sf::Vector2f(Window::player.playerSprite.getPosition().x - this->SensorOffSet,
				SensorYlocation - sensorSize));
	}
	Window::enemySensor.setSize(sf::Vector2f(3, sensorSize));
	this->sensorSize += this->SensorSpeed;
	

	if(this->enemyBulletTraveling == false)
	{
		for (auto& enemy : Window::enemy.EnemySpriteContainer)
		{

			if (Window::enemySensor.getGlobalBounds().intersects(enemy.getGlobalBounds()))
			{
				Window::enemy.enemyBulletSprite.setPosition(Window::enemySensor.getPosition().x,Window::enemySensor.getPosition().y + 10);
				this->enemyBulletTraveling = true;
				Window::drawEnemyBullet = true;
				this->getNewSensorOffSet = true;
				this->sensorSize = 5;
				Window::enemyFireSound.play();
			}
		}
	}
}
void GameLogic::UpdateEnemyBullet()
{
	
	//Making the bullet go down
	if (this->enemyBulletTraveling)
	{
		Window::enemy.enemyBulletSprite.move(0.f, this->bulletSpeed);
	}

	//Looking to see if the bullet has hit the bottom of the screen 
	if (Window::enemy.enemyBulletSprite.getPosition().y > Window::gameWindow->getSize().y)
	{
		this->enemyBulletTraveling = false;
		Window::drawEnemyBullet = false;
		Window::enemy.enemyBulletSprite.setPosition(0.f, 0.f);
	}

	//Looking to see if the player has been hit
	if (Window::enemy.enemyBulletSprite.getGlobalBounds().intersects(Window::player.playerSprite.getGlobalBounds()))
	{
		this->enemyBulletTraveling = false;
		this->UpdateLives();

		Window::shipHitSound.play();
		Window::drawEnemyBullet = false;
		Window::enemy.enemyBulletSprite.setPosition(0.f, 0.f);

	}

	//looking to see if bullet hits cover
	int coverIT = 0;
	for (auto& cover : Window::cover.destuctableCoverContainer)
	{

		if (Window::enemy.enemyBulletSprite.getGlobalBounds().intersects(cover.getGlobalBounds()))
		{
			Window::cover.destuctableCoverContainer[coverIT].setPosition(-10.f, -10.f);

			this->enemyBulletTraveling = false;
			Window::drawEnemyBullet = false;
			Window::enemy.enemyBulletSprite.setPosition(0.f, 0.f);

		}

		coverIT++;

	}
}

//UI
void GameLogic::UpdateScore()
{
	/// <summary>
	/// Every time the player hits an enemy this function will be called to incresse there score 
	/// </summary>
	Window::score += 50;
	Window::scoreText.setString("Score: " + std::to_string(this->score));
}
void GameLogic::UpdateLives()
{
	/// <summary>
	/// Every time a player is hit by a bullet this function will be called to decrese there lives by one
	/// 
	///		--If lives = 0 then it will be game over for the player 
	/// </summary>
	Window::lives--;
	Window::livesText.setString("Lives: " + std::to_string(this->lives));

	if(Window::lives == 0)
	{
		Window::drawMainGame = false;
		Window::drawEndScreen = true;

		this->updateMainGame = false;
		this->updateEndScreen = true;
	}
}

//Mouse
void GameLogic::UpdateMousePosition()
{
	/// <summary>
	/// This function is used to track the loction of the mouse for the Main menu and End Screen 
	/// 
	///		--If the mouse intersects with the button:
	///			--Button will turn green 
	///			--Player can click on button 
	/// 
	///		--If player clicks on the button:
	///			--In main menu player will be taken to the game 
	///			--In End Screen player will be taken back the the Main menu 
	/// 
	///		--MouselickTimer variable is used here becasue of a bug were the player would click the back button on the 
	///		  End Screen and the main menu Play button would load in to fast for the player to take there finger of the 
	///		  Mouse button and the game would instanly start. The veriable gives a bit of a cool down timer between mouse
	///		  cliks so this cant happen any more 
	///		  
	/// </summary>
	this->mousePosWindow = sf::Mouse::getPosition(*Window::gameWindow);
	this->mousePosView = Window::gameWindow->mapPixelToCoords(this->mousePosWindow);

	if(Window::Button.getGlobalBounds().contains(this->mousePosView))
	{
		Window::Button.setOutlineColor(sf::Color::Green);
		Window::menuButtonText.setFillColor(sf::Color::Green);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->mouseClickTimer > 30)
		{
			if(Window::drawMainMenu)
			{
				this->mouseClickTimer = 0;

				Window::drawMainMenu = false;
				Window::drawMainGame = true;

				this->updateMainMenu = false;
				this->updateMainGame = true;

				Window::lives = 3;
				Window::score = 0;
				Window::livesText.setString("Lives: " + std::to_string(this->lives));
				Window::scoreText.setString("Score: " + std::to_string(this->score));
			}
			else if(Window::drawEndScreen)
			{
				this->mouseClickTimer = 0;

				Window::drawEndScreen = false;
				Window::drawMainMenu = true;
				Window::RedrawGame();

				this->updateMainMenu = true;
				this->updateEndScreen = false;
			}
		}
	}
	else
	{
		Window::Button.setOutlineColor(sf::Color::White);
		Window::menuButtonText.setFillColor(sf::Color::White);
	}
}

//Function that are called to update the timer veriables 
void GameLogic::UpdateMousClickTimer()
{
	this->mouseClickTimer++;
}
void GameLogic::UpdateSwapTextureTimer()
{
	this->swapTextureTimer++;
}

//Function that restes the veriabls when a game has been completed 
void GameLogic::ResetGameLogic()
{
	this->InitVeriables();

	//This is reste here becase of a bug were the sensor would lose track of the players Y location 
	//and start spwaning higher than it should do every time a new game is played 
	Window::enemySensorLimiter.setPosition(static_cast<float>(0), static_cast<float>(44));
}




//Function that calls all other update functions 
void GameLogic::Update()
{
	

	this->WindowEvents();
	if(this->updateMainMenu)
	{
		this->UpdateMousePosition();
		this->UpdateMousClickTimer();
	}
	else if(this->updateMainGame)
	{
		this->UpdateMousePosition();
		this->UpdatePlayer();
		this->UpdateEnemy();
		this->UpdateEnemySensor();
		this->UpdatePlayerBullet();
		this->UpdateEnemyBullet();
		this->UpdateSwapTextureTimer();
	}
	else
	{
		this->enemySensor.setPosition(
			static_cast<float>(this->gameWindow->getSize().x / 2),
			static_cast<float>(this->gameWindow->getSize().y - this->player.playerSprite.getGlobalBounds().height)
		);
		this->ResetGameLogic();
		this->UpdateMousePosition();
		this->UpdateMousClickTimer();
	}
	
}

GameLogic::GameLogic()
{
	this->InitVeriables();
}

GameLogic::~GameLogic()
{
}
