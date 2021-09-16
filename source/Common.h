#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>


extern SDL_Renderer* gRenderer;


SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path, int& width, int& height);