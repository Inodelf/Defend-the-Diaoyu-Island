/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>


//Screen attributes
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *upMessage = NULL;
SDL_Surface *downMessage = NULL;
SDL_Surface *leftMessage = NULL;
SDL_Surface *rightMessage = NULL;
SDL_Surface *message = NULL;
SDL_Surface *boat = NULL;

//The event structure
SDL_Event event;

//The portions of the sprite map to be blitted
SDL_Rect clip[ 8 ];


//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };


SDL_Surface *load_image( std::string filename )
{
  //The image that's loaded
  SDL_Surface* loadedImage = NULL;
  
  //The optimezed surface that will be used
  SDL_Surface* optimizedImage = NULL;
  
  //Load the image
  loadedImage = IMG_Load( filename.c_str() );

  //If the image loaded
  if( loadedImage != NULL )
    {
      //Creete an optimized surface
      optimizedImage = SDL_DisplayFormat( loadedImage );
      //Free the old surface
      SDL_FreeSurface( loadedImage );
      
      //If the surface was optimized
      if( optimizedImage != NULL )
        {
          Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF );
          //Color key surface
          SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }
  
  //Return the optimized surface
  return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
  //Initialize all SDL subsystems
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
      return false;
    }

  //Set up the screen
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
  
  //If there was an error in setting up the screen
  if( screen == NULL )
    {
      return false;
    }



    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "TTF test", NULL );

    //If everything initialized fine
    return true;
}



bool load_files()
{
  
  //Load the background image
  background = load_image( "libpic/area.xcf" );

    


  //Open the font
  font = TTF_OpenFont( "fonts/simsun.ttf", 28 );

  //If there was a problem in loading the background
    if( background == NULL )
   {
    return false;
  }
  boat = load_image( "libpic/boat.png" );
  
  //If there was an error in loading the font
  if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{

    //Free the surfaces
  SDL_FreeSurface( background );

  SDL_FreeSurface( upMessage );
  SDL_FreeSurface( downMessage );
  SDL_FreeSurface( leftMessage );
  SDL_FreeSurface( rightMessage );
  SDL_FreeSurface( boat );

    //Close the font that was used
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();
    
    //Quit SDL
    SDL_Quit();
   
}

int main( int argc, char* args[] )
{
  //Quit flag
  bool quit = false;
  
  //Initialize
  if( init() == false )
    {
      return 1;
    }

    //Load the files
    if( load_files() == false )
      {
        return 1;
      }

  //Generate the message surfaces
  upMessage = TTF_RenderText_Solid( font, "Up was pressed.", textColor );
  downMessage = TTF_RenderText_Solid( font, "Down was pressed.", textColor );
  leftMessage = TTF_RenderText_Solid( font, "Left was pressed.", textColor );
  rightMessage = TTF_RenderText_Solid( font, "Right was pressed", textColor );    
    
clip[ 0 ].x = 0;
clip[ 0 ].y = 0;
clip[ 0 ].w = 250;
clip[ 0 ].h = 100;

clip[ 1 ].x = 475;
clip[ 1 ].y = 0;
clip[ 1 ].w = 175;
clip[ 1 ].h = 125;

clip[ 2 ].x = 0;
clip[ 2 ].y = 150;
clip[ 2 ].w = 325;
clip[ 2 ].h = 125;

clip[ 3 ].x = 525;
clip[ 3 ].y = 150;
clip[ 3 ].w = 125;
clip[ 3 ].h = 200;

clip[ 4 ].x = 0;
clip[ 4 ].y = 300;
clip[ 4 ].w = 200;
clip[ 4 ].h = 75;

clip[ 5 ].x = 425;
clip[ 5 ].y = 350;
clip[ 5 ].w = 275;
clip[ 5 ].h = 125;

clip[ 6 ].x = 0;
clip[ 6 ].y = 375;
clip[ 6 ].w = 200;
clip[ 6 ].h = 300;

clip[ 7 ].x = 400;
clip[ 7 ].y = 475;
clip[ 7 ].w = 300;
clip[ 7 ].h = 200;

    

    //Render the text
    message = TTF_RenderText_Solid( font, "good luck", textColor );
    
    //If there was an error in rendering the text
    if( message == NULL )
      {
        return 1;
      }

    //Apply the images to the screen
    apply_surface( 0, 0, background, screen, NULL );
    apply_surface( 0, 140, message, screen, NULL );

    
    //Update the screen
    if( SDL_Flip( screen ) == -1 )
      {
        return 1;
      }
    
    //While the user hasn't quit
    while( quit == false )
      {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
          {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
              {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                  {
                  case SDLK_w: message = upMessage; break;
                  case SDLK_s: message = downMessage; break;
                  case SDLK_a: message = leftMessage; break;
                  case SDLK_d: message = rightMessage; break;
                  }
              }
            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
              {
                //Quit the program
                quit =true;
              }
          }
        //If a message needs to be displayed
        if( message != NULL )
          {
            //Apply the background to the screen
            apply_surface( 0, 0, background, screen );
            apply_surface( 400, 400, boat, screen, &clip[ 2 ] );
            //Apply the message centered on the screen
          apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) /2, message, screen );
          //Null the surface pointer
          message = NULL;
        }

      //Update the screen
      if( SDL_Flip( screen ) == -1 )
        {
          return 1;
        }
      }
    
    //Free surfaces and font then quit SDL_ttf and SDL
    clean_up();
    
    return 0;
    }

