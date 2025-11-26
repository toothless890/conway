#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "makeTexture.h"
#include <time.h>
#if defined(_WIN32) || defined(_WIN64)
#define mainFunction WinMain
#elif defined(__linux__) || defined(__unix__)
#define mainFunction main
#endif

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCALE 2
#define DEFAULT_ZOOM_SCALE 16
#define ZOOM_WIDTH 1920
#define ZOOM_HEIGHT 1080
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))


void updateScreen(int sizeX, int sizeY, int (*Array)[sizeY], SDL_Renderer *renderer)
{

  SDL_Rect rect;
  int blockScale = SCALE - 1;
  rect.x = 0;
  rect.y = 0;
  rect.w = blockScale;
  rect.h = blockScale;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (int x = 0; x < sizeX; x++)
  {
    for (int y = 0; y < sizeY; y++)
    {
      if (Array[x][y] == 1)
      {
        rect.x = x * SCALE;
        rect.y = y * SCALE;
        SDL_RenderFillRect(renderer, &rect);
      }  
    }
  }
}

void drawZoom(int zoomPosX, int zoomPosY, int sizeX, int sizeY, int mouseX, int mouseY, int zoomScale, int (*Array) [sizeY], SDL_Renderer *renderer){

  SDL_Rect rect;
  int blockScale = zoomScale - 1;

  printf(" %d, %d\n",zoomPosX, zoomPosY);
  rect.x = 0;
  rect.y = 0;
  rect.w = blockScale;
  rect.h = blockScale;

  int zoomSizeX = ZOOM_WIDTH / zoomScale;
  int zoomSizeY = ZOOM_HEIGHT / zoomScale;
  zoomPosX = zoomPosX/2 + zoomSizeX/4;
  zoomPosY = zoomPosY/2 + zoomSizeY/4;
  int xstart = max(zoomPosX-zoomSizeX/2, 0);
  int xend = min(xstart+zoomSizeX/2, sizeX-zoomSizeX/2);
  int ystart = max(zoomPosY-zoomSizeY/2, 0);
  int yend = min(ystart+zoomSizeY/2, sizeY-zoomSizeY/2);
  // int xstart = 0; int xend = 16;
  // int ystart = 0; int yend = 16;
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for ( int x = xstart; x< xend; x++){
    for (int y = ystart; y< yend; y++){
      // printf(" %d, %d\n",x, y);
      if (Array[x][y] == 1)
      {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      }  
      else{
        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 25);
      }
        rect.x = (x-xstart) * zoomScale;
        rect.y = (y-ystart) * zoomScale;
        SDL_RenderFillRect(renderer, &rect);
      
    }
  }

}


// int WinMain(int argc, char *args[])
int mainFunction(int argc, char *args[])
{
  SDL_Window *window = NULL;
  // SDL_Surface *screenSurface = NULL;
  SDL_Renderer *renderer = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  window = SDL_CreateWindow(
      "sdl2",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }

  // screenSurface = SDL_GetWindowSurface(window);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  int sizeX = SCREEN_WIDTH / SCALE;
  int sizeY = SCREEN_HEIGHT / SCALE;

 

  int a[sizeX][sizeY];
  int (*Array)[sizeY] = a;

  int b[sizeX][sizeY];
  int (*tempArray)[sizeY] = b;

  initializeEmptyArray(sizeX, sizeY, Array);
  populateArray(sizeX, sizeY, Array);
  updateScreen(sizeX, sizeY, Array, renderer);



  int t = 0;
  int start = clock();
  int exit = false;
  int pause = false;
  int clicking = false;
  int zooming = false;
  int mouseX = 0;
  int mouseY = 0;
  int zoomScale = DEFAULT_ZOOM_SCALE;
  int zoomPosX = 0;
  int zoomPosY = 0;

  SDL_Rect rect;
  int blockScale = SCALE;
  rect.x = 0;
  rect.y = 0;
  rect.w = blockScale;
  rect.h = blockScale;
  int mouseButton = 0;
  int step = 0;
  while (!exit)
  {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    if (!pause || step)
    {
      generationStep(sizeX, sizeY, Array, tempArray);
      t++;
    }
    step = 0;
    rect.x = mouseX / SCALE * SCALE;
    rect.y = mouseY / SCALE * SCALE;
    mouseButton = SDL_GetMouseState(&mouseX, &mouseY);
    if (clicking)
    {
      if (mouseButton == 1)
        alterCell(sizeX, sizeY, Array, mouseX / SCALE, mouseY / SCALE, 1);
      else
        alterCell(sizeX, sizeY, Array, mouseX / SCALE, mouseY / SCALE, 0);
      }   
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      updateScreen(sizeX, sizeY, Array, renderer);
      if(zooming){
    	  drawZoom(zoomPosX, zoomPosY, sizeX, sizeY, mouseX, mouseY, zoomScale, Array, renderer);
      }

      SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
      SDL_RenderFillRect(renderer, &rect);
      SDL_RenderPresent(renderer);

      SDL_Event e;
      while (SDL_PollEvent(&e))
      {
      if (e.type == SDL_QUIT)
        exit = true;
      if (e.type == SDL_KEYDOWN)
      {
        if (e.key.keysym.sym == SDLK_SPACE)
          pause = !pause;

        if (e.key.keysym.sym == SDLK_n)
          step = 1;

        if (e.key.keysym.sym == SDLK_z){
          zooming = !zooming;
          zoomPosX = mouseX;
          zoomPosY = mouseY;
        }
        if (e.key.keysym.sym == SDLK_c)
          initializeEmptyArray(sizeX, sizeY, Array);
        if (e.key.keysym.sym == SDLK_i)
          zoomScale = min(zoomScale+2, 3210000);
        if (e.key.keysym.sym == SDLK_o)
          zoomScale = max(zoomScale -2, 2);
        if (e.key.keysym.sym == SDLK_r)
          populateArray(sizeX, sizeY, Array);
      }
      if (e.type == SDL_MOUSEBUTTONDOWN)
        clicking = true;
      if (e.type == SDL_MOUSEBUTTONUP)
        clicking = false;
    }
  }
  int end = clock();
  end -= start;
  printf("%d%s", end, "\n");

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
