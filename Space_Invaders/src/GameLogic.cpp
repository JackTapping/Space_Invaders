#include "GameLogic.h"
#include "..\include\GameLogic.h"


void GameLogic::InitVeriables()
{
	/// <summary>
	/// Gives defalut values to all veriables befor the get used in the class
	/// </summary>
	this->leftOrRight = true;
	this->playerBulletTraveling = false;
	this->enemyBulletTraveling = false;
	
	this->bulletSpeed = 6.f;

	//Variables for the Sensor to work 
	this->sensorSize = 5;
	this->SensorSpeed = 10;
	this->SensorYlocation = Window::enemySensor.getPosition().y;
	this->HowManySenesorDetects = 0;
	this->SensorStopGrowing = false;
	this->SensorOffSet = 0;
	this->getNewSensorOffSet = true;
}

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
	return Window::gameWindow->isOpen();
}

void GameLogic::UpdatePlayer()
{
	/// <summary>
	/// This method handles the player contoles
	/// 
	///			--Player can move left and right
	///			--player can not move of the edge of the windwo 
	///			--player can shoot 
	/// </summary>

	//if statment for controlling left and right movement 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Window::player.sprite.move(-5.f, 0.f);

		//resetting player if they move past the edge of the sreen
		if (Window::player.sprite.getPosition().x < 0)
		{
			Window::player.sprite.setPosition(
				static_cast<float>(0),
				static_cast<float>(Window::gameWindow->getSize().y - Window::player.sprite.getSize().y));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Window::player.sprite.move(5.f, 0.f);

		//resetting player if they move past the edge of the sreen
		if (Window::player.sprite.getPosition().x > Window::gameWindow->getSize().x - Window::player.sprite.getSize().x)
		{
			Window::player.sprite.setPosition(
				static_cast<float>(Window::gameWindow->getSize().x - Window::player.sprite.getSize().x),
				static_cast<float>(Window::gameWindow->getSize().y - Window::player.sprite.getSize().y));
		}
	}

	//if statment for contorlling shooting 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->playerBulletTraveling == false)
	{
		
		this->ShootBullet();
	}
}
void GameLogic::ShootBullet()
{
	/// <summary>
	/// If the player press Space bar then a bullet object will be placed in the Spawn bullet Vector
	/// 
	///		--Bullet object postion is set just abover the player
	///		--Bullet object is placed in BulletContainer Vector
	///		--Buller Cool Down is reset
	/// 
	///		--Bullet object and vector can be found in the Player class 
	/// </summary>

	this->playerBulletTraveling = true;
	Window::drawPlayerBullet = true;
	Window::player.Bullet.setPosition(
		static_cast<float>(Window::player.sprite.getPosition().x + 10),
		static_cast<float>(Window::gameWindow->getSize().y - 50));
	

}
void GameLogic::UpdatePlayerBullet()
{
	/// <summary>
	/// Will update all of the position of all the bullet and detect enemy collistion 
	/// 
	///		--Bullets will move upwards from players postion 
	///		--if a bullets hits the top of the screen it is deleted 
	///			--Bullet will stop being drawn by the window
	///			--bulet gets its postion set of screen 
	/// 
	///		--if a bullet hits an emeny it is deleted 
	/// </summary>

	// used as an itorator for the EnemyColletion vector 
	int enemyIT = 0;
	int coverIT = 0;

	//moving the bullet upwards from the player 
	Window::player.Bullet.move(0.f, -this->bulletSpeed);

	//deleting the bullet if it hits the top of the screen 
	if (Window::player.Bullet.getPosition().y < -8)
	{
		this->playerBulletTraveling = false;
		Window::drawPlayerBullet = false;
		Window::player.Bullet.setPosition(0, 0);
	}

	//looking to see if bullet hits enemy
	for (auto& enemy : Window::enemy.EnemySpriteContainer)
	{

		if (Window::player.Bullet.getGlobalBounds().intersects(enemy.getGlobalBounds()))
		{
			Window::enemy.EnemySpriteContainer.erase(Window::enemy.EnemySpriteContainer.begin() + enemyIT);

			this->playerBulletTraveling = false;
			Window::drawPlayerBullet = false;
			Window::player.Bullet.setPosition(0, 0);

		}

		enemyIT++;

	}

	//looking to see if bullet hits cover
	for (auto& cover : Window::cover.destuctableCoverContainer)
	{

		if (Window::player.Bullet.getGlobalBounds().intersects(cover.getGlobalBounds()))
		{
			Window::cover.destuctableCoverContainer.erase(Window::cover.destuctableCoverContainer.begin() + coverIT);

			this->playerBulletTraveling = false;
			Window::drawPlayerBullet = false;
			Window::player.Bullet.setPosition(0, 0);

		}

		coverIT++;

	}


	}


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
	/// 
	///		--Enemy Shoots:
	///		
	///			
	/// </summary>
	int enemyIT = 0;
	for (auto& enemy : Window::enemy.EnemySpriteContainer)
	{

		if (leftOrRight)
		{
			enemy.move(20.f, 0);

		}
		else
		{
			enemy.move(-20.f, 0);
		}

		//looking to see if enemy hits cover
		int coverIT = 0;
		for (auto& cover : Window::cover.destuctableCoverContainer)
		{

			if (enemy.getGlobalBounds().intersects(cover.getGlobalBounds()))
			{
				std::cout << "Enemy ID: " << enemyIT << " " << "CoverID: " << coverIT << "\n";
				Window::cover.destuctableCoverContainer.erase(Window::cover.destuctableCoverContainer.begin() + coverIT);

			}

			
			coverIT++;

		}
		enemyIT++;
	}



	for (auto& e : Window::enemy.EnemySpriteContainer)
	{

		if (e.getGlobalBounds().left > Window::gameWindow->getSize().x - e.getSize().x)
		{
			this->leftOrRight = false;

			for (auto& e : Window::enemy.EnemySpriteContainer)
			{
				e.move(0, 3.f);
				
			}
			Window::enemySensorLimiter.move(0, 3.f);
		}
		else if (e.getPosition().x < 0)
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
	///		--Enemy Shoots at Player:
	///			--Enemy Sensor grows up close to the player
	///			--Once Sensor toucher an enemy it spawns a bullet 
	///			--Bullet travles stright down from were it spawned
	///			--If the Bullet hits something it will stop been drawn an 
	///			  have its postition sent of screen. 
	///			--If Sensor Touches Limiter it will stop growing 
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
			sf::Vector2f((Window::player.sprite.getPosition().x +20) + this->SensorOffSet,
				SensorYlocation - sensorSize));
	}
	else
	{
		Window::enemySensor.setPosition(
			sf::Vector2f(Window::player.sprite.getPosition().x - this->SensorOffSet,
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
				Window::enemy.Bullet.setPosition(Window::enemySensor.getPosition().x,Window::enemySensor.getPosition().y + 10);
				this->enemyBulletTraveling = true;
				Window::drawEnemyBullet = true;
				this->getNewSensorOffSet = true;
				this->sensorSize = 5;
				HowManySenesorDetects++;
			}
		}
	}
	
	
	this->HowManySenesorDetects = 0;
}
void GameLogic::UpdateEnemyBullet()
{
	if (this->enemyBulletTraveling)
	{
		Window::enemy.Bullet.move(0.f, this->bulletSpeed);
	}

	if(Window::enemy.Bullet.getPosition().y > Window::gameWindow->getSize().y)
	{
		this->enemyBulletTraveling = false;
		Window::drawEnemyBullet = false;
		Window::enemy.Bullet.setPosition(0.f, 0.f);
	}

	if(Window::enemy.Bullet.getGlobalBounds().intersects(Window::player.sprite.getGlobalBounds()))
	{
		this->enemyBulletTraveling = false;
		Window::drawEnemyBullet = false;
		Window::enemy.Bullet.setPosition(0.f, 0.f);
	}

	//looking to see if bullet hits cover
	int coverIT = 0;
	for (auto& cover : Window::cover.destuctableCoverContainer)
	{

		if (Window::enemy.Bullet.getGlobalBounds().intersects(cover.getGlobalBounds()))
		{
			Window::cover.destuctableCoverContainer.erase(Window::cover.destuctableCoverContainer.begin() + coverIT);

			this->enemyBulletTraveling = false;
			Window::drawEnemyBullet = false;
			Window::enemy.Bullet.setPosition(0.f, 0.f);

		}

		coverIT++;

	}
}




void GameLogic::Update()
{
	this->WindowEvents();
	this->UpdatePlayer();
	this->UpdateEnemySensor();
	this->UpdateEnemy();
	this->UpdatePlayerBullet();
	this->UpdateEnemyBullet();
}

GameLogic::GameLogic()
{
	this->InitVeriables();
}

GameLogic::~GameLogic()
{
}
