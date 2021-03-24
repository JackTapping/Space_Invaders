#include "Cover.h"
#include "..\include\Cover.h"

void Cover::InitCover()
{
	if(this->coverTexture.loadFromFile("..\\assets\\images\\OKBlock.png"))
	{
		std::cout << "Cover Texture Loaded\n";
	}
	this->coverSprite.setTexture(this->coverTexture);
	this->coverSprite.setScale(.315f, .315f);
	//the number .315 is used because when i first made the game i used SF::RecShape and not SF::Sprite 
	//Beacuse the new Srptie has a different size to the spahe i origionlay used  setting the Scle to .315 was the
	//Fastses way to get the cover back in its correct position. 
}

Cover::Cover()
{
	InitCover();
}

Cover::~Cover()
{
}
