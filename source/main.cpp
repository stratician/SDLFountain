/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "Sprite.h"
#include "Emitter.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

int gTextureWidth;
int gTextureHeight;
CSprite* spr1;

const float GRAVITY = 0.4f;


class CParticle
{
private:
	float x, y;
	float vx, vy;
	CSprite* spr;
	
public:

	bool bDestroy;
	CParticle(int x, int y, float vx, float vy) 
	{
		if(rand()%10 < 5)
			spr = new CSprite(gTexture, gTextureWidth, gTextureHeight);
		else
			spr = new CEmitter(gTexture, gTextureWidth, gTextureHeight);
		bDestroy = false;

		this->x = x;
		this->y = y;
		this->vx = vx;
		this->vy = vy;
	}

	~CParticle()
	{
		if (spr)
		{
			delete spr;
		}
	}

	void Process()
	{
		x += vx;
		y += vy;
		vy += GRAVITY;
		vy *= 0.97f;

		if (y > SCREEN_HEIGHT)
		{
			bDestroy = true;
		}
	}

	void Render()
	{
		if(spr)
		{
			spr->Render(gRenderer, x, y, 0.5, 0.5);
		}
	}
};

std::vector<CParticle* > particles;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture = loadTexture( "images/mario.png" );
	if( gTexture == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Get image dimensions
		gTextureWidth = loadedSurface->w;
		gTextureHeight = loadedSurface->h;


		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

int main( int argc, char* args[] )
{

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	

			
			spr1 = new CSprite(gTexture, gTextureWidth, gTextureHeight);

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym) 
						{
						case SDLK_UP:
							// Create a sprite
							break;
						}
					}
				}


				//Clear screen
				SDL_RenderClear( gRenderer );

				// Render texture to screen
				// SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

				if (rand() % 6 == 0)
				{
					particles.push_back(new CParticle(SCREEN_WIDTH >> 1, SCREEN_HEIGHT - 100, (-500.0f + rand() % 1000) * 0.03f, -20 - (rand() % 200) * 0.1));
				}

				for (int i=particles.size()-1;i>=0;--i)
				{ 
					particles[i]->Process();
					if (!particles[i]->bDestroy)
					{
						particles[i]->Render();
					}
					else
					{
						particles.erase(particles.begin() + i);
					}
				}

				


				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}