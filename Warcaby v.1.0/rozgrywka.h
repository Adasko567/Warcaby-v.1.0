#pragma once

#include <iostream>
#include <vector>

#include "plansza.h"
#include "AI.h"

using namespace std;

class Rozgrywka {
public:
	void AnalizaRuchu(Plansza& p, vector <vector<int>>& tab, int& x, int& y);
	void Ruch(Plansza& p, vector <vector<int>>& tab, int& x, int& y);
	void PassTurn(Plansza& p, int x, int y);
	void GameLoop(Plansza& p, vector <vector<int>>& tab, int x, int y);
	void Kill(Plansza& p, vector <vector<int>>& tab, int x, int y);
	bool CanYouKill(Plansza p, int x, int y);
	bool CanAnyoneKill(Plansza p);
	bool CanYouKillQ(Plansza& p, int x, int y);
	void CheckIfEmptyQ(Plansza p, vector <vector<int>>& tab, int x, int y);
	void KillQ(Plansza& p, vector <vector<int>>& tab, int x, int y);
	void RuchAI(Plansza p, vector <vector<int>>& t, int& xPoz, int& yPoz);
	void T(bool t);
private:
	int xSel = -100, ySel = -100;
	int pSel = -1;
	vector <int> pKill;
	bool tura = 1;
	bool flagRuch = 0;
	bool turnEnd = 0;
	int killerX = -1, killerY = -1;
	int killer = -1;
	bool AmongUs = 0;
	bool EnabledAI = 1;
	int xAI, yAI;
};