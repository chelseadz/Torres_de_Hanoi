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
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>

#include "Utileria.h"
#include "Disco_y_Estaca.h"


#define _MIN_DISCS 2 /*< Mínima cantidad de discos que el usuario puede elegir. */
#define _MAX_DISCS 8 /*< Máxima cantidad de discos que el usuario puede elegir. */

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
int DiskNumber(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_SAMPLE* move, ALLEGRO_SAMPLE* select);

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
int MinNMoves(int n_discs);

/**
 * \brief Dibuja el número de movimientos que el jugador ha hecho.
 *
 * \details Si la fuente que se le pasa a la función no está inicializada correctamente,
 * la función solo imprime un mensaje de error en el flujo de errores std::cerr de la consola.
 *
 * \param n_moves Número de movimientos que el jugador ha hecho.
 * \param font fuente con la que se imprime el texto del mensaje.
 * \return void
 */
void DisplayNMoves(unsigned n_moves, ALLEGRO_FONT* font);

/**
 * \brief Dibuja el número de movimientos minimos para ganar.
 *
 * \details Si la fuente que se le pasa a la función no está inicializada correctamente,
 * la función solo imprime un mensaje de error en el flujo de errores std::cerr de la consola.
 *
 * \param n_moves Número de discos.
 * \param font fuente con la que se imprime el texto del mensaje.
 * \return void
 */
void DisplayMinMoves(unsigned numDiscs, ALLEGRO_FONT* font);

void Ending(ALLEGRO_EVENT_QUEUE* queue, int moves, int min_moves);

void EndingDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph, int moves, int min_moves);



#endif 
