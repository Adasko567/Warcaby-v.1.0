#include "rozgrywka.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <cmath>

#include "plansza.h"
#include "AI.h"


using namespace std;

bool Between(int x1, int x2, int a) {
	if ((x1 > a && x2 < a) || (x1 < a) && (x2 > a))
		return true;
	else
		return false;
}

bool CheckIfEmpty(Plansza p, int x, int y) {
	if (x < 0 || y < 0 || x > 9 || y > 9)
		return false;
	for (int i = 0; i < p.pTab.size(); i++) {
		if (x == p.pTab[i].PozX && y == p.pTab[i].PozY) {
			return false;
		}
	}
	return true;
}

void Rozgrywka::RuchAI(Plansza p, vector <vector<int>>& t, int& xPoz, int& yPoz) {
	AI a;
	a.SaveStart(p);
	if (tura == 1) {
		int max = numeric_limits<int>::min();
		int value;
		for (int i = 0; i < p.pTab.size(); i++) {
			if (p.pTab[i].color == tura) {
				vector <vector<int>> tab;
				AnalizaRuchu(p, tab, p.pTab[i].PozX, p.pTab[i].PozY);
				for (int j = 0; j < tab.size(); j++) {
					value = a.minimax(p, 1, numeric_limits<int>::min(), numeric_limits<int>::max(), tura);
					if (value > max) {
						max = value;
						xPoz = tab[j][0];
						yPoz = tab[j][1];
						
					}
				}
				tab.clear();
			}
		}
	}
	else {
		int max = numeric_limits<int>::max();
		int value = numeric_limits<int>::max();	
		int _pSel , _xSel, _ySel;
		for (int i = 0; i < p.pTab.size(); i++) {
			if (p.pTab[i].color == tura) {
				vector <vector<int>> tab;
				AnalizaRuchu(p, tab, p.pTab[i].PozX, p.pTab[i].PozY);
				for (int j = 0; j < tab.size(); j++) {
					value = a.minimax(p, 2, numeric_limits<int>::min(), numeric_limits<int>::max(), tura);
					if (value < max) {
						max = value;
						xPoz = tab[j][0];
						yPoz = tab[j][1];
						_pSel = i;
						_xSel = p.pTab[i].PozX;
						_ySel = p.pTab[i].PozY;
						t = tab;
					}
				}
				tab.clear();
			}
		}
		pSel = _pSel;
		xSel = _xSel;
		ySel = _ySel;
	}
}


void Rozgrywka::CheckIfEmptyQ(Plansza p, vector <vector<int>>& tab, int x, int y) {
	int dirX = x - p.pTab[pSel].PozX , dirY = y - p.pTab[pSel].PozY;
	while (x >= 0 && y >= 0 && x < 10 && y < 10 && CheckIfEmpty(p, x, y) == 1)  {
		tab.push_back({ x, y });
		x += dirX;
		y += dirY;
	}
}

void Rozgrywka::GameLoop(Plansza& p, vector <vector<int>>& tab, int x, int y) {
	if (!EnabledAI) {
		Ruch(p, tab, x, y);
		PassTurn(p, x, y);
		if (turnEnd == 0)
			AnalizaRuchu(p, tab, x, y);
	}
	else {
		AI a;
		if (tura == 1) {
			Ruch(p, tab, x, y);
			PassTurn(p, x, y);
			if (turnEnd == 0)
				AnalizaRuchu(p, tab, x, y);
		}
		if (tura == 0) {
			Ruch(p, tab, xAI, yAI);
			PassTurn(p, xAI, yAI);
			if (turnEnd == 0) {
				RuchAI(p, tab, xAI, yAI);
			}
		}
	}
}

void Rozgrywka::PassTurn(Plansza& p, int x, int y) {
	turnEnd = 0;
	if (tura == 1 && killer != -1)
		pSel--;
	if (flagRuch == 1 && (killer == -1 || ((pSel == killer && p.pTab[killer].status == 0 && CanYouKill(p, p.pTab[killer].PozX, p.pTab[killer].PozY) == false) || (pSel == killer && p.pTab[killer].status == 1 && CanYouKillQ(p, killerX, killerY) == false)))) {
		if (tura == 1)
			tura = 0;
		else
			tura = 1;
		flagRuch = 0;
		turnEnd = 1;
		killerX = -1;
		killerY = -1;
		killer = -1;
	}
}

bool Rozgrywka::CanAnyoneKill(Plansza p) {
	for (int i = 0; i < p.pTab.size(); i++) {
		if (p.pTab[i].color == tura) {
			if (p.pTab[i].status == 0 && CanYouKill(p, p.pTab[i].PozX, p.pTab[i].PozY) == 1) {
				return 1;
			}
			if (p.pTab[i].status == 1 && CanYouKillQ(p, p.pTab[i].PozX, p.pTab[i].PozY) == 1) {
				return 1;
			}
		}
	}
	return 0;
}

void Rozgrywka::T(bool t) {
	tura = t;
}

