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
#include "Utileria.h"

 /**
  * \brief Función que se encarga de mostrar las Instrucciones
  *
  * \param queue Cola de eventos principal.
  * \return void
  */
void Instrucciones(ALLEGRO_EVENT_QUEUE* queue);

/**
 * \brief Muesta el titulo y los botones en pantalla
 *
 * \param
 * \return void
 */
void InstruccionesDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph);

void MoverSeleccion_Instrucciones(int Button);

/**
 * \brief Función que se encarga de mostrar el origen del juego
 *
 * \param queue Cola de eventos principal.
 * \return void
 */
void Origen(ALLEGRO_EVENT_QUEUE* queue);

void OrigenDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph);


void Acertijo(ALLEGRO_EVENT_QUEUE* queue);

void AcertijoDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph);

#endif
