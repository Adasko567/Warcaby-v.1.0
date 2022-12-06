#include "plansza.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

using namespace std;

Plansza::Plansza() {
	int x = 40;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if ((i + j) % 2 != 0 && x > 20) {
				Pionek p(0, 0, j, i);
				pTab.push_back(p);
				x--;
			}
			if ((i + j) % 2 != 0 && x > 0 && i > 5) {
				Pionek p(1, 0, j, i);
				pTab.push_back(p);
				x--;
			}
		}
	}; 
}

void Plansza::RuchPionka(Pionek& p, int x, int y) {
	p.PozX = x;
	p.PozY = y;
}

void Plansza::Queen(Pionek& p) {
	p.status = 1;
}