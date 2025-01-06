/*****************************************************************//**
 * \file   main.cpp
 * \brief  Archivo principal del proyecto.
 * 
 * \author Equipo Rocket
 * \date   29/04/2021
 *********************************************************************/

#include <iostream>
#include <allegro5/allegro5.h>

#include "Utileria.h"
#include "Menu.h"

#include "Juego.h"

int main(int argc, char** argv){

	//Inicializar componentes principal de Allegro.
	initialize_al_component(al_init(), "Allegro");

	//Inicializar teclado.
	initialize_al_component(al_install_keyboard(), "teclado");

	//Inicializar cola de eventos.
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	initialize_al_component(queue, "cola de eventos");

	//Inicializar temporizador.
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / _FPS);
	initialize_al_component(timer, "temporizador");

	//Crear pantalla.
	ALLEGRO_DISPLAY* disp = al_create_display(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	initialize_al_component(disp, "pantalla");

	//Mover pantalla a posici�n inicial.
	al_set_window_position(disp, _WINDOW_POS_X, _WINDOW_POS_Y);


	//Pedir el registro eventos relevantes en la cola de eventos.
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	//Pasar control a funci�n menu hasta que el usuario quiera salir.
	try {
		Menu(queue);
	} catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
	//Liberar variables de Allegro
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}
