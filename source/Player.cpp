#include "Player.h"
#include "Common.h"

CPlayer::CPlayer()
{
	Init();
}



CPlayer::~CPlayer()
{
	if (spr != NULL)
	{
		delete spr;
	}
	
	if (tex != NULL)
	{
		SDL_DestroyTexture(tex);
		tex = NULL;
	}

	
}


void CPlayer::Init()
{
	// Init Sprite
	tex = loadTexture(gRenderer, "images/ship.png", width, height);
	spr = new CSprite(tex, width, height);

	x = 0;
	y = 0;
}

void CPlayer::Draw()
{
	if (spr != NULL)
	{
		spr->Render(gRenderer, x, y, 1.0, 1.0);
	}
}


void CPlayer::Process()
{

}