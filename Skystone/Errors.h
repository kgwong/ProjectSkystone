#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include <string>

#include <SDL\SDL.h>

void MySDL_Error(const std::string& message);

SDL_Window* MySDL_CreateWindow(const char* title,
									int x, int y, int w,
									int h, Uint32 flags);

SDL_Renderer* MySDL_CreateRenderer(SDL_Window* window,
									int index, Uint32 flags);

void MySDL_RenderCopy(SDL_Renderer* renderer,
						SDL_Texture* texture,
						const SDL_Rect* srcrect,
						const SDL_Rect* dstrect);

void printCoord(int x, int y);


#endif //ERRORS_H