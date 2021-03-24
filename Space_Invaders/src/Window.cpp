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
	this->drawEnemySensor = false;
	this->drawMainGame = false;
	this->drawEndScreen = false;
	this->drawMainMenu = true;

	this->lives = 3;
	this->score = 0;
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
	this->player.playerSprite.setPosition(
		static_cast<float>(this->gameWindow->getSize().x / 2),
		static_cast<float>(this->gameWindow->getSize().y - this->player.playerSprite.getGlobalBounds().height)
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

	// variables to ser were the enemies will spawn n screen 
	int columnPadding = 100;
	int rowPadding = 50;

	//Setting the inital texture for the enemy 
	this->enemy.enemySprite.setTexture(this->enemy.enemyShipTextureA1);

	// loop will run untill 48 enemies are on screen 
	int numberOfEnemies = 0;
	while (numberOfEnemies < 48)
	{
		//if condition to check if the next enemy placed will not be to close to the edge of the screen.
		if (columnPadding + 100 < this->gameWindow->getSize().x)
		{
			//setting the enemies position and adding it to the Vector 
			this->enemy.enemySprite.setPosition(static_cast<float>(columnPadding), static_cast<float>(rowPadding));
			this->enemy.EnemySpriteContainer.push_back(this->enemy.enemySprite);

			//Updateing the column padding so the next enemy is 10 pixels away from the last one 
			columnPadding += this->enemy.enemySprite.getGlobalBounds().width + 10;
		}
		else
		{
			columnPadding = 100;
			rowPadding += this->enemy.enemySprite.getGlobalBounds().height + 10;
		}

		//Chaning the texture of the enemies
		if(numberOfEnemies == 11)
		{
			this->enemy.enemySprite.setTexture(this->enemy.enemyShipTextureC1);
		}
		else if(numberOfEnemies == 22)
		{
			this->enemy.enemySprite.setTexture(this->enemy.enemyShipTextureB1);
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
		static_cast<float>(this->gameWindow->getSize().y - this->player.playerSprite.getGlobalBounds().height)
	);

	this->enemySensorLimiter.setPosition(static_cast<float>(0), static_cast<float>(44));
}
void Window::InitCover()
{
	/// <summary>
	/// Adds 3 layers of cover next to the bottom of the screen for the player to use 
	/// </summary>

	// variables for the padding 
	float columnOffset = this->cover.coverSprite.getGlobalBounds().width + 65.f;
	float rowOffset = this->cover.coverSprite.getGlobalBounds().height + 475.f;
	int numberOfCover = 0;

	// loop will run untill all cover is on screen 
	while (numberOfCover < 138)
	{
		
			//setting the enemies position and adding it to the Vector 
			this->cover.coverSprite.setPosition(static_cast<float>(columnOffset), static_cast<float>(rowOffset));
			this->cover.destuctableCoverContainer[numberOfCover] = this->cover.coverSprite;

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
				rowOffset += this->cover.coverSprite.getGlobalBounds().height;
				columnOffset = this->cover.coverSprite.getGlobalBounds().width + 55.f;
			}
			columnOffset += this->cover.coverSprite.getGlobalBounds().width;

		numberOfCover++;
	}

}
void Window::InitSound()
{
	/// <summary>
	/// loads all the sound files to buffer and gives the correct Buffer to the right Sound object 
	/// </summary>
	if(this->shipFireBuffer.loadFromFile("..\\assets\\sounds\\ShipBullet.wav"))
	{
		std::cout << "Ship Fire Sound Loaded\n";
	}
	if (this->shipHitBuffer.loadFromFile("..\\assets\\sounds\\ShipHit.wav"))
	{
		std::cout << "Ship Hit Sound Loaded\n";
	}
	if (this->enemyFireBuffer.loadFromFile("..\\assets\\sounds\\InvaderBullet.wav"))
	{
		std::cout << "Enemy Fire Sound Loaded\n";
	}
	if (this->enemyHitBuffer.loadFromFile("..\\assets\\sounds\\InvaderHit.wav"))
	{
		std::cout << "Enemy Hit Sound Loaded\n";
	}

	this->shipFireSound.setBuffer(this->shipFireBuffer);
	this->shipHitSound.setBuffer(this->shipHitBuffer);
	this->enemyFireSound.setBuffer(this->enemyFireBuffer);
	this->enemyHitSound.setBuffer(this->enemyHitBuffer);
}
void Window::InitObjectsForText()
{
	/// <summary>
	/// Sets the font of the game and gives the Text object the fonat as well as the text that will be displayed 
	/// Also sets the loction/size/color of the Rectangle shape that is used for the button 
	/// </summary>
	if(this->gameFont.loadFromFile("..\\assets\\fonts\\unifont.ttf"))
	{
		std::cout << "Game Font Loaded\n";
	}

	this->menuButtonText.setFont(this->gameFont);
	this->livesText.setFont(this->gameFont);
	this->scoreText.setFont(this->gameFont);
	this->winLoseText.setFont(this->gameFont);
	this->menuHelpText.setFont(this->gameFont);

	this->livesText.setString("Lives: " + std::to_string(this->lives));
	this->scoreText.setString("Score: " + std::to_string(this->score));
	this->menuButtonText.setString("PLAY");
	this->menuHelpText.setString("Click on the Button to start the game\nPress A/D or Left/Right to move\nPress SPace to Shoot");

	this->livesText.setPosition(0, 0);
	this->scoreText.setPosition(this->gameWindow->getSize().x - (this->scoreText.getGlobalBounds().width + 50), 0);
	this->menuButtonText.setPosition(
		(this->gameWindow->getSize().x / 2) - (this->Button.getSize().x / 2) - (this->menuButtonText.getGlobalBounds().width/2)
	    , 75);
	this->menuHelpText.setPosition(130,225);

	this->Button.setSize(sf::Vector2f(200.f,100.f));
	this->Button.setPosition((this->gameWindow->getSize().x / 2) - (this->Button.getSize().x / 2), 50.f);
	this->Button.setFillColor(sf::Color::Black);
	this->Button.setOutlineColor(sf::Color::White);
	this->Button.setOutlineThickness(2);
}
void Window::InitMusic()
{
	/// <summary>
	/// Loads the music from the file and gives it to the correct Music object 
	/// </summary>
	if(this->gameMusic.openFromFile("..\\assets\\sounds\\06_Mars.wav"))
	{
		std::cout << "Game Music Loaded\n";
	}
	if (this->mainMenuMusic.openFromFile("..\\assets\\sounds\\01_Title Screen.wav"))
	{
		std::cout << "Main Menu Music Loaded\n";
	}
	if (this->endScreenMusic.openFromFile("..\\assets\\sounds\\12_Invader Homeworld.wav"))
	{
		std::cout << "End Screen Music Loaded\n";
	}

	this->gameMusic.setVolume(50);
	this->mainMenuMusic.setVolume(50);
	this->endScreenMusic.setVolume(50);
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
	this->InitSound();
	this->InitObjectsForText();
	this->InitMusic();
}
Window::~Window()
{
	delete this->gameWindow;
}


