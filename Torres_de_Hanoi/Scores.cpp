/*****************************************************************//**
 * \file   Scores.cpp
 * \brief  Implementación de "Scores.h"
 * 
 * \author Equipo Rocket
 * \date   22/05/2021
 *********************************************************************/

#include "Scores.h"

#include "Utileria.h"

#include <fstream>

bool Score::operator< (const Score& s) {
	return moves < s.moves;
}

Score* GetPreviousScores(const char* filename) {
	std::ifstream file(filename);

	if (file.is_open() && file.good()) {
		int n;
		file >> n;

		if (file.good()) {
			Score* scores;
			try {
				scores = new Score[n];
			} catch (const std::bad_alloc&) {
				return NULL;
			}

			for (int i = 0; i < n; ++i) {
				file >> scores[i].name >> scores[i].moves;
			}

			if (!file.fail()) {
				Quicksort(scores, 0, n - 1);
				return scores;
			} else {
				delete[] scores;
				return NULL;
			}
		}
		return NULL;

	} else {
		return NULL;
	}
}
