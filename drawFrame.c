#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "makeTexture.h"
#include <time.h>


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCALE 2
void updateScreen(int sizeX, int sizeY, int (*Array)[sizeY], SDL_Renderer *renderer)
{

  SDL_Rect rect;
  int blockScale = SCALE-1;
  rect.x = 0;
  rect.y = 0;
  rect.w = blockScale;
  rect.h = blockScale;

  for (int x = 0; x < sizeX; x++)
  {
    for (int y = 0; y < sizeY; y++)
    {
      if (Array[x][y] == 1)
      {
        rect.x = x*SCALE;
        rect.y = y*SCALE;
        SDL_RenderFillRect(renderer, &rect);
      }
    }
  }

  SDL_RenderPresent(renderer);
  
}

<<<<<<< HEAD
//int WinMain(int argc, char *args[])
=======
// int WinMain(int argc, char *args[])
>>>>>>> 5c08f4e (fixed drawing)
int main(int argc, char *args[])
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


  int sizeX = 1920/SCALE;
  int sizeY = 1080/SCALE;
  int a[sizeX][sizeY];
  int(*Array)[sizeY] = a;

  int b[sizeX][sizeY];
  int(*tempArray)[sizeY] = b;

  initializeEmptyArray(sizeX, sizeY, Array);
  populateArray(sizeX, sizeY, Array);
  updateScreen(sizeX, sizeY, Array, renderer);

  int t = 0;
  int start = clock();
  int exit = false;
  int pause = false;
  int clicking = false;
  int mouseX = 0;
  int mouseY = 0;

  SDL_Rect rect;
  int blockScale = SCALE;
  rect.x = 0;
  rect.y = 0;
  rect.w = blockScale;
  rect.h = blockScale;
  int mouseButton=0;
  int step = 0;
  while (t<500 && !exit)
  {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    if (!pause || step){
      generationStep(sizeX, sizeY, Array, tempArray);
      t++;
    }
    step = 0;
    rect.x=mouseX/SCALE *SCALE;
    rect.y=mouseY/SCALE *SCALE;
    mouseButton = SDL_GetMouseState(&mouseX, &mouseY);
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
    if (clicking){
      if (mouseButton == 1) alterCell(sizeX, sizeY, Array, mouseX/SCALE, mouseY/SCALE, 1);
      else alterCell(sizeX, sizeY, Array, mouseX/SCALE, mouseY/SCALE, 0);
    }
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    updateScreen(sizeX, sizeY, Array, renderer);
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) exit = true;
        if (e.type == SDL_KEYDOWN) { if (e.key.keysym.sym ==SDLK_SPACE) pause = !pause;}
        if (e.type == SDL_KEYDOWN) { if (e.key.keysym.sym ==SDLK_n) step= 1;}
        if (e.type == SDL_KEYDOWN) { if (e.key.keysym.sym ==SDLK_c) initializeEmptyArray(sizeX, sizeY, Array);}
        if (e.type == SDL_KEYDOWN) { if (e.key.keysym.sym ==SDLK_r) populateArray(sizeX, sizeY, Array);}
        if (e.type == SDL_MOUSEBUTTONDOWN) clicking = true;
        if (e.type == SDL_MOUSEBUTTONUP) clicking = false;
    }
  }
  int end = clock();
  end -= start;
<<<<<<< HEAD
  printf("%d%s", end, "\n");
=======
>>>>>>> 5c08f4e (fixed drawing)

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;

}
