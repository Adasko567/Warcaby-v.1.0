#include "window.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "plansza.h"
#include "rozgrywka.h"

using namespace std;

const int g_width = 84;
const int g_height = 84;

Window::Window(const string& title, int width, int height) :
	_title(title), _width(g_width*width), _height(g_height*height)
{
	_closed = !init();
}

Window::~Window() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyTexture(_texture);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	SDL_Quit();
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "Failed to initialized SDL\n";
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		cerr << "Failed to initialize SDL_imag.h #PNG\n";
		return false;
	}
	if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG) {
		cerr << "Failed to initialize SDL_imag.h #JPG\n";
		return false;
	}
	
	_window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, _height,
		0
	);
	if (_window == nullptr) {
		cerr << "Failed to create window \n";
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == nullptr) {
		cerr << "Failed to create renderer\n";
		return false;
	}

	return true;
}

void Window::pollEvents() {
	SDL_Event event;
	bool poll = 0;
	while (!poll) {
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				_closed = true;
				poll = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					_closed = true;
					poll = true;
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				xPress = event.motion.x / g_width;
				yPress = event.motion.y / g_height;
				poll = true;
				break;
			default:
				break;
			}
		}
	}
}

void Window::gameOver() {
	_closed = true;
}

void drawRect(SDL_Renderer* renderer, int xPos, int yPos, int ColorRed, int ColorGreen, int ColorBlue) {
	SDL_Rect rect;
	rect.w = g_width;
	rect.h = g_height;
	rect.x = xPos * g_width;
	rect.y = yPos * g_height;

	SDL_SetRenderDrawColor(renderer, ColorRed, ColorGreen, ColorBlue, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void drawIMG(SDL_Renderer* renderer, SDL_Texture* texture, int xPos, int yPos, const string& image_path) {
	SDL_Rect rect;
	rect.w = g_width;
	rect.h = g_height;
	rect.x = xPos * g_width;
	rect.y = yPos * g_height;

	auto surface = IMG_Load(image_path.c_str());
	if (!surface) {
		cerr << "Failed to create surface\n";
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		cerr << "Failed to create texture\n";
	}
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void drawBackground(SDL_Renderer* renderer, SDL_Texture* texture, int xPos, int yPos, const string& image_path) {
	SDL_Rect rect;
	rect.w = 900;
	rect.h = 900;
	rect.x = xPos * g_width;
	rect.y = yPos * g_height;

	auto surface = IMG_Load(image_path.c_str());
	if (!surface) {
		cerr << "Failed to create surface\n";
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		cerr << "Failed to create texture\n";
	}
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

Plansza p;
Rozgrywka r;
vector <vector<int>> t;

void Window::draw() const {	
	r.GameLoop(p, t, xPress, yPress);
	SDL_SetRenderDrawColor(_renderer, 100, 255, 60, 255);
	SDL_RenderClear(_renderer);
	for (int i = 0; i < g_height; i++) {
		for (int j = 0; j < g_width; j++) {
			if ((j + i) % 2 == 0) 
				drawRect(_renderer, j, i, 200, 200, 200);
			else {
				if (j == xPress && i == yPress) {
					drawRect(_renderer, j, i, 255, 255, 0);
				}
				else
					drawRect(_renderer, j, i, 100, 50, 0);
				for (int k = 0; k < t.size(); k++) {
					if (t[k][0] == j && t[k][1] == i)
						drawRect(_renderer, j, i, 100, 255, 0);
				}
			}
			for (int k = 0; k < p.pTab.size(); k++) {
				if (p.pTab[k].PozX == j && p.pTab[k].PozY == i && p.pTab[k].color == 0)
					if (p.pTab[k].status == 0)
						drawIMG(_renderer, _texture, j, i, "C:/Users/kubas/Desktop/warcaby/Cz.png");
					else
						drawIMG(_renderer, _texture, j, i, "C:/Users/kubas/Desktop/warcaby/QueenCz.png");
				if (p.pTab[k].PozX == j && p.pTab[k].PozY == i && p.pTab[k].color == 1)
					if (p.pTab[k].status == 0)
						drawIMG(_renderer, _texture, j, i, "C:/Users/kubas/Desktop/warcaby/B.png");
					else
						drawIMG(_renderer, _texture, j, i, "C:/Users/kubas/Desktop/warcaby/QueenB.png");
			}
		}
	}
	SDL_RenderPresent(_renderer);
}
