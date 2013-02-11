/* 
function name: loadImg
parameter:cons char* FileName
parameter Note:FileName is a pointer use to save the name of image file
return:SDL_Surface* this is a pointer of SDL_Surface
function:load image to memory
*/
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
SDL_Surface* loadImg(const char* FileName)
{
  //Temporary storage for the image that's loaded
  SDL_Surface* loadedImage = NULL;
  //The optimized image that will be used
  SDL_Surface* optimizedImage = NULL;
    loadedImage = SDL_LoadBMP (FileName);
  if (loadedImage != NULL)
    {
      optimizedImage = SDL_DisplayFormat(loadedImage);

  //Free the old image
  SDL_FreeSurface(loadedImage);
    }
  return optimizedImage;
}
/* 
function name: showImg
parameter:SDL_Surface *source, int x, int y, int width, int height,
SDL_Surface *destination
parameter note:source is the handler of image:
x is the left of image
y is the top of image
width is the width of image
height is the height of image
destination is screen handler

return:void
function:show image to display memory
*/
void showImg(SDL_Surface *source,int x, int y,int width,int height,
	     SDL_Surface *destination)
{
  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.w = (width == 0) ? source->w:width;
  position.h = (height == 0) ? source->h:height;
  SDL_BlitSurface(source,NULL,destination,&position);
}
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
//the surfaces that will be used
SDL_Surface *message = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

int main(int argc, char *args[] )
{
  //Initialize all SDL subsystems
  if (SDL_Init(SDL_INIT_EVERYTHING) ==-1)
    {
      printf("初始化失败！\n");
      return 1;
    }
  //Set up the screen
  screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
  if (screen == NULL)
    {
      printf("there is an error in setting up the screen\n");
      return 1;
	     }
  message = loadImg("libpic/hello.bmp");
  background = loadImg("libpic/background.bmp");

  //Apply the background to screen
  showImg(background,0,0,0,0,screen);
  showImg(background,640,0,0,0,screen);
  showImg(background,0,480,0,0,screen);
  showImg(background,640,480,0,0,screen);
  showImg(message,18,14,999,999,screen);
  if (SDL_Flip(screen) == -1)
    {
      printf("Please check the vedio card");
      return 1;
    }
  //Wait 2 seconds
  SDL_Delay(8000);
  //Free the surface
  SDL_FreeSurface(message);
  SDL_FreeSurface(background);
  SDL_Quit ();
  return 0;
}
