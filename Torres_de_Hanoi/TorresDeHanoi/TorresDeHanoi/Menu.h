/*****************************************************************//**
 * \file   Menu.h
 * \brief  Responsable del men� principal de la aplicaci�n.
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
//#include "Utileria.h"

/**
 * \brief Opciones que hay en el men� principal.
 * 
 */
enum {
    _PLAY = 0,
    _INSTRUCTIONS,
    _CREDITS,
    _LEAVE
};

/**
 * \brief Funci�n que se encarga de mostrar el men� principal.
 * 
 * \param queue Cola de eventos principal.
 * \param display Pantalla.
 * \return void
 */
void Menu(ALLEGRO_EVENT_QUEUE* queue);

/**
 * \brief Dibuja en pantalla flechas para indicar al usuario que use sus flechsa en el teclado.
 *
 * \param x Posicion en el eje x de la pantalla.
 * \param y Posicion en el eje y de la pantalla.
 * \return void
 */
void DrawKeyArrows(float x, float y);

/**
 * \brief Muesta el titulo y los botones en pantalla.
 *
 * \param title Fuente definida para los titulos.
 * \param text Fuente definida para el texto.
 * \return void
 */
void MenuDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text);

/**
 * \brief Simula el cambio de opciones en pantalla y regresa la que se escoje.
 *
 * \param Button Bot�n en el que se encuentra actualmente.
 * \return void
 */
void MoveSelection(int Button);

#endif 
