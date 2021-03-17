#include "GameLogic.h"
#include "..\include\GameLogic.h"


void GameLogic::InitVeriables()
{
	/// <summary>
	/// Gives defalut values to all veriables befor the get used in the class
	/// </summary>
	this->BulletCoolDown = 30;
	this->leftOrRight = true;
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Window::player.sprite.move(-5.f,0.f);

		//resetting player if they move past the edge of the sreen
		if(Window::player.sprite.getPosition().x < 0)
		{
			Window::player.sprite.setPosition(
				static_cast<float>(0),
				static_cast<float>(Window::gameWindow->getSize().y - Window::player.sprite.getSize().y));
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
	

	if(this->BulletCoolDown > 30)
	{
		Window::player.Bullet.setPosition(
			static_cast<float>(Window::player.sprite.getPosition().x + 10),
			static_cast<float>(Window::gameWindow->getSize().y - 50)
		);
		Window::player.BulletsContainer.push_back(Window::player.Bullet);

		this->BulletCoolDown = 0;
	}
	
}
void GameLogic::UpdateBullets()
{
	/// <summary>
	/// Will up data all of the position of all the bullets inside of the BulletsContainer Vector
	/// 
	///		--Bullets will move upwards from players postion 
	///		--if a bullets hits the top of the screen it is deleted 
	///		--if a bullet hits an emeny it is deleted 
	/// </summary>
	
	int bulletIT = 0;
	int enemyIT  = 0;

	for(auto &bullet : Window::player.BulletsContainer)
	{
		//moving the  bullet
		bullet.move(0.f, -5.f);

		//deleting the bullet if it hits the top of the screen 
		if(bullet.getPosition().y < -8)
		{
			Window::player.BulletsContainer.erase(Window::player.BulletsContainer.begin() + bulletIT);
		}

		//looking to see if bullet hits enemy
		for(auto &enemy : Window::enemy.EnemyContainer)
		{
			if(bullet.getGlobalBounds().intersects(enemy.getGlobalBounds()))
			{
				Window::enemy.EnemyContainer.erase(Window::enemy.EnemyContainer.begin() + enemyIT);
  				Window::player.BulletsContainer.erase(Window::player.BulletsContainer.begin() + bulletIT);
			}
			
			enemyIT++;
			
		}
		
		bulletIT++;
		
	}
}

void GameLogic::BulletTimer()
{
	/// <summary>
	/// BulletCoolDown variable ticks up by 1 every time the game is updated
	/// variable is used to control how oftern the player can shoot
	/// </summary>
	BulletCoolDown += 1;
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
	
		for (auto& e : Window::enemy.EnemyContainer)
		{
			
			if (leftOrRight) 
			{
				e.move(2.f, 0);
			}
			else
			{
				e.move(-2.f, 0);
			}
		}

		for (auto& e : Window::enemy.EnemyContainer)
		{

			if (e.getGlobalBounds().left > Window::gameWindow->getSize().x - e.getSize().x)
			{
				this->leftOrRight = false;

				for (auto& e : Window::enemy.EnemyContainer)
				{
					e.move(0, 3.f);
				}
			}
			else if (e.getPosition().x == 0)
			{
				this->leftOrRight = true;

				for (auto& e : Window::enemy.EnemyContainer)
				{
					e.move(0, 3.f);
				}
			}
		}


	
	
}

void GameLogic::Update()
{
	this->WindowEvents();
	this->UpdatePlayer();
	this->UpdateEnemy();
	this->UpdateBullets();
	this->BulletTimer();
}

GameLogic::GameLogic()
{
	this->InitVeriables();
}

GameLogic::~GameLogic()
{
}
