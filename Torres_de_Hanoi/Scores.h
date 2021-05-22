/*****************************************************************//**
 * \file   Scores.h
 * \brief  Implementa estructura para guardar y leer puntaje de un jugador.
 * 
 * \author Equipo Rocket
 * \date   22/05/2021
 *********************************************************************/
#pragma once
#ifndef _SCORES_H
#define _SCORES_H

#include "Utileria.h"

#define _MAX_NAME_CHARS 15

struct Score {
	short moves;
	char name[_MAX_NAME_CHARS];

	bool operator < (const Score& s);
};

/**
 * \brief Regresa un puntero en el heap apuntando a un arreglo con los puntajes.
 * 
 * \details El formato del archivo con los puntajes tiene que ser el siguiente:
 *				n \\Número de puntajes en el archivo.
 *				Chelsea 15
 *				Enrique 15
 *				Diego 14
 *			Los puntajes no necesariamente tienen que estar ordenados de antemano.
 *			Los nombres de jugador tienen que ser una sola palabra.
 * 
 * \param filename nombre del archivo donde están guardados los puntajes.
 * \return Puntero a arreglo de Score en el heap ordenado de menor a mayor.
 *		   Regresa NULL si hubo algún problema para hacer al lectura.
 */
Score* GetPreviousScores(const char* filename);


#endif
