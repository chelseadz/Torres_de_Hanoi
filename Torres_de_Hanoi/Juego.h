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


#define _MIN_DISCS 2 /*< Mínima cantidad de discos que el usuario puede elegir. */
#define _MAX_DICS 8 /*< Máxima cantidad de discos que el usuario puede elegir. */

constexpr auto MAX_DISKS = 7;		// Maximo numero de discos en el juego.;

/**
 * Opciones de seleccion
 */
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
void Juego(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display);

/**
 * \brief Captura el numero de discos iniciales
 *
 * \param queue cola de evento que recibe entrada de usuario.
 * \return numero de discos
 */
int DiskNumber(ALLEGRO_EVENT_QUEUE* queue);

/**
 * \brief Muestra en pantalla el numero de discos que es estan capturando
 *
 * \param queue cola de evento que recibe entrada de usuario.
 * \return nada
 */
void NumberOfDisksDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, int Disks);

/**
 * \brief Cambia el numero de discos en pantalla
 *
 * \param queue cola de evento que recibe entrada de usuario.
 * \return nada
 */

void ChangeDiskNumberDisplay(int Button);

#endif 
