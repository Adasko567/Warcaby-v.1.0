#pragma once

#include <iostream>

using namespace std;

class Pionek {
public:
	Pionek(bool _clr, bool _st, int _PozX, int _PozY);
	int PozX, PozY;
	bool color; // 0 - czarny, 1 - bia�y
	bool status; // 0 - zwyk�y, 1 - kr�lowa
private:
	
};