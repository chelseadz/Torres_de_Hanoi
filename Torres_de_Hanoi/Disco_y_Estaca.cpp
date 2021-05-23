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
#include <climits>
#include <iostream>

#define _COLUMN_PORTION_FILENAME "estaca_media_mas_larga.png"
#define _COLUMN_WIDTH 27
#define _COLUMN_HEIGHT 37

#define _NULL_DISCS INT_MAX

int Estaca::max_discs = _NULL_DISCS;
int Estaca::stick_height;
int Estaca::stick_width;

bool Estaca::Initialize_stakes(int height, int width, int _max_discs) {
	if ((_max_discs < 0 || _max_discs > _MAX_DISC_CAPACTITY) && _max_discs != _NULL_DISCS)
		return false;

	Estaca::max_discs = _max_discs;
	Estaca::stick_height = height;
	Estaca::stick_width = width;

	return true;
}

Estaca::Estaca(unsigned short base_x_pos, unsigned short base_y_pos) {


	if (base_x_pos < _WINDOW_WIDTH && base_y_pos < _WINDOW_HEIGHT) {
		x_base_pos = base_x_pos;
		y_base_pos = base_y_pos;
	} else
		throw std::invalid_argument("Posici\243n  de base inv\240lida.");

	if (max_discs == _NULL_DISCS)
		throw std::logic_error("Clase Estaca no est\240 inicializada.");

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
	discs[curr_n_discs].y_pos = y_base_pos - curr_disc_column_height -  discs[curr_n_discs].height / 2;

	curr_disc_column_height += y_base_pos - discs[curr_n_discs].y_pos - curr_disc_column_height;

	++curr_n_discs;

	return true;

}

const Disco& Estaca::last() {
	if (curr_n_discs == 0) throw std::logic_error("No hay discos.");
	return discs[curr_n_discs - 1];
}

bool Estaca::pop_back() {
	if (curr_n_discs < 1) return false;
	
	curr_disc_column_height -= discs[curr_n_discs - 1].height / 2.0f;
	if (curr_n_discs == 1) curr_disc_column_height = 0;

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
		al_map_rgb(100, 70, 0));

}


void Estaca::PrintRodDiscs() {

	for (int i = 0; i < curr_n_discs; i++) {
		discs[i].draw();
	}

	if (curr_n_discs != 0) {
		int dif = discs[curr_n_discs - 1].y_pos - (y_base_pos - stick_height);
		if (dif > 0) {
			if (curr_n_discs > 1 && dif > discs[curr_n_discs - 2].height / 2.0f) {
				dif = discs[curr_n_discs - 2].height / 2.0f;
			} else if (dif > discs[curr_n_discs - 1].height / 2.0f) {
				dif = discs[curr_n_discs - 1].height / 2.0f;
			}
			if (dif > _COLUMN_HEIGHT) 
				dif = _COLUMN_HEIGHT;

			ALLEGRO_BITMAP* column_portion = al_load_bitmap(_COLUMN_PORTION_FILENAME);
			try {
				initialize_al_component(column_portion, "column portion image.");

				al_draw_bitmap_region(column_portion, 0, _COLUMN_HEIGHT - dif, _COLUMN_WIDTH, dif,
					discs[curr_n_discs -1].x_pos - _COLUMN_WIDTH / 2.0f,
					discs[curr_n_discs - 1].y_pos - dif,	0);

			} catch (const std::runtime_error& e) {
				std::cerr << e.what() << '\n';
			}

			al_destroy_bitmap(column_portion);
		}
	}
}


