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

#define _AN_TIME 2.0f

int Estaca::max_discs;
int Estaca::stick_height;
int Estaca::stick_width;

bool Estaca::Initialize_stakes(int height, int width, int _max_discs) {
	if (_max_discs < 0 || _max_discs > _MAX_DISC_CAPACTITY)
		return false;

	max_discs = _max_discs;
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
	if (curr_n_discs == 0) throw std::invalid_argument("No hay discos.");
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
	if ( curr_n_discs == 0 || !dest.push_back(last())) return false;
	pop_back();

	//Calcular velocidadades en px / cuadro
	float vy_1 = 3.0f * (Estaca::stick_height - moving_disc.y_pos) / (_AN_TIME * _FPS);
	float vx_2 = 3.0f * (dest.x_base_pos - x_base_pos) / (_AN_TIME * _FPS);
	float vy_3 = 3.0f * (Estaca::stick_height - dest.last().y_pos) / (_AN_TIME * _FPS);


	ALLEGRO_EVENT event;

	bool done = false;
	bool redraw = false;

	while (!done) {
		al_wait_for_event(queue, &event);

		switch (event.type) {
			case ALLEGRO_EVENT_TIMER:

				if (moving_disc.y_pos < Estaca::stick_height &&
					moving_disc.x_pos != x_base_pos) {

					moving_disc.y_pos += vy_1;

				} else if (moving_disc.y_pos >= Estaca::stick_height && moving_disc.x_pos < dest.x_base_pos) {

					moving_disc.x_pos += vx_2;
					moving_disc.y_pos = Elipse((dest.x_base_pos - x_base_pos) / 2.0f,
						_ARC_HEIGHT, (x_base_pos + dest.x_base_pos) / 2.0f, y_base_pos + Estaca::stick_height,
						moving_disc.x_pos);

				} else if (moving_disc.x_pos >= dest.x_base_pos) {
					moving_disc.x_pos = dest.x_base_pos;
					moving_disc.y_pos -= vy_3;

					if (moving_disc.y_pos <= dest.last().y_pos)
						done = true;
				}

				redraw = true;
					
		}

		if (done) break;

		if (redraw) {
			al_draw_bitmap(backbuffer, 0, 0, 0);
			moving_disc.draw();
		}
	}

	return true;
}

 

