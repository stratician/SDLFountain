#include "Emitter.h"

void CEmitter::Render(SDL_Renderer* renderer, int x, int y, float sx, float sy, double angle, SDL_Point* center, SDL_RendererFlip flip) const
{
	CSprite::Render(renderer, x, y, sx, sy, angle, center, flip);
	
	for (int i = 0; i < 8; ++i) {
		CSprite::Render(renderer, x + cos(i*45) * 100.0f, y + sin(i*45) * 100.0f, sx * 0.5, sy * 0.5, angle, center, flip);
	}

}