#include "pionek.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

Pionek::Pionek(bool _clr, bool _st, int _PozX, int _PozY) {
	color = _clr;
	status = _st;
	PozX = _PozX;
	PozY = _PozY;
}