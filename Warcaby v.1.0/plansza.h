#pragma once

#include <iostream>
#include <vector>

#include "pionek.h"

using namespace std;

class Plansza {
public:
	vector <Pionek> pTab;
	Plansza();
	void RuchPionka(Pionek& p, int x, int y);
	void Queen(Pionek& p);
private:
	
};