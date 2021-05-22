/*****************************************************************//**
 * \file   Selector_flecha.h
 * \brief  Estructura de una flecha que el usuario usa para seleccionar estacas.
 * 
 * \author Equipo Rocket
 * \date   21/05/2021
 *********************************************************************/
#pragma once
#ifndef _SELECTOR_FLECHA_H
#define _SELECTOR_FLECHA_H

#include "Disco_y_Estaca.h"

#include <climits>

#define _ARROW_WIDTH 40
#define _ARROW_HEIGTH 35

#define _N_STAKES 3

#define _NORMAL_COLOR YELLOW_RED
#define _SELECTED_COLOR ORANGE

#define _NULL_SELECTION SHRT_MAX

/**
 * \brief Opciones que puede tomar variable selected_stake.
 */
enum {
	_LEFT_S, /*< Estaca izquierda. */
	_MIDDLE_S, /*< Estaca central. */
	_RIGHT_S /*< Estaca derecha. */
};

struct Arrow_selector {
	static float y_pos;
	static Estaca* available_stakes[_N_STAKES];

	short selected_stake = _NULL_SELECTION;
	bool show;
	bool selected = 0;



	/**
	 * \brief Constructor de objeto.
	 * 
	 * \param pointee Estaca a la que apunta la flecha.
	 * \param show = 1 Si se tiene que mostrar la flecha o no.
	 */
	Arrow_selector(int selected_stake, bool show = 1);

	/**
	 * \brief Inicializa posición en y de centro para cada flecha.
	 * 
	 * \param y posición en y.
	 */
	static void Set_y_pos(float y);

	/**
	 * \brief Guarda las direcciones de las estacas para poder mover la flecha hacia ella cuando se pida.
	 * 
	 * \param left Estaca que se encuentra hasta la izquierda.
	 * \param middle Estaca que se encuentra en el centro.
	 * \param right Estaca que se encuentra a la derecha.
	 */
	static void Set_available_stakes(Estaca* left, Estaca* middle, Estaca* right);

	/**
	 * \brief Puntero a estaca a la cual está apuntando la flecha.
	 * 
	 * \return Puntero a estaca apuntada por la flecha.
	 */
	Estaca* pointee();

	/**
	 * \brief Hace que la flecha apunte a la flecha vecina derecha actual.
	 * 
	 * \details Si la flecha apunta a la estaca derecha,
	 *  después de movimiento va a apuntar a la estaca izquierda.
	 * 
	 */
	void move_right();

	/**
	 * \brief Hace que la flecha apunte a la flecha vecina derecha actual.
	 * 
	 * \details Si la flecha apunta a la estaca izquierda,
	 *  después de movimiento va a apuntar a la estaca derecha.
	 * 
	 */
	void move_left();
	
	/**
	 * \brief Dibuja la flecha si la variable show es true.
	 * 
	 */
	void draw();
};


#endif