bool Rozgrywka::CanYouKill(Plansza p, int x, int y) {
	for (int i = 0; i < p.pTab.size(); i++) {
		if (!CheckIfEmpty(p, x - 1, y - 1)) {
			if (p.pTab[i].color != p.pTab[pSel].color && p.pTab[i].PozX == x - 1 && p.pTab[i].PozY == y - 1) {
				if (CheckIfEmpty(p, x - 2, y - 2)) {
					return 1;
				}		
			}
		}
		if (!CheckIfEmpty(p, x + 1, y - 1)) {
			if (p.pTab[i].color != p.pTab[pSel].color && p.pTab[i].PozX == x + 1 && p.pTab[i].PozY == y - 1) {
				if (CheckIfEmpty(p, x + 2, y - 2)) {
					return 1;
				}
			}
		}
		if (!CheckIfEmpty(p, x - 1, y + 1)) {
			if (p.pTab[i].color != p.pTab[pSel].color && p.pTab[i].PozX == x - 1 && p.pTab[i].PozY == y + 1) {
				if (CheckIfEmpty(p, x - 2, y + 2)) {
					return 1;
				}
			}
		}
		if (!CheckIfEmpty(p, x + 1, y + 1)) {
			if (p.pTab[i].color != p.pTab[pSel].color && p.pTab[i].PozX == x + 1 && p.pTab[i].PozY == y + 1) {
				if (CheckIfEmpty(p, x + 2, y + 2)) {
					return 1;
				}
			}
		}
	}
	return 0;
}

bool Rozgrywka::CanYouKillQ(Plansza& p, int x, int y) {
	int dirX, dirY;
	int x2, y2;
	if (x == -1 || y == -1)
		return false;
	for (int i = 0; i < p.pTab.size(); i++) {
		if (p.pTab[i].color != p.pTab[pSel].color) {
			if (x + y == p.pTab[i].PozX + p.pTab[i].PozY || x - y == p.pTab[i].PozX - p.pTab[i].PozY) {
				if (x > p.pTab[i].PozX)
					dirX = -1;
				else
					dirX = 1;
				if (y > p.pTab[i].PozY)
					dirY = -1;
				else
					dirY = 1;
				x2 = x + dirX;
				y2 = y + dirY;
				while (x2 >= 0 && y2 >= 0 && x2 < 10 && y2 < 10) {
					if (x2 == p.pTab[i].PozX && y2 == p.pTab[i].PozY && CheckIfEmpty(p, x2 + dirX, y2 + dirY) == 1) {
						return true;
					}
					else if (CheckIfEmpty(p, x2, y2) == 0) {
						break;
					}
					x2 += dirX;
					y2 += dirY;
				}
			}
		}
	}
	return false;
}

void Rozgrywka::KillQ(Plansza& p, vector <vector<int>>& tab, int x, int y) {
	int dirX, dirY;
	int x2, y2;
	for (int i = 0; i < p.pTab.size(); i++) {
		if (p.pTab[i].color != p.pTab[pSel].color) {
			if (x + y == p.pTab[i].PozX + p.pTab[i].PozY || x - y == p.pTab[i].PozX - p.pTab[i].PozY) {
				if (x > p.pTab[i].PozX)
					dirX = -1;
				else
					dirX = 1;
				if (y > p.pTab[i].PozY)
					dirY = -1;
				else
					dirY = 1;
				x2 = x + dirX;
				y2 = y + dirY;
				while (x2 >= 0 && y2 >= 0 && x2 < 10 && y2 < 10) {
					if (x2 == p.pTab[i].PozX && y2 == p.pTab[i].PozY && CheckIfEmpty(p, x2 + dirX, y2 + dirY) == 1) {
						int x3 = x2 + dirX, y3 = y2 + dirY;
						pKill.push_back(i);
						while (x3 >= 0 && y3 >= 0 && x3 < 10 && y3 < 10) {
							if (CheckIfEmpty(p, x3, y3) == 1)
								tab.push_back({ x3,y3 });
							else
								break;
							x3 += dirX;
							y3 += dirY;
						}
					}
					else if (CheckIfEmpty(p, x2, y2) == 0) {
						break;
					}
					x2 += dirX;
					y2 += dirY;
				}
			}
		}
	}
}

void Rozgrywka::Kill(Plansza& p, vector <vector<int>>& tab, int x, int y) {
	for (int i = 0; i < p.pTab.size(); i++) {
		if (!CheckIfEmpty(p, x - 1, y - 1)) {
			if (p.pTab[i].color != p.pTab[pSel].color && p.pTab[i].PozX == x - 1 && p.pTab[i].PozY == y - 1 && CheckIfEmpty(p, x - 2, y - 2)) {
				pKill.push_back(i);
				tab.push_back({ x - 2, y - 2 });
			}
		}
		if (!CheckIfEmpty(p, x + 1, y - 1)) {
			if (p.pTab[i].color != p.pTab[pSel].color && p.pTab[i].PozX == x + 1 && p.pTab[i].PozY == y - 1 && CheckIfEmpty(p, x + 2, y - 2)) {
				pKill.push_back(i);
				tab.push_back({ x + 2, y - 2 });
			}
		}
		if (!CheckIfEmpty(p, x - 1, y + 1)) {
			if (p.pTab[i].color != p.pTab[pSel].color && p.pTab[i].PozX == x - 1 && p.pTab[i].PozY == y + 1 && CheckIfEmpty(p, x - 2, y + 2)) {
				pKill.push_back(i);
				tab.push_back({ x - 2, y + 2 });
			}
		}
		if (!CheckIfEmpty(p, x + 1, y + 1)) {
			if (p.pTab[i].color != p.pTab[pSel].color && p.pTab[i].PozX == x + 1 && p.pTab[i].PozY == y + 1 && CheckIfEmpty(p, x + 2, y + 2)) {
				pKill.push_back(i);
				tab.push_back({ x + 2, y + 2 });
			}
		}
	}
}

void Rozgrywka::Ruch(Plansza& p, vector <vector<int>>& tab, int& x, int& y) {
	AmongUs = 0;
	bool flag2 = 0; // jak bia³y zabija czarnego to bez tego sie robi s³abo
	if (tab.size() > 0) {
		for (int j = 0; j < p.pTab.size(); j++) {
			if (xSel == p.pTab[j].PozX && ySel == p.pTab[j].PozY) {
				for (int i = 0; i < tab.size(); i++) {
					if (tab[i][0] == x && tab[i][1] == y) {
						for (int k = 0; k < pKill.size(); k++) {
							if (Between(x, xSel, p.pTab[pKill[k]].PozX) && Between(y, ySel, p.pTab[pKill[k]].PozY)) {
								if (p.pTab[pKill[k]].color == 0)
									flag2 = 1;
								AmongUs = 1;
								p.pTab.erase(p.pTab.begin() + pKill[k]);
								break;
							}
						}
						if (flag2 == 1) {
							p.RuchPionka(p.pTab[j - 1], x, y);
							if (AmongUs == 1)
								killer = j - 1;
							if (y == 0)
								p.Queen(p.pTab[j - 1]);
						}
						else {
							p.RuchPionka(p.pTab[j], x, y);
							if (AmongUs == 1)
								killer = j;
							if (y == 9 || y == 0)
								p.Queen(p.pTab[j]);
						}
						if (AmongUs == 1) {
							killerX = x;
							killerY = y;
						}
						xSel = -100;
						ySel = -100;
						flagRuch = 1;

						break;
					}
				}
				break;
			}
		}
	}
	pKill.clear();
	tab.clear();
}

void Rozgrywka::AnalizaRuchu(Plansza& p, vector <vector<int>>& tab, int& x, int& y) {
	bool flag = 0; // czy jakis pionek zostal wybrany

	for (int i = 0; i < p.pTab.size(); i++) {
		if (p.pTab[i].PozX == x && p.pTab[i].PozY == y) {
			flag = 1;
			xSel = x;
			ySel = y;
			pSel = i;
			break;
		}
	}
	if (flag && (p.pTab[pSel].color == tura || EnabledAI == 1 )) {
		if (p.pTab[pSel].status == 0) {
			if (CanYouKill(p, x, y) == 1) {
				if ((killerX == x && killerY == y && flagRuch == 1) || flagRuch == 0)
					Kill(p, tab, x, y);
			}
			else if (CanAnyoneKill(p) == 0) {
				if (CheckIfEmpty(p, x - 1, y - 1) && (x - 1 >= 0 && y - 1 >= 0) && p.pTab[pSel].color == 1)
					tab.push_back({ x - 1, y - 1 });
				if (CheckIfEmpty(p, x + 1, y - 1) && (x + 1 >= 0 && y - 1 >= 0) && p.pTab[pSel].color == 1)
					tab.push_back({ x + 1, y - 1 });
				if (CheckIfEmpty(p, x - 1, y + 1) && (x - 1 >= 0 && y + 1 >= 0) && p.pTab[pSel].color == 0)
					tab.push_back({ x - 1, y + 1 });
				if (CheckIfEmpty(p, x + 1, y + 1) && (x + 1 >= 0 && y + 1 >= 0) && p.pTab[pSel].color == 0)
					tab.push_back({ x + 1, y + 1 });
			}
			//cout << CanAnyoneKill(p);
		}
		else {
			if (CanYouKillQ(p, x, y) == 1) {
				if ((killerX == x && killerY == y && flagRuch == 1) || flagRuch == 0) {
					KillQ(p, tab, x, y);
				}
			}
			else if (CanAnyoneKill(p) == 0) {
				CheckIfEmptyQ(p, tab, x - 1, y - 1);
				CheckIfEmptyQ(p, tab, x + 1, y - 1);
				CheckIfEmptyQ(p, tab, x - 1, y + 1);
				CheckIfEmptyQ(p, tab, x + 1, y + 1);
			}
		}
	}
}

