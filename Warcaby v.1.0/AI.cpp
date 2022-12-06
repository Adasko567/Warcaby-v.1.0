#include "AI.h"

#include <iostream>

#include "plansza.h"
#include "rozgrywka.h"

using namespace std;

int evaluate(Plansza pStart, Plansza pEnd) {
	int BStart = 0, CzStart = 0;
	int BEnd = 0, CzEnd = 0;
	int QBStart = 0, QCzStart = 0;
	int QBEnd = 0, QCzEnd = 0;
	int BDistanceStart = 0, CzDistanceStart = 0;
	int BDistanceEnd = 0, CzDistanceEnd = 0;
	for (int i = 0; i < pStart.pTab.size(); i++) {
		if (pStart.pTab[i].color == 0) {
			CzDistanceStart += pStart.pTab[i].PozY;
			if (pStart.pTab[i].status == 1)
				QCzStart;
			else
				CzStart++;
		}
		else {
			BDistanceStart += 9 - pStart.pTab[i].PozY;
			if (pStart.pTab[i].status == 1)
				QBStart++;
			else
				BStart++;
		}
	}
	for (int i = 0; i < pEnd.pTab.size(); i++) {
		if (pStart.pTab[i].color == 0) {
			CzDistanceEnd += pEnd.pTab[i].PozY;
			if (pEnd.pTab[i].status == 1)
				QCzEnd;
			else
				CzEnd++;
		}
		else {
			BDistanceEnd += 9 - pEnd.pTab[i].PozY;
			if (pEnd.pTab[i].status == 1)
				QBEnd++;
			else
				BEnd++;
		}
	}
	int ValueofDistance = ((BDistanceEnd - BDistanceStart) - (CzDistanceEnd - CzDistanceStart));
	int ValueOfPieces = ((BEnd - BStart) - (CzEnd - CzStart)) * 10;
	int ValueOfQueens = ((QBEnd - QBStart) - (QCzEnd - QCzStart)) * 30;
	cout << ValueofDistance + ValueOfPieces + ValueOfQueens << ", ";
	return ValueofDistance + ValueOfPieces + ValueOfQueens;
}

void AI::SaveStart(Plansza p) {
	pStart = p;
}

void AI::Analize(Plansza p, vector <Plansza> &child, bool maximizingPlayer) {
	for (int i = 0; i < p.pTab.size(); i++) {
		if (p.pTab[i].color == maximizingPlayer) {
			vector <vector<int>> tab;
			Rozgrywka r;
			r.T(maximizingPlayer);
			r.AnalizaRuchu(p, tab, p.pTab[i].PozX, p.pTab[i].PozY);
			for (int j = 0; j < tab.size(); j++) {
				vector <vector<int>> tab2 = tab;
				child.push_back(p);
				r.Ruch(child[child.size() - 1], tab2, tab[j][0], tab[j][1]); // dla x,y tab2 mo¿e
				tab2.clear();
			}
			tab.clear();
		}
	}
}

int AI::minimax(Plansza p, int depth, int alpha, int beta, bool maximizingPlayer) {
	int eval;
	if (depth == 0) // || gameOver
		return evaluate(pStart , p);

	vector <Plansza> child;

	Analize(p, child, maximizingPlayer);

	//cout << child.size();

	if (maximizingPlayer) {
		int maxEval = numeric_limits<int>::max();
		for (size_t i = 0; i < child.size(); i++) {
			eval = minimax(child[i], depth - 1, alpha, beta, false);
			maxEval = max(alpha, eval);
			alpha = max(alpha, eval);
			if (beta <= alpha)
				break;
		}
		child.clear();
		return maxEval;
	}
	else {
		int minEval = numeric_limits<int>::min();
		for (size_t i = 0; i < child.size(); i++) {
			eval = minimax(child[i], depth - 1, alpha, beta, true);
			minEval = min(alpha, eval);
			alpha = min(alpha, eval);
			if (beta <= alpha)
				break;
		}
		child.clear();
		return minEval;
	}
}

/*
void AI::RuchAI(Plansza p, bool tura, int &xPoz, int &yPoz) {
	SaveStart(p);
	int max = numeric_limits<int>::min();
	int value;
	for (int i = 0; i < p.pTab.size(); i++) {
		vector <vector<int>> tab;
		Rozgrywka r;
		r.AnalizaRuchu(p, tab, p.pTab[i].PozX, p.pTab[i].PozY);
		for (int i = 0; i < tab.size(); i++) {
			value = minimax(p, 3, numeric_limits<int>::min(), numeric_limits<int>::max(), tura);
			if (value > max) {
				max = value;
				xPoz = tab[i][0];
				yPoz = tab[i][1];
			}
		}
		tab.clear();
	}
}
*/