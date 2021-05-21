/*****************************************************************//**
 * \file   Menu.h
 * \brief  Responsable del menú principal de la aplicación.
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/
#pragma once
#ifndef _MENU_H
#define _MENU_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Utileria.h"

/**
 * \brief Función que se encarga de mostrar el menú principal
 * 
 * \param queue Cola de eventos principal.
 * \return void
 */
void Menu(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display);

/**
 * \brief Muesta el titulo y los botones en pantalla
 *
 * \param 
 * \return void
 */
void MenuDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text);

void MoveSelection(int Button);





#endif 
