/*****************************************************************//**
 * \file   Disco_y_Estaca.cpp
 * \brief  Implementación de funciones para disco y estaca.
 * 
 * \author Equipo Rocket
 * \date   19/05/2021
 *********************************************************************/

#include "Disco_y_Estaca.h"

#include "Utileria.h"

#include <cstdlib>

#define _ARC_HEIGHT 100

#define _AN_TIME 2.0f

int Estaca::max_discs;
int Estaca::stick_height;
int Estaca::stick_width;

bool Estaca::Initialize_stakes(int height, int width, int _max_discs) {
	if (_max_discs < 0 || _max_discs > _MAX_DISC_CAPACTITY)
		return false;

	Estaca::max_discs = _max_discs;
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
		discs = NULL;
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
	discs[curr_n_discs].y_pos = y_base_pos - curr_disc_column_height - discs[curr_n_discs].height / 2;

	curr_disc_column_height += disc.height;

	++curr_n_discs;

	return true;

}

const Disco& Estaca::last() {
	if (curr_n_discs == 0) throw std::invalid_argument("No hay discos.");
	return discs[curr_n_discs - 1];
}

bool Estaca::pop_back() {
	if (curr_n_discs < 1) return false;
	
	curr_disc_column_height -= discs[curr_n_discs - 1].height;
	--curr_n_discs;
	return true;
}

void Disco::draw() {
	//Elipse de abajo
	al_draw_filled_ellipse(x_pos, y_pos + height / 3, width / 2,
		-height / 3, color);
	//rectángulo del centro
	al_draw_filled_rectangle(x_pos - width / 2, y_pos, x_pos + width / 2,
		y_pos + height / 3, color);
	//elipse de arriba
	al_draw_filled_ellipse(x_pos, y_pos, width / 2, height / 3,
		al_map_rgb(100, 60, 0));
}


void Estaca::PrintRod() {
	//Palo Estaca

	//Estaca
	al_draw_filled_rectangle((-stick_width) / 2 + x_base_pos, y_base_pos,
		(stick_width) / 2 + x_base_pos, y_base_pos - stick_height, al_map_rgba_f(0, 0, 0.5, 0.3));

	for (int i = 0; i < curr_n_discs; i++) {
		discs[i].draw();
	}

}

bool Estaca::full() {
	if (curr_n_discs == max_discs) return true;
	return false;
}


bool Estaca::move_to_stake(Estaca& dest, bool& moving) {
	
	//Estas variables estáticas solo se inicializan la primera vez que se llama a la función.
	static bool first = 1;

	static Disco* moving_disc;
	static float vy_1, vx_2, vy_3;


	if (first) {
		if (curr_n_discs == 0) return false;
		moving_disc = &discs[curr_n_discs - 1];
		if (dest.full()) return false;

		//Calcular velocidadades en px / cuadro
		vy_1 = 3.0f * (moving_disc->y_pos - (y_base_pos - Estaca::stick_height)) / (_AN_TIME * _FPS);
		vx_2 = 3.0f * (dest.x_base_pos - x_base_pos) / (_AN_TIME * _FPS);
		vy_3 = 3.0f * (Estaca::stick_height - dest.curr_disc_column_height - moving_disc->height / 2.0f) / 
			(_AN_TIME * _FPS);

		first = 0;
	}
	


	if (moving_disc->y_pos > y_base_pos - Estaca::stick_height &&
		moving_disc->x_pos == x_base_pos) {

		moving_disc->y_pos -= vy_1;

	}
	else if (moving_disc->y_pos <= y_base_pos - Estaca::stick_height && moving_disc->x_pos < dest.x_base_pos) {
		moving_disc->x_pos += vx_2;
		moving_disc->y_pos = Elipse((dest.x_base_pos - x_base_pos) / 2.0f,
			_ARC_HEIGHT, (x_base_pos + dest.x_base_pos) / 2.0f, y_base_pos - Estaca::stick_height,
			moving_disc->x_pos);

	}
	else if (moving_disc->x_pos >= dest.x_base_pos) {
		moving_disc->x_pos = dest.x_base_pos;
		moving_disc->y_pos += vy_3;

		if (moving_disc->y_pos >= dest.y_base_pos - dest.curr_disc_column_height - moving_disc->height / 2.0f) {
			moving = 0;
			first = 1;

			dest.push_back(*moving_disc);
			pop_back();
			moving_disc = NULL;
		}
	
	}

	return true;
}



