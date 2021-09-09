#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class SDL_Texture;
class SDL_Renderer;

class CSprite
{

private:


protected:
	//Current displayed texture
	SDL_Texture* texture = NULL;
	float width;
	float height;


public:

	CSprite(SDL_Texture* texture, int width, int height);
	virtual ~CSprite();

	void Render(SDL_Renderer* renderer, int x, int y, float sx, float sy, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

};