void Estaca::InitDiscsAndRods() {

	if (curr_n_discs != 0) throw std::logic_error("La estaca no se puede inicializar.");

	const float _INIT_D_WIDTH = _LARGEST_DISC_WIDTH;
	const float _INIT_D_HEIGHT = _LARGEST_DISC_HEIGHT;
	
	for (int i = 0; i < max_discs; i++) {
		ALLEGRO_COLOR disc_color;
		switch (i)
		{
			case 0: 
				disc_color = VERY_PALE_YELLOW;
				break;
			case 1: 
				disc_color = PALE_YELLOW;
				break;
			case 2: 
				disc_color = PALE_YELLOW_RED;
				break;
			case 3: 
				disc_color = YELLOW_RED;
				break;
			case 4: 
				disc_color = MAXIMUM_YELLOW_RED;
				break;
			case 5: 
				disc_color = BRORANGE;
				break;
			case 6: 
				disc_color = BRONZE;
				break;
			case 7: 
				disc_color = METALIC_BRONZE;
				break;
		}
		push_back(Disco{ _INIT_D_WIDTH - (0.1f) * i * _INIT_D_WIDTH,
			_INIT_D_HEIGHT - (0.085f) * i * _INIT_D_HEIGHT, 0, 0, disc_color });
	}
}

bool Estaca::full() {
	if (curr_n_discs == max_discs) return true;
	return false;
}


bool Estaca::move_to_stake(Estaca* dest, bool& moving, bool finalize) {
	
	//Estas variables estáticas solo se inicializan la primera vez que se llama a la función.
	static bool first = 1;

	static Disco* moving_disc;
	static float vy_1, vx_2, vy_3;

	if (dest->curr_n_discs != 0 && curr_n_discs != 0 && last().width > dest->last().width)
		return false;

	if (first) {
		if (curr_n_discs == 0) return false;
		moving_disc = &discs[curr_n_discs - 1];
		if (dest->full()) return false;

		//Calcular velocidadades en px / cuadro
		vy_1 = 3.0f * (moving_disc->y_pos - (y_base_pos - Estaca::stick_height)) / (_AN_TIME * _FPS);
		vx_2 = 3.0f * (dest->x_base_pos - x_base_pos) / (_AN_TIME * _FPS);
		vy_3 = 3.0f * (Estaca::stick_height - dest->curr_disc_column_height - moving_disc->height / 2.0f) / 
			(_AN_TIME * _FPS);

		first = 0;
	}
	
	if (finalize && moving_disc != NULL) {
		dest->push_back(*moving_disc);
		pop_back();
		moving_disc = NULL;

		moving = 0;
		first = 1;
		return true;
	}

	if (moving_disc == NULL) {
		first = true;
		return false;
	}

	if (moving_disc->y_pos > y_base_pos - Estaca::stick_height &&
		moving_disc->x_pos == x_base_pos) {

		moving_disc->y_pos -= vy_1;

	}
	else if (moving_disc->y_pos <= y_base_pos - Estaca::stick_height && moving_disc->x_pos != dest->x_base_pos) {
		
		moving_disc->x_pos += vx_2;

		if (x_base_pos < dest->x_base_pos && moving_disc->x_pos > dest->x_base_pos)
			moving_disc->x_pos = dest->x_base_pos;
		else if (x_base_pos > dest->x_base_pos && moving_disc->x_pos < dest->x_base_pos) 
			moving_disc->x_pos = dest->x_base_pos;

		moving_disc->y_pos = Elipse((dest->x_base_pos - x_base_pos) / 2.0f,
			_ARC_HEIGHT, (x_base_pos + dest->x_base_pos) / 2.0f, y_base_pos - Estaca::stick_height,
			moving_disc->x_pos);
		

	}
	else if (moving_disc->x_pos >= dest->x_base_pos) {
		
		moving_disc->y_pos += vy_3;

		if (moving_disc->y_pos >= dest->y_base_pos - dest->curr_disc_column_height - moving_disc->height / 2.0f) {
			dest->push_back(*moving_disc);
			pop_back();
			moving_disc = NULL;
			
			moving = 0;
			first = 1;
		}
	
	}

	return true;
}

unsigned short Estaca::base_pos_x()
{
	return x_base_pos;
}

unsigned short Estaca::base_pos_y()
{
	return y_base_pos;
}





