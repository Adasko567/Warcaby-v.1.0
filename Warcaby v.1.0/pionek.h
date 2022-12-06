#pragma once

#include <iostream>

using namespace std;

class Pionek {
public:
	Pionek(bool _clr, bool _st, int _PozX, int _PozY);
	int PozX, PozY;
	bool color; // 0 - czarny, 1 - bia³y
	bool status; // 0 - zwyk³y, 1 - królowa
private:
	
};