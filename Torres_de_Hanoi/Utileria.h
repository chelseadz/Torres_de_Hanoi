/*****************************************************************//**
 * \file   Utileria.h
 * \brief  Funciones de utileria para todo el proyecto.
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/
#pragma once
#ifndef _UTILERIA_H
#define _UTILERIA_H

#include <allegro5/allegro5.h>
#include <stdexcept>

/** Colores usados para imprimir los discos y para los textos.
 */
enum Color {
	VERY_PALE_YELLOW=0,
	PALE_YELLOW,
	PALE_YELLOW_RED,
	YELLOW_RED,
	MAXIMUM_YELLOW_RED,
	ORANGE,
	BRORANGE,
	BRONZE,
	METALIC_BRONZE,
	INDIGO,
	HANBLUE,
	UNITED_NATIONS_BLUE
};

 /*< Medidas en px de la pantalla. */
enum {
	_WINDOW_HEIGTH = 684, /*< Altura de la pantalla del programa en pixeles. */
	_WINDOW_WIDTH = 1216 /*< Ancho de la pantalla del programa en pixeles. */
};

/*< Posicion inicial de la pantalla (px desde la esquina superior izquierda) en x y en y. */
enum {
	_WINDOW_POS_X = 0, /*< Posición inicial de la pantalla en x en px, iniciando del margen izuqierdo. */
	_WINDOW_POS_Y = 0 /*< Posición inicial de la pantalla en y en px, iniciando del margen superior. */
};

#define _FPS 60.0f /*< Cantidad de cuadros por segundo que se actualiza la pantalla */

 /**
  * \brief Si flag tiene un valor falso, tira un excepción de tipo std::runtime_error.
  * \details La excepción tiene el mensaje "No se pudo inicializar comp_name.".
  *
  * \param flag Si es verdaro se tira la excepción.
  *				Se usa con alguna función que regresa verdadero si se pudo inicializar el componente
  *				y falso si no lo pudo hacer.
  * \param comp_namme Nombre de lo que se está inicializando. Se incluye en el mensaje de excepción.
  * \return void
  */
void initialize_al_component(bool flag, const char* comp_name);

/**
 * \brief Coordenada en y correspondiente a parte inferior de una elipse con paramatros a, b, p y q.
 * Correspondiente a la ecuación en forma  (x-p)^2/a^2 + (y-q)^2/b^2 = 1.
 * 
 * \details Tira excepción si la x dada no está en el dominio de la función. 
 *
 * \param a semieje horizontal.
 * \param b semieje vertical.
 * \param p coordanada x de centro de la elipse.
 * \param q coordenada y de centro de la elpise.
 * \param x coordenada en x a evaluar en la ecuación.
 * 
 * \return coordenada y del punto correspondiente en el elipse inferior.
 */
float Elipse(float a, float b, float p, float q, float x);

/**
 * \brief Asigna el mapa RGB al color recibido
 * 
 * \param nombre_color Nombre del color de que se requiere el mapa
 * \return al_map_rgb() El mapa de color correspondiente
 */
ALLEGRO_COLOR MapaDeColor(Color nombre_color);

#endif
