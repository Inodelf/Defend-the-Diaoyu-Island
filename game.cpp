/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>


//Screen attributes
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 50;

//The dimentsions of the dot
const int DOT_WIDTH = 130;
const int DOT_HEIGHT = 85;

//The surfaces
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *upMessage = NULL;
SDL_Surface *downMessage = NULL;
SDL_Surface *leftMessage = NULL;
SDL_Surface *rightMessage = NULL;
SDL_Surface *message = NULL;
SDL_Surface *boat = NULL;
SDL_Surface *dot = NULL;
SDL_Surface *image= NULL;

//The event structure
SDL_Event event;

//The portions of the sprite map to be blitted
SDL_Rect clip[ 8 ];


//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be used
Mix_Chunk *cannon1 = NULL;
Mix_Chunk *cannon2 = NULL;
Mix_Chunk *cannon3 = NULL;


//the dot that will move around on the screen
class Dot
{
private:
  //The X and Y offsets of the dot
  int x, y;

  //The velocity of the dot
  int xVel, yVel;

public:
  //Initializes the variables
  Dot();

  //Takes key presses and adjusts the dot's velocity
  void handle_input();

  //Move the dot
  void move();

  //Shows the dot on the screen
  void show();
};

//The timer
class Timer
{
private:
  //The clock time when the timer started
  int startTicks;

  //The ticks stored when the timer was paused
  int pausedTicks;

  //The timer status
  bool paused;
  bool started;

public:
  //Initializes variables
  Timer();

  //The various clock actions
  void start();
  void stop();
  void pause();
  void unpause();

  //Gets the timer's time
  int get_ticks();

  //Checks the status of the timer
  bool is_started();
  bool is_paused();
  
};

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

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
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

  //Load the music
  music = Mix_LoadMUS( "mix/sea.wav" );

  //If there was a problem in loading the music
  if( music == NULL )
  {
    return false;
  }

  //Load the sound effects
  cannon1 = Mix_LoadWAV( "gun/global.wav" );
  cannon2 = Mix_LoadWAV( "gun/msg.wav" );
  cannon3 = Mix_LoadWAV( "gun/system.wav" );

  //If there was a problem loadiing the sound effects
  if( ( cannon1 == NULL ) || ( cannon2 == NULL ) || ( cannon3 == NULL ) )
  {
    return false;
  }
  
  //If there was a problem in loading the background
    if( background == NULL )
   {
    return false;
  }
  dot = load_image( "libpic/boat.png" );
  
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
  SDL_FreeSurface( dot );
  Mix_FreeChunk( cannon1 );
  Mix_FreeChunk( cannon2 );
  Mix_FreeChunk( cannon3 );
  Mix_FreeMusic( music );
  
    //Close the font that was used
    TTF_CloseFont( font );

    //Quit SDL_mixer
    Mix_CloseAudio();
    
    //Quit SDL_ttf
    TTF_Quit();
    
    //Quit SDL
    SDL_Quit();
   
}

Dot::Dot()
{
  //Initialize the offsets
  x = 0;
  y = 0;

  //Initialize the velocity
  xVel = 0;
  yVel = 0;
}

void Dot::handle_input()
{
  //If a key was pressed
  if( event.type == SDL_KEYDOWN )
  {
    //Adjust the velocity
    switch( event.key.keysym.sym )
    {
    case SDLK_UP: yVel -= DOT_HEIGHT / 6;
      break;
    case SDLK_DOWN: yVel += DOT_HEIGHT / 6;
      break;
    case SDLK_LEFT: xVel -= DOT_WIDTH / 8;
      break;
    case SDLK_RIGHT: xVel += DOT_WIDTH / 8;
      break;
    }
  }
  //If a key was released
  else if( event.type == SDL_KEYUP )
  {
    //Adjust the velocity
    switch( event.key.keysym.sym )
    {
    case SDLK_UP: yVel += DOT_HEIGHT / 6;
      break;
    case SDLK_DOWN: yVel -= DOT_HEIGHT / 6;
      break;
    case SDLK_LEFT: xVel += DOT_WIDTH / 8;
      break;
    case SDLK_RIGHT: xVel -= DOT_WIDTH / 8;
      break;
    }
  }
}

void Dot::move()
{
  //Move the dot left or right
  x += xVel;

  //If the dot went too far to the left or right
  if(( x < 0 ) || ( x + DOT_WIDTH > SCREEN_WIDTH ))
  {
    //move back
    x -= xVel;
  }

  //Move the dot up or down
  y += yVel;

  //If the dot went too far up or down
  if(( y < 0 ) || ( y + DOT_HEIGHT > SCREEN_HEIGHT ))
  {
    //move back
    y -= yVel;
  }
}

void Dot::show()
{
  //Show the dot
  apply_surface( x, y, dot, screen, &clip[1] );
}

Timer::Timer()
{
  //Initialize the variables
  startTicks = 0;
  pausedTicks = 0;
  paused = false;
  started = false;
}

void Timer::start()
{
  //Start the timer
  started = true;

  //Unpause the timer
  paused = false;

  //Get the current clock time
  startTicks = SDL_GetTicks();
}

