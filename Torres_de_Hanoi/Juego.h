/*****************************************************************//**
 * \file   Juego.h
 * \brief  Responsable del juego y toda sus dinámicas.
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/
#pragma once
#ifndef _JUEGO_H
#define _JUEGO_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <string>

#include "Utileria.h"

#define MAX_DISKS 7		// Maximo numero de discos en el juego.

enum {
    _ADD = 1,
    _SUBSTRACT
};

/**
 * \brief Función principal del juego
 * 
 * \param queue cola de evento que recibe entrada de usuario.
 * \return void
 */
void Juego(ALLEGRO_EVENT_QUEUE* queue);

int DiskNumber(ALLEGRO_EVENT_QUEUE* queue);

void NumberOfDisksDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, int Disks) {

    //Screen
    al_clear_to_color(al_map_rgb(3, 3, 100));
    //Title
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, _WINDOW_HEIGTH / 2, ALLEGRO_ALIGN_CENTER, "Numero de Discos: ");

    //Disk Numbers
    std::string tmp = std::to_string(Disks);
    char const* num_char = tmp.c_str();

    al_draw_filled_rectangle(_WINDOW_WIDTH / 5,  _WINDOW_HEIGTH / 9,  2 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.3));
    al_draw_text(text, al_map_rgb(255, 255, 255), 1.5 * _WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, num_char);

    //Add Button
    al_draw_filled_rectangle(_WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.3));
    //Substract Button
    al_draw_filled_rectangle(3 * _WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 4 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.5));

}

void ChangeDiskNumberDisplay(int Button) {

    switch (Button)
    {
    case _ADD:
        al_draw_filled_rectangle(_WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
        break;
    case _SUBSTRACT:
        al_draw_filled_rectangle(3 * _WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 4 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
        break;
    }

}


#endif 
