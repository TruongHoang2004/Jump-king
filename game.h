#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class game
{
public:
    game();
    ~game();

    bool init( std::string title, int width, int height );
    void update();
    void handleEvents();
    bool isRunning();
    void render();
    void clean();
private:
    bool running;
    SDL_Window * gWindow;
};

#endif // GAME_H_
