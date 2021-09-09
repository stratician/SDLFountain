#include "Sprite.h"



CSprite::CSprite(SDL_Texture* texture, int width, int height)
{
	this->texture = texture;
	this->width = width;
	this->height = height;
}

CSprite::~CSprite()
{
	// Note, we don't delete this, as it's a reference, so just set to NULL
	texture = NULL;
}

void CSprite::Render(SDL_Renderer* renderer, int x, int y, float sx, float sy, double angle, SDL_Point* center, SDL_RendererFlip flip) const
{
	//Render texture to screen
	if (texture)
	{
		//Set rendering space and render to screen
		SDL_Rect dRect = { x, y, width * sx, height * sy};

		//Set clip rendering dimensions (scale)
		SDL_Rect sRect = { 0, 0, width, height};

		//Render to screen
		SDL_RenderCopyEx(renderer, texture, &sRect, &dRect, angle, center, flip);
	}
}