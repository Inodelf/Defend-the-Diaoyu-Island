/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"

#include "SDL/SDL_ttf.h"
#include <string>


//The surfaces

SDL_Surface *message = NULL;



//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 255, 255, 255 };


    //Return the optimized surface
    return optimizedImage;
}

void apply_font( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init_fonts()
{

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }


    //If everything initialized fine
    return true;
}

bool load_fonts()
{

    //Open the font
    font = TTF_OpenFont( "fonts/FreeSans.ttf", 28 );

    //If there was a problem in loading the background

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_fonts()
{

    //Free the surfaces
    SDL_FreeSurface( message );

    //Close the font that was used
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

