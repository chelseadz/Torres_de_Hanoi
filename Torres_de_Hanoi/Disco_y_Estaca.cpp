/*****************************************************************//**
 * \file   Disco_y_Estaca.cpp
 * \brief  Implementación de funciones para disco y estaca.
 * 
 * \author Equipo Rocket
 * \date   19/05/2021
 *********************************************************************/

#include "Disco_y_Estaca.h"

#include "Utileria.h"

int Estaca::max_discs;
int Estaca::stick_height;
int Estaca::stick_width;

bool Estaca::Initialize_stakes(int height, int width, int max_discs) {
	if (max_discs < 0 || max_discs > _MAX_DISC_CAPACTITY)
		return false;

	Estaca::max_discs = max_discs;
	Estaca::stick_height = height;
	Estaca::stick_width = width;

	return true;
}

Estaca::Estaca(unsigned short base_x_pos, unsigned short base_y_pos) {


	if (base_x_pos < _WINDOW_WIDTH && base_y_pos < _WINDOW_HEIGTH) {
		x_base_pos = base_x_pos;
		y_base_pos = base_y_pos;
	} else
		throw std::invalid_argument("Posici\243n  de base inv\240lida.");


	try {
		discs = new Disco[max_discs];
	} catch (const std::bad_alloc&) {
		throw std::runtime_error("No se pudo alocar memoria para los discos.");
	}

	curr_n_discs = curr_disc_column_height = 0;
}

Estaca::~Estaca() {
	if (discs != NULL) delete[] discs;
}

bool Estaca::push_back(const Disco& disc) {
	if (curr_n_discs == max_discs) return false;

	discs[curr_n_discs] = disc;

	discs[curr_n_discs].x_pos = x_base_pos;
	discs[curr_n_discs].y_pos = y_base_pos + curr_disc_column_height + discs[curr_n_discs].height / 2;

	curr_disc_column_height += disc.height;

	return true;

}

const Disco& Estaca::last() {
	return discs[curr_n_discs - 1];
}

bool Estaca::pop_back() {
	if (curr_n_discs == 0) return false;
	
	curr_disc_column_height -= discs[curr_n_discs - 1].height;
	--curr_n_discs;
	return true;
}

void Disco::draw() {
	//Ahorita se dibuja solo un rectangulo del color del disco. Puede cambiar el dibujo en el futuro. :)
	al_draw_filled_rectangle(x_pos + width / 2, y_pos + height / 2,
		x_pos - width / 2, y_pos - height / 2, color);
}
