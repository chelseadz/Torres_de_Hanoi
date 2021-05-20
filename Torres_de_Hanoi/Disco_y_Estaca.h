/*****************************************************************//**
 * \file   Disco_y_Estaca.h
 * \brief  Clase para un disco y estructura para una estaca.
 * 
 * \author Equipo Rocket
 * \date   19/05/2021
 *********************************************************************/
#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>

#include "Utileria.h"

#define _MIN_DISC_CAPACITY 1
#define _MAX_DISC_CAPACTITY 10


struct Disco {
	double width, height; //Altura y ancho del disco.
	int x_pos, y_pos; //Coordenadas del centro del disco.
	ALLEGRO_COLOR color; //Color del disco.


	void draw();
};

class Estaca {
public:
	bool static Initialize_stakes(int height, int width, int max_discs);

	Estaca(unsigned short base_x_pos, unsigned short base_y_pos);

	bool push_back(const Disco& disc);

	const Disco& last();

	bool pop_back();

	bool full();


	void PrintRod();

	void InitDiscsAndRods();

	bool move_to_stake(Estaca& dest, bool& moving);


	~Estaca();

private:
	static int stick_height; 
	static int stick_width;
	static int max_discs;

	unsigned short x_base_pos, y_base_pos;
	unsigned short curr_n_discs;
	unsigned int curr_disc_column_height;
	Disco* discs;
};
