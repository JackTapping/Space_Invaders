#include "Window.h"
#include "..\include\Window.h"

//Initialization Functions 
void Window::InitVariables()
{
	// settign up the variables for the game window
	this->gameWindow = nullptr;

	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->drawPlayerBullet = false;
	this->drawEnemyBullet = false;
}
void Window::InitWindow()
{
	//creating the game window 
	this->gameWindow = new sf::RenderWindow(this->videoMode, "Space Invaders", sf::Style::Default);
	this->gameWindow->setFramerateLimit(60);
}
void Window::InitPlayer()
{
	// Sets the players loction at the bottom of the screen once the game starts 
	this->player.sprite.setPosition(
		static_cast<float>(this->gameWindow->getSize().x / 2),
		static_cast<float>(this->gameWindow->getSize().y - this->player.sprite.getSize().y)
	);
}
void Window::InitEnemies()
{
	/// <summary>
	/// Function will spawn all enemies on the screen at the start of the game.
	/// 
	///		--enemies will be soted in Enemy Collection Vector that can be found in the Enemy class
	///		--enmies will be in rows and collumns 
	///			-- once one row reaches the end of the screen new row starts under it 
	///			-- rows and columns will be padded out to create space on the screen 
	///			--The scaner shape will be pointed placed in the middel of an enemy facing down 
	/// </summary>

	// variables for the padding 
	int columnPadding = 100;
	int rowPadding = 10;
	int numberOfEnemies = 0;

	// loop will run untill 25 enemies are on screen 
	while (numberOfEnemies < 55)
	{
		//if condition to check if the next enemy placed will not be to close to the edge of the screen.
		if (columnPadding + 100 < this->gameWindow->getSize().x)
		{
			//setting the enemies position and adding it to the Vector 
			this->enemy.sprite.setPosition(static_cast<float>(columnPadding), static_cast<float>(rowPadding));
			this->enemy.EnemySpriteContainer.push_back(this->enemy.sprite);

			//Updateing the column padding so the next enemy is 10 pixels away from the last one 
			columnPadding += this->enemy.sprite.getSize().x + 10;
		}
		else
		{
			columnPadding = 100;
			rowPadding += this->enemy.sprite.getSize().y + 10;
		}

		numberOfEnemies++;
	}


}
void Window::InitEnemySensor()
{

	/// <summary>
	/// Sets up the Rectangle shapes that are used to sense enemies 
	/// 
	///		--enemySensor starts in the center of the player 
	///		--enemySeneor Limmiter starts at the bottom of the top layer of enemies 
	/// </summary>
	
	this->enemySensor.setSize(sf::Vector2f(3.f, 3.f));
	this->enemySensor.setFillColor(sf::Color::Magenta);

	this->enemySensorLimiter.setSize(sf::Vector2f(this->gameWindow->getSize().x, 3.f));
	this->enemySensorLimiter.setFillColor(sf::Color::Magenta);

	this->enemySensor.setPosition(
		static_cast<float>(this->gameWindow->getSize().x / 2),
		static_cast<float>(this->gameWindow->getSize().y - this->player.sprite.getSize().y)
	);

	this->enemySensorLimiter.setPosition(static_cast<float>(0), static_cast<float>(44));
}

void Window::InitCover()
{
	/// <summary>
	/// Adds 3 layers of cover next to the bottom of the screen for the player to use 
	/// </summary>

	// variables for the padding 
	float columnOffset = this->cover.sprite.getSize().x + 65.f;
	float rowOffset = this->cover.sprite.getSize().y + 475.f;
	int numberOfCover = 0;

	// loop will run untill all cover is on screen 
	while (numberOfCover < 138)
	{
		
			//setting the enemies position and adding it to the Vector 
			this->cover.sprite.setPosition(static_cast<float>(columnOffset), static_cast<float>(rowOffset));
			this->cover.destuctableCoverContainer.push_back(this->cover.sprite);

			if(numberOfCover == 15 || numberOfCover == 61 || numberOfCover == 107)
			{
				columnOffset += 100.f;
			}
			else if (numberOfCover == 30 || numberOfCover == 76 || numberOfCover == 122)
			{
			
				columnOffset += 100.f;
			}

			if(numberOfCover == 45 || numberOfCover == 91)
			{
				rowOffset += this->cover.sprite.getSize().y;
				columnOffset = this->cover.sprite.getSize().x + 55.f;
			}
			columnOffset += this->cover.sprite.getSize().x;

		numberOfCover++;
	}

}


//Constructor / Deconstructor 
Window::Window()
{
	this->InitVariables();
	this->InitWindow();
	this->InitPlayer();
	this->InitEnemies();
	this->InitEnemySensor();
	this->InitCover();
}
Window::~Window()
{
	delete this->gameWindow;
}


// Indevidual Object Rendering functions 
void Window::RenderPlayer()
{
	this->gameWindow->draw(this->player.sprite);
}
void Window::RenederPlayerBullet()
{
	if (this->drawPlayerBullet) 
	{
		this->gameWindow->draw(this->player.Bullet);
	}
	
}
void Window::RenderEnemy()
{
	for (auto &e : enemy.EnemySpriteContainer)
	{
		this->gameWindow->draw(e);
	}

}
void Window::RenderEnemySensor()
{
	this->gameWindow->draw(this->enemySensor);
	this->gameWindow->draw(this->enemySensorLimiter);
}
void Window::RenderEnemyBullet()
{
	if(this->drawEnemyBullet)
	{
		this->gameWindow->draw(this->enemy.Bullet);
	}
		
	
}

void Window::RenderCover()
{
	for (auto& e : this->cover.destuctableCoverContainer)
	{
		this->gameWindow->draw(e);
	}
}


void Window::Render()
{
	/// <summary>
	/// Ties all of the smaller render functions togeather so they can all be called from one place 
	/// 
	///		--window is cleared
	///		--All render functions are called
	///		--Window it displayed 
	/// </summary>
	this->gameWindow->clear();

	this->RenderPlayer();
	this->RenederPlayerBullet();
	this->RenderEnemySensor();
	this->RenderEnemy();
	this->RenderEnemyBullet();
	this, RenderCover();

	this->gameWindow->display();
}