void Timer::stop()
{
  //Stop the timer
  started = false;

  //Unpause the timer
  paused = false;
}

void Timer::pause()
{
  //If the timer is running and isn't already paused
  if(( started == true ) && ( paused == false ))
  {
    //Pause the timer
    paused = true;

    //Calculate the paused ticks
    pausedTicks = SDL_GetTicks() - startTicks;
  }
}

void Timer::unpause()
{
  //If the timer is paused
  if( paused == true )
  {
    //Unpause the timer
    paused = false;

    //Reset the starting ticks
    startTicks = SDL_GetTicks() - pausedTicks;

    //Reset the paused ticks
    pausedTicks = 0;
  }
}

int Timer::get_ticks()
{
  //If the timer is running
  if( started == true )
  {
    //If the timer is paused
    if( paused == true )
    {
      //Return the number of ticks when the timer was paused
      return pausedTicks;
    }
    else
    {
      //Return the current time minus the start time
      return SDL_GetTicks() - startTicks;
    }
  }

  //If the timer isn't running
  return 0;
}

bool Timer::is_started()
{
  return started;
}

bool Timer::is_paused()
{
  return paused;
}


int main( int argc, char* args[] )
{
  //Quit flag
  bool quit = false;

  //The dot that will be used
  Dot myDot;

  //The frame rate regulator
  Timer fps;
  
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
//    message = TTF_RenderText_Solid( font, "good luck", textColor );
    
    //If there was an error in rendering the text
//  if( message == NULL )
//    {
//        return 1;
//      }

    //Apply the images to the screen
    apply_surface( 0, 0, background, screen, NULL );
    //    apply_surface( 0, 140, message, screen, NULL );

    
    //Update the screen
    if( SDL_Flip( screen ) == -1 )
      {
        return 1;
      }
    
    //While the user hasn't quit
    while( quit == false )
      {
        //Start the frame timer
        fps.start();
        
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
          {
            //Handle events for the dot
            myDot.handle_input();
            
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
              {
                //If a was pressed
                if( event.key.keysym.sym == SDLK_w )
                {
                  //Play the cannon1 effect
                  if( Mix_PlayChannel( -1, cannon1, 0 ) == -1 )
                  {
                    return 1;
                  }
                }
                //If s was pressed
                else if( event.key.keysym.sym == SDLK_s )
                {
                  //Play the cannon2 hit effect
                  if( Mix_PlayChannel( -1, cannon2, 0 ) == -1 )
                  {
                    return 1;
                  }
                }

                //If a was pressed
                else if( event.key.keysym.sym == SDLK_a )
                {
                  //Play the cannon3 hit effect
                  if( Mix_PlayChannel( -1, cannon3, 0 ) == -1 )
                  {
                    return 1;
                  }
                }

                //If d was pressed
                else if( event.key.keysym.sym == SDLK_d )
                {
                  //If ther is no music playing
                  if( Mix_PlayingMusic() == 0 )
                  {
                    //Play the music
                    if( Mix_PlayMusic( music, -1 ) == -1 )
                    {
                      return 1;
                    }
                  }

                  //If music is being played
                  else
                  {
                    //If the music is paused
                    if( Mix_PausedMusic() == 1 )
                    {
                      //Resume the music
                      Mix_ResumeMusic();
                    }
                    else
                    {
                      //Pause the music
                      Mix_PausedMusic();
                    }
                  }
                }

                //If f was pressed
                else if( event.key.keysym.sym == SDLK_f )
                {
                  //Stop the music
                  Mix_HaltMusic();
                }
              }
            
              
                  
                //Set the proper message surface
            /*        switch( event.key.keysym.sym )
                  {
                  case SDLK_w: message = upMessage; break;
                  case SDLK_s: message = downMessage; break;
                  case SDLK_a: message = leftMessage; break;
                  case SDLK_d: message = rightMessage; break;
                  }
            */                  }
                  //If a message needs to be displayed
        if( message != NULL )
         {
           // Apply the background to the screen
           
           // apply_surface( 400, 400, boat, screen, &clip[ 2 ] );
            //Apply the message centered on the screen
            apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) /2, message, screen );
          //Null the surface pointer
          message = NULL;
            }
        
        //Move the dot
        myDot.move();

        //Fill the screen white
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

        //Show the dot on the screen
        apply_surface( 0, 0, background, screen );
        apply_surface( 0, 0, image, screen, NULL );
        //If a message needs to be displayed
        if( message != NULL )
         {
           // Apply the background to the screen
           
           // apply_surface( 400, 400, boat, screen, &clip[ 2 ] );
            //Apply the message centered on the screen
            apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) /2, message, screen );
          //Null the surface pointer
          message = NULL;
            }
        
        myDot.show();
        

      //Update the screen
      if( SDL_Flip( screen ) == -1 )
        {
          return 1;
        }
      
    
      //Cap the frame rate
      if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
      {
        SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
      }

      //If the user has Xed out the window
      if( event.type == SDL_QUIT )
      {
        //Quit the program
        quit =true;
      }
      }

      
    
    //Free surfaces and font then quit SDL_ttf and SDL
    clean_up();
    
    return 0;

}




