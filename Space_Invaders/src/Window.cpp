#include "Window.h"

void Window::InitVariables()
{
	// settign up the variables for the game window
	this->gameWindow = nullptr;

	this->videoMode.height = 600;
	this->videoMode.width = 800;
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
		static_cast<float>( this->gameWindow->getSize().x /2),
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
	/// </summary>
	
	// variables for the padding 
	int columnPadding = 100;
	int rowPadding = 10;
	int numberOfEnemies = 0;
	
	// loop will run untill 25 enemies are on screen 
	while(numberOfEnemies < 55)
	{
		//if condition to check if the next enemy placed will not be to close to the edge of the screen.
		if (columnPadding + 100 < this->gameWindow->getSize().x)
		{
			//setting the enemies position and adding it to the Vector 
			this->enemy.sprite.setPosition(static_cast<float>(columnPadding), static_cast<float>(rowPadding));
			this->enemy.EnemyContainer.push_back(this->enemy.sprite);

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


Window::Window()
{
	this->InitVariables();
	this->InitWindow();
	this->InitPlayer();
	this->InitEnemies();
}
Window::~Window()
{
	delete this->gameWindow;
}



void Window::RenderPlayer()
{
	this->gameWindow->draw(this->player.sprite);
}
void Window::RenederBullet()
{
	for(auto &e : player.BulletsContainer)
	{
		this->gameWindow->draw(e);
	}
}

void Window::RenderEnemy()
{
	for(auto &e : enemy.EnemyContainer)
	{
		this->gameWindow->draw(e);
	}
}


void Window::Render()
{
	this->gameWindow->clear();

	this->RenderPlayer();
	this->RenederBullet();
	this->RenderEnemy();

	this->gameWindow->display();
}
