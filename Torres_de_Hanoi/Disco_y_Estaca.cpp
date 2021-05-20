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

#define _ARC_HEIGHT 60

#define _AN_TIME 2

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
	//Elipse de abajo
	al_draw_filled_ellipse(x_pos, y_pos+height/3,  width / 2,
		- height / 3, color);
	//rectángulo del centro
	al_draw_filled_rectangle(x_pos - width / 2, y_pos, x_pos + width /2,
		y_pos + height/3, color);
	//elipse de arriba
	al_draw_filled_ellipse(x_pos, y_pos, width / 2, height / 3, 
		al_map_rgb(100, 60, 0));
}


bool Estaca::move_to_stake(Estaca& dest, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display) {
	//Guardar buffer que ya tiene lo dibujado en pantalla.
	ALLEGRO_BITMAP* backbuffer = al_get_backbuffer(display);

	Disco moving_disc = discs[curr_n_discs - 1];
	dest.push_back(last());
	pop_back();

	//Calcular velocidadades en px / cuadro
	float vy_1 = 3 * (Estaca::stick_height - moving_disc.y_pos) / (_AN_TIME * _FPS);
	float vx_2 = 3 * (dest.x_base_pos - x_base_pos) / (_AN_TIME * _FPS);
	float vy_3 = 3 * (Estaca::stick_height - dest.last().y_pos) / (_AN_TIME * _FPS);


	int n_frames = 0;

	ALLEGRO_EVENT event;

	bool done = false;
	bool redraw = false;

	while (!done) {
		al_wait_for_event(queue, &event);

		switch (event.type) {
			case ALLEGRO_EVENT_TIMER:
				++n_frames;

				//Mover en recta para salir de estaca actual.
				if (moving_disc.y_pos < Estaca::stick_height &&
					moving_disc.x_pos != x_base_pos) {
					moving_disc.y_pos += vy_1;
				} else if (moving_disc.y_pos >= Estaca::stick_height)
		}
	}

	return true;
}

 

