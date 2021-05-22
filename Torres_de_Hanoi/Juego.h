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
#include "Disco_y_Estaca.h"


#define _MIN_DISCS 2 /*< Mínima cantidad de discos que el usuario puede elegir. */
#define _MAX_DISCS 8 /*< Máxima cantidad de discos que el usuario puede elegir. */

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

/**
 * \brief Mínimo número de movimientos para resolver el juego con n_discs discos.
 *
 * \details Si n_discs es negativo, tira excepción de tipo std::invalid_argument.
 *
 * \param n_discs cantidad de discos en el juego.
 * \return Número mínimo de movimientos.
 */
int Min_n_moves(int n_discs);


///**
// * \brief Captura de que estaca se movera el disco
// *
// * \param queue cola de evento que recibe entrada de usuario.
// * \return Entero que representa la estaca origen
// */
//
//int What_to_Move(ALLEGRO_EVENT_QUEUE* queue, Estaca &init, Estaca &aux, Estaca &fin);
//
///**
// * \brief Muestra una flecha en la posicion de la estaca de la cual se movera el disco
// *
// * \param queue cola de evento que recibe entrada de usuario y  las referencias a las estacas para imprimiras en pantalla.
// * \return void
// */
//void What_to_Move_Display(int Button);
//
///**
// * \brief Captura a que estaca se movera el disco
// *
// * \param queue cola de evento que recibe entrada de usuario.
// * \return Entero que representa la estaca origen
// */
//
//int Where_to_Move(ALLEGRO_EVENT_QUEUE* queue, int Origin, Estaca& init, Estaca& aux, Estaca& fin);
//
///**
// * \brief Muestra una flecha de donde viene el disco y a donde va
// *
// * \param queue cola de evento que recibe entrada de usuario  y  las referencias a las estacas para imprimiras en pantalla.
// * \return void
// */
//void Where_to_Move_Display(int Origin, int Dest);



#endif 
