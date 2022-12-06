#pragma once

#include <iostream>

#include "plansza.h"
#include "rozgrywka.h"

using namespace std;

class AI {
public:
	void SaveStart(Plansza p);
	int minimax(Plansza p, int depth, int alpha, int beta, bool maximizingPlayer);
	void Analize(Plansza p, vector <Plansza> &child, bool maximizingPlayer);
	//void RuchAI(Plansza p, bool tura, int& xPoz, int& yPoz);
private:
	int maxEval = numeric_limits<int>::max();
	int minEval = numeric_limits<int>::min();

	int NumOfChildren = 0;

	Plansza pStart; // W planszy zrobiæ funkcje inicjuj¹c¹ plansze a nie u¿ywaæ konstruktora
};