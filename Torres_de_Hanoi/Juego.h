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

#include "Utileria.h"


#define _MIN_DISCS 2 /*< Mínima cantidad de discos que el usuario puede elegir. */
#define _MAX_DICS 8 /*< Máxima cantidad de discos que el usuario puede elegir. */

/**
 * \brief Función principal del juego
 * 
 * \param queue cola de evento que recibe entrada de usuario.
 * \return void
 */
void Juego(ALLEGRO_EVENT_QUEUE* queue);


/**
 * \brief Imprime una estaca en una posicion y numero de discos dados
 *
 * \param queue cola de evento que recibe entrada de usuario.
 * \return void
 */
void PrintRod(double pos_x, double pos_y, int numDisks);
#endif 
