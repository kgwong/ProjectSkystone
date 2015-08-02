#ifndef FATALERRORS_H
#define FATALERRORS_H

#include <iostream>
#include <string>

#include <SDL\SDL.h>

void MySDL_Error(const std::string& message);
void MySDL_Error(std::ostream &os, const std::string& message);

void printCoord(int x, int y);


#endif //FATALERRORS_H