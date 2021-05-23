/*****************************************************************//**
 * \file   Creditos.h
 * \brief  Encargado de página de creditos.
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/
#pragma once
#ifndef _CREDITOS_H
#define _CREDITOS_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Utileria.h"

 /**
  * \brief Función que se encarga de mostrar los ccréditos
  *
  * \param queue Cola de eventos principal.
  * \return void
  */
void Credits(ALLEGRO_EVENT_QUEUE* queue);

/**
 * \brief Muesta el texto de créditos en pantalla
 *
 * \param title Fuente definida para el título
 * \param text Fuente definida para los botones
 * \param paragraph Fuente definida para el cuerpo
 * 
 * \return void
 */
void CreditsDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph);

#endif 
