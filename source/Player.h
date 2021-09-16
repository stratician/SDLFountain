#pragma once

#include "Sprite.h"

class CPlayer
{

private:

	SDL_Texture* tex;
	CSprite* spr;
	
	double x, y;
	int width;
	int height;

public:
	CPlayer();
	virtual ~CPlayer();

	void Init();
	void Draw();
	void Process();


};