void Window::RenderMenu()
{
	/// <summary>
	/// Function renders the corect tect for the Main Menu and Endsceen depending on what part of the game 
	/// should be getting rendered 
	/// </summary>
	if(this->drawMainMenu)
	{
		this->menuButtonText.setString("PLAY");
		this->menuHelpText.setString("Click on the Button to start the game\nPress A/D or Left/Right to move\nPress SPace to Shoot");
	}
	else if(this->drawEndScreen)
	{
		this->menuButtonText.setString("BACK");
		if (this->lives > 0)
		{
			this->menuHelpText.setString("Congatulations You WON !!!\nScore: " + std::to_string(this->score) + "\nLives: "
				+ std::to_string(this->lives));
		}
		else
		{
			this->menuHelpText.setString("You Lost Better Luck Next Time\nScore: " + std::to_string(this->score) + "\nLives: "
				+ std::to_string(this->lives));
		}
		
	}

	this->gameWindow->draw(this->Button);
	this->gameWindow->draw(this->menuButtonText);
	this->gameWindow->draw(this->menuHelpText);
}

// Indevidual Object Rendering functions 
void Window::RenderPlayer()
{
	this->gameWindow->draw(this->player.playerSprite);
}
void Window::RenederPlayerBullet()
{
	if (this->drawPlayerBullet) 
	{
		this->gameWindow->draw(this->player.playerBulletSprite);
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
	if(this->drawEnemySensor)
	{
		this->gameWindow->draw(this->enemySensor);
		this->gameWindow->draw(this->enemySensorLimiter);
	}
	
}
void Window::RenderEnemyBullet()
{
	if(this->drawEnemyBullet)
	{
		this->gameWindow->draw(this->enemy.enemyBulletSprite);
	}
		
	
}

void Window::RenderGameText()
{
	this->gameWindow->draw(this->scoreText);
	this->gameWindow->draw(this->livesText);
}

void Window::RenderCover()
{
	for (auto& e : this->cover.destuctableCoverContainer)
	{
		this->gameWindow->draw(e);
	}
}

void Window::RedrawGame()
{
	this->enemy.EnemySpriteContainer.clear();
	this->InitEnemies();
	this->InitCover();
	this->InitPlayer();
}

void Window::PlayMusic()
{
	if(this->drawMainMenu)
	{
		this->endScreenMusic.stop();
		if (this->mainMenuMusic.getStatus() != sf::Music::Status::Playing)
		{
			this->mainMenuMusic.play();
		}
	}
	else if (this->drawMainGame) 
	{
		this->mainMenuMusic.stop();
		if (this->gameMusic.getStatus() != sf::Music::Status::Playing)
		{
			this->gameMusic.play();
		}
	}
	else
	{
		this->gameMusic.stop();
		if (this->endScreenMusic.getStatus() != sf::Music::Status::Playing)
		{
			this->endScreenMusic.play();
		}
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

	this->PlayMusic();
	

	if(this->drawMainMenu)
	{
		this->RenderMenu();
	}
	else if(this->drawMainGame)
	{
		this->RenderPlayer();
		this->RenederPlayerBullet();
		this->RenderEnemy();
		this->RenderEnemySensor();
		this->RenderEnemyBullet();
		this, RenderCover();
		this->RenderGameText();
	}
	else
	{
		this->RenderMenu();
	}
	

	

	this->gameWindow->display();
}

