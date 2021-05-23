/*****************************************************************//**
 * \file   Instrucciones.h
 * \brief  Encargado de la página de instrucciones para el juego.
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/
#pragma once
#ifndef _INSTRUCCIONES_H
#define _INSTRUCCIONES_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
//#include "Utileria.h"

 /**
  * \brief Función que se encarga de mostrar las Instrucciones.
  *
  * \param queue Cola de eventos principal.
  * \return void
  */
void Instructions(ALLEGRO_EVENT_QUEUE* queue);

/**
 * \brief Muesta en pantalla el contenido de instrucciones.
 *
 * \param title Fuente definida para el título
 * \param text Fuente definida para los botones
 * \param paragraph Fuente definida para el cuerpo
 *
 * \return void
 */
void InstructionsDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph);

/**
 * \brief Simula el cambio de opciones en pantalla y regresa la que se escoje.
 *
 * \param Button Botón en el que se encuentra actualmente.
 * \return void
 */
void MoveSelection_Instructions(int Button);

/**
 * \brief Función que se encarga de mostrar el origen del juego
 *
 * \param queue Cola de eventos principal.
 * \return void
 */
void Origin(ALLEGRO_EVENT_QUEUE* queue);

/**
 * \brief Muesta en pantalla el contenido de la pestaña de Origen del juego.
 *
 * \param title Fuente definida para el título
 * \param text Fuente definida para los botones
 * \param paragraph Fuente definida para el cuerpo
 *
 * \return void
 */
void OriginDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph);

#endif
