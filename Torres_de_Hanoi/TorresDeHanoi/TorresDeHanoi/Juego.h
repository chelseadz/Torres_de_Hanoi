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
#include <utility>

#include "Scores.h"


#define _MIN_DISCS 2 /*< Mínima cantidad de discos que el usuario puede elegir. */
#define _MAX_DISCS 8 /*< Máxima cantidad de discos que el usuario puede elegir. */

/**
 * Opciones de seleccion de la flecha que incrementa o disminuye el numero de discos para jugar.
 */
enum {
    _ADD = 1,
    _SUBSTRACT
};


/**
 * \brief Función principal del juego
 * 
 * \param queue Cola de evento que recibe entrada de usuario.
 * \param display Pantalla
 * \return void
 */
void Juego(ALLEGRO_EVENT_QUEUE* queue);

/**
 * \brief Captura el numero de discos iniciales
 *
 * \param queue cola de evento que recibe entrada de usuario.
 * \return numero de discos
 */
int DiskNumber(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_SAMPLE* move, 
    ALLEGRO_SAMPLE* select, ALLEGRO_SAMPLE* error_sound);

/**
 * \brief Muestra en pantalla el numero de discos que se estan capturando para jugar.
 *
 * \param queue cola de evento que recibe entrada de usuario.
 * \param title Fuente definida para los titulos
 * \param text Fuente definida para los textos
 * \param Disks Numero de discos actual.
 * 
 * \return nada
 */
void NumberOfDisksDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, int Disks);

/**
 * \brief Cambia el numero de discos en pantalla
 *
 * \param Button Botón donde se encuentra actualmente.
 * 
 * \return nada
 */

void ChangeDiskNumberDisplay(int Button);

/**
 * \brief Mínimo número de movimientos para resolver el juego con n_discs discos.
 *
 * \details Si n_discs es negativo, tira excepción de tipo std::invalid_argument.
 *
 * \param n_discs cantidad de discos en el juego.
 * 
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
 * 
 * \return void
 */
void DisplayNMoves(unsigned n_moves, ALLEGRO_FONT* font);

/**
 * \brief Dibuja el número de movimientos minimos para ganar.
 *
 * \details Si la fuente que se le pasa a la función no está inicializada correctamente,
 * la función solo imprime un mensaje de error en el flujo de errores std::cerr de la consola.
 *
 * \param n_moves Número de discos en el juego.
 * \param font fuente con la que se imprime el texto del mensaje.
 * 
 * \return void
 */
void DisplayMinMoves(unsigned numDiscs, ALLEGRO_FONT* font);

/**
 * \brief Gestiona los movimientos del usuario si pulsa ESC para salir.
 * 
 * \param queue Cola de eventos.
 * \param font fuente con la que se imprime el texto.
 * \param move_sound Sonido de movimiento ente botones.
 * 
 * \return void
 */
bool EscapeGame(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE* move_sound);

/**
 * \brief Imprime lo que se ve en la pantalla de ESCAPE.
 * 
 * \param font fuente con la que se imprime el texto.
 * 
 * \return void
 */
void DisplayEscapeGame( ALLEGRO_FONT* font);

/**
 * \brief Finaliza el juego.
 *
 * \param queue Cola de evento que recibe entrada de usuario.
 * \param moves Movimientos en los que se terminó el juego.
 * \param min_moves Cantidad minima para ganar el juego.
 * \return void
 */
void Ending(ALLEGRO_EVENT_QUEUE* queue, int moves, int min_moves, int discs);

/**
 * \brief Muestra en pantalla el fin del juego.
 *
 * \param queue cola de evento que recibe entrada de usuario.
 * \param title Fuente definida para los titulos
 * \param text Fuente definida para los textos
 * \param moves Movimientos en los que se terminó el juego.
 * \param min_moves Cantidad minima para ganar el juego.
 * \return nada
 */
void EndingDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph, int moves, int min_moves);

void DisplayHighScores(ALLEGRO_FONT* header, ALLEGRO_FONT* text, Score* scores, int n_scores);

Score* GetHighScores(int n_discs, int& n_scores);

std::string MoveSequenceGenerator(int n_discs, char start, char target);

#endif 
