#pragma once
#include "sprite.h"

class CEmitter :
    public CSprite
{
public:

    CEmitter(SDL_Texture* texture, int width, int height) : CSprite(texture, width, height) {}
    ~CEmitter() {}

    void Render(SDL_Renderer* renderer, int x, int y, float sx, float sy, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

};

