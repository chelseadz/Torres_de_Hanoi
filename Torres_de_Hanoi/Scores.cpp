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
#include <cstring>


bool Score::operator< (const Score& s) {
	return moves < s.moves;
}

Score* Score::operator=(const Score& s) {
	moves = s.moves;
	strncpy_s(name, _MAX_NAME_CHARS, s.name, _MAX_NAME_CHARS);
	return this;
}

Score* GetPreviousScores(const char* filename, int& n_scores) {
	std::ifstream file(filename);

	if (file.is_open() && file.good()) {
		int n;
		file >> n;

		if (file.good()) {
			Score* scores;
			try {
				scores = new Score[n];
			} catch (const std::bad_alloc&) {
				n_scores = 0;
				return NULL;
			}

			n_scores = n;

			for (int i = 0; i < n; ++i) {
				file >> scores[i].name >> scores[i].moves;
			}

			if (!file.fail()) {
				Quicksort(scores, 0, n - 1);
				return scores;
			} else {
				delete[] scores;
				n_scores = 0;
				return NULL;
			}
		}
	}

	n_scores = 0;
	return NULL;
}


void AddScoresToFile(const char* filename, Score* scores, int size, const Score& last) {

	std::ofstream file(filename);

	if (file.is_open() && file.good()) {
		Quicksort(scores, 0, size - 1);

		if (size > 4 && last.moves <= scores[size - 1].moves) size = 4;

		file << size + 1 << '\n';

		for (int i = 0; i < size; ++i)
			file << scores[i].name << ' ' << scores[i].moves << '\n';

		file << last.name << ' ' << last.moves << '\n';
	
		file.close();
	}

}
