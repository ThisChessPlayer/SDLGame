 /*****************************************************************************

                                                         Author: Jason Ma
                                                         Date:   Sep 25 2016
                                      SDLGame

 File Name:     Display.cpp
 Description:   SDL interface, handles events and displays everything
                appropriately.
 *****************************************************************************/

//#include "SDL2/include/SDL2/SDL.h"
//#include "SDL_image/include/SDL2/SDL_image.h"
//#include "SDL2_TTF-2.0.14/i686-w64-mingw32/include/SDL2/SDL_ttf.h"
//#include "SDL.h"
//#include "SDL_image.h"
//#include "SDL_ttf.h"

#include "Display.h"
//#include "Camera.h"
//#include <png.h>
//#include <zlib.h>
#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window * window = NULL; //window to render to
SDL_Surface * screenSurface = NULL; //surface contained by window
SDL_Renderer * renderer = NULL;
SDL_Texture * mouseTexture;
SDL_Texture * gridTexture;
SDL_Texture * sideticksTexture;
SDL_Texture * robotoTestString;

SDL_Event event;
SDL_Rect mouseRect;
SDL_Rect tile;
SDL_Rect downRect;
SDL_Rect upRect;

TTF_Font * roboto;

int robotoTestStringWidth;
int robotoTestStringHeight;

bool cameraMove[4];

Camera camera = Camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
bool mouseDown = false;

int Display::init() {
  //attempt to init SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL init failed! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }
 
  //attempt to create window  
  window = SDL_CreateWindow("Cubeception 3 Status Monitor", 
      SDL_WINDOWPOS_UNDEFINED, 
      SDL_WINDOWPOS_UNDEFINED, 
      SCREEN_WIDTH, 
      SCREEN_HEIGHT, 
      SDL_WINDOW_SHOWN);

  if(window == NULL) {
    printf("Window creation failed! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if(renderer == NULL) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return -1;
  }

  int imgFlags = IMG_INIT_PNG;

  if(!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
  }

  screenSurface = SDL_GetWindowSurface(window);

  if(TTF_Init() == -1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }

  SDL_FillRect(screenSurface, NULL, 
      SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

  SDL_UpdateWindowSurface(window);

  SDL_ShowCursor(SDL_DISABLE);

  return 0;
}

int Display::load() {

  SDL_Color white = {255, 255, 255};

  mouseTexture = loadTexture("crosshair16.png");
  gridTexture = loadTexture("gridtest.png");
  sideticksTexture = loadTexture("sideticks.png");
  roboto = loadTTF("roboto/Roboto-Light.ttf", 12);
  robotoTestString = loadTTFString(roboto, white, "hi");
  //TODO actually check whether texture was loaded, unloaded -> NULL
  return 0;
}

TTF_Font * Display::loadTTF(const char * path, int size) {
  TTF_Font * font = TTF_OpenFont(path, size);

  if(font == NULL) {
    printf("Unable to create font from %s!\n", path);
    return font;
  }

  return font;
}

SDL_Texture * Display::loadTTFString(TTF_Font * font, SDL_Color color, const char * message) {
  SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, message, color); 

  SDL_Texture * result = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

  if(result == NULL) {
    printf("Unable to create texture from %s! SDL Error: %s\n", message, SDL_GetError());
    return result;
  }

  //robotoTestStringWidth = surfaceMessage->w;
  //robotoTestStringHeight = surfaceMessage->h;

  SDL_FreeSurface(surfaceMessage);
  return result;
}

SDL_Texture * Display::loadTexture(std::string path) {
  SDL_Texture * result = NULL;

  SDL_Surface * loadedSurface = IMG_Load(path.c_str());
  if(loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    return result;
  }

  result = SDL_CreateTextureFromSurface(renderer, loadedSurface);

  if(result == NULL) {
    printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    return result;
  }

  SDL_FreeSurface(loadedSurface);

  return result;
}

int Display::handleEvents() {
  int x, y;

  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
        return -1;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
          case SDLK_q:
            return -1;
          case SDLK_w:
            cameraMove[2] = true;
            break;
          case SDLK_s:
            cameraMove[3] = true;
            break;
          case SDLK_a:
            cameraMove[0] = true;
            break;
          case SDLK_d:
            cameraMove[1] = true;
            break;
        }
        break;
      case SDL_KEYUP:
        switch(event.key.keysym.sym) {
          case SDLK_w:
            cameraMove[2] = false;
            break;
          case SDLK_s:
            cameraMove[3] = false;
            break;
          case SDLK_a:
            cameraMove[0] = false;
            break;
          case SDLK_d:
            cameraMove[1] = false;
            break;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        mouseDown = true;
        SDL_GetMouseState(&x, &y);
        downRect = {x + camera.getX() - ((x + camera.getX()) % 64), y + camera.getY() - ((y + camera.getY()) % 64), 63, 63};
        /*
        cout << "---------------------" << endl;
        cout << x << " " << y << endl;
        cout << camera.getX() << " " << camera.getY() << endl;
        cout << downRect.x << " " << downRect.y << endl;
        cout << "---------------------" << endl;
        */
        break;
      case SDL_MOUSEBUTTONUP:
        mouseDown = false;
        SDL_GetMouseState(&x, &y);
        upRect = {x - (x % 64), y - (y % 64), 64, 64};
        break;
        break;
      case SDL_MOUSEMOTION:

        //get mouse position, draw rect
        SDL_GetMouseState(&x, &y);
        mouseRect = {x - 8, y - 8, 16, 16};

        //cout << x << " " << y << endl;
    }
  }
  return 0;
}

void Display::render(Camera camera) {
  //clear screen
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);

  //draw rect
  /*
  SDL_Rect rect = {400, 400, 400, 400};
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &rect);
  */

  //SDL_SetRenderDrawColor(renderer, 0x00, 0x88, 0x00, 0xFF);

  //render tiles
  for(int i = 0; i < SCREEN_WIDTH / 64 + 1; i++)
    for(int j = 0; j < SCREEN_HEIGHT / 64 + 1; j++) {
      //SDL_SetRenderDrawColor(renderer, 0x00, 0x88, 0x00, 0xFF);

      tile.x = i * 64;
      tile.y = j * 64;
      tile.w = 64;
      tile.h = 64;

      render(gridTexture, tile, camera);

      //if((i + j) % 2 == 0)
      //  SDL_RenderFillRect(renderer, &tile);
    }

  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

  //SDL_RenderFillRect(renderer, &downRect);
  
  //render down rect
  render(downRect, camera);
  
  //render HUD
  SDL_Rect msgRect;
  msgRect.x = 100;
  msgRect.y = 100;
  SDL_QueryTexture(robotoTestString, NULL, NULL, &msgRect.w, &msgRect.h);

  SDL_Rect sideticksRect;
  sideticksRect.x = 0;
  sideticksRect.y = 0;
  sideticksRect.w = 32;
  sideticksRect.h = SCREEN_HEIGHT;
  
  SDL_RenderCopy(renderer, sideticksTexture, NULL, &sideticksRect);

  //render crosshair
  SDL_RenderCopy(renderer, mouseTexture, NULL, &mouseRect);

  //show frame
  SDL_RenderPresent(renderer);
}

void Display::render(SDL_Rect globalArea, Camera camera) {
  if(onScreen(globalArea, camera)) {
    globalArea.x -= camera.getX();
    globalArea.y -= camera.getY();
    SDL_RenderFillRect(renderer, &globalArea);
  }
}

void Display::render(SDL_Texture * texture, SDL_Rect globalArea, Camera camera) {

  if(onScreen(globalArea, camera)) {
    globalArea.x -= camera.getX();
    globalArea.y -= camera.getY();
    SDL_RenderCopy(renderer, texture, NULL, &globalArea);
  }
}

bool Display::onScreen(SDL_Rect rect, Camera camera) {
  if(rect.x > camera.getX() + camera.getWidth() || rect.x + rect.w < camera.getX())
    return false;

  if(rect.y > camera.getY() + camera.getHeight() || rect.y + rect.h < camera.getY())
    return false;

  return true;
}

void Display::stop() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}

int main(int argc, char * argv[]) {
  Display disp;

  if(disp.init()) {
    cout << "Init Error" << endl;
    return -1;
  }

  if(disp.load()) {
    cout << "Load Error" << endl;
    return -1;
  }

  int quit = 0;
  int frames = 0;
  mouseRect = {0, 0, 10, 10};
  unsigned int begin = SDL_GetTicks();
  while(!quit) {
    if(SDL_GetTicks() - begin > 1000) {
      begin = SDL_GetTicks();
      cout << "FPS: " << frames << endl;
      frames = 0;
    }
    if(disp.handleEvents() == -1)
      break;


    //handle camera movements every render
    //TODO move this to another thread, so it is consistent at different speeds
    if(cameraMove[0])
      camera.addX(-1);
    if(cameraMove[1])
      camera.addX(1);
    if(cameraMove[2])
      camera.addY(-1);
    if(cameraMove[3])
      camera.addY(1);

    disp.render(camera);
    frames++;
  }
  disp.stop();

  return 0; 
}


