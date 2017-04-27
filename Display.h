 /*****************************************************************************

                                                         Author: Jason Ma
                                                         Date:   Feb 07 2017
                                      SDLGame

 File Name:     Display.h
 Description:   SDL interface, handles events and displays everything
                appropriately.
 *****************************************************************************/

//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <string>
#include "Camera.h"

#ifndef DISPLAY_H
#define DISPLAY_H

class Display{
  public:
  	int init();
  	int load();
  	int handleEvents();
    bool onScreen(SDL_Rect rect, Camera camera);
  	void render(Camera camera);
    void render(SDL_Rect area, Camera camera);
    void render(SDL_Texture * texture, SDL_Rect area, Camera camera);
  	void stop();

    SDL_Texture * loadTexture(std::string path);
    SDL_Texture * loadTTFString(TTF_Font * font, SDL_Color color, const char * message);
    TTF_Font * loadTTF(const char *, int size);

};

#endif /* DISPLAY_H */