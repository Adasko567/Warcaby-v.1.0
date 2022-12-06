#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

#include "plansza.h"
#include "rozgrywka.h"

using namespace std;

class Window {
public:
	Window(const string& title, int width, int height);
	~Window();

	void gameOver();
	void pollEvents();
	void draw() const;

	inline bool isClosed() const { return _closed; }
private:
	bool init();
private:
	string _title;
	int _width = 0;
	int _height = 0;
	bool _closed = false;

	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	SDL_Texture* _texture = nullptr;

private:
	int x, y;
	int xPress = -100, yPress = -100;
};