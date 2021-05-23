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
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>

/** Colores usados para imprimir los discos y para los textos.
 */
const ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255),
	VERY_PALE_YELLOW = al_map_rgb(253, 250, 195),
	PALE_YELLOW = al_map_rgb(248, 181, 76),
	PALE_YELLOW_RED = al_map_rgb(255, 212, 87),
	YELLOW_RED = al_map_rgb(255, 200, 48),
	MAXIMUM_YELLOW_RED = al_map_rgb(193, 145, 0),
	BRORANGE = al_map_rgb(171, 125, 65),
	BRONZE = al_map_rgb(149, 104, 0),
	METALIC_BRONZE = al_map_rgb(139, 81, 33),
	ORANGE = al_map_rgb(255, 108, 0),
	YELLOW = al_map_rgb(255, 225, 0),
	RED = al_map_rgb(255, 0, 0),
	UNITED_NATIONS_BLUE = al_map_rgb(82, 158, 233),
	INDIGO = al_map_rgb(56, 109, 197),
	HANBLUE = al_map_rgb(19, 40, 107),
	BLACK = al_map_rgb(0, 0, 0);

/** Sonidos de movimiento y selección de botones */
#define _SELECT_SOUND_FILENAME "seleccionar_boton.wav"
#define _MOVE_SOUND_FILENAME "cambiar_botones.wav"

 /*< Medidas en px de la pantalla. */
enum {
	_WINDOW_HEIGHT = 684, /*< Altura de la pantalla del programa en pixeles. */
	_WINDOW_WIDTH = 1216 /*< Ancho de la pantalla del programa en pixeles. */
};

/*< Posicion inicial de la pantalla (px desde la esquina superior izquierda) en x y en y. */
enum {
	_WINDOW_POS_X = 130, /*< Posición inicial de la pantalla en x en px, iniciando del margen izuqierdo. */
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
 * \brief Dibuja un botón en pantalla 
 * 
 * \param x1 Posición x donde comienza el rectángulo
 * \param y1 Posición y donde comienza el rectángulo
 * \param x2 Posición x donde termina el rectángulo
 * \param y2 Posición y donde termina el rectángulo
 * \param button_color Color del botón
 * \param text Fuente del texto a escribir sobre el botón
 * \param string Texto que se escribe sobre el botón
 * \param text_color Color del texto que se escribe
 *
 * \return void
 */
void DrawButton(float x1, float y1, float x2, float y2, ALLEGRO_FONT* text, const char string[],
	ALLEGRO_COLOR button_color = YELLOW_RED, ALLEGRO_COLOR text_color = MAXIMUM_YELLOW_RED);

/**
 * \brief Dibuja el logo del juego en pantalla
 *
 * \param text Fuente del texto a escribir sobre el botón
 * \param x Posición x del centro del logo
 * \param y Posición y del centro logo
 *
 * \return void
 */
void DrawLogo(const ALLEGRO_FONT* font, int font_size, float x, float y);

/**
 * \brief Ordena un arreglo con algoritmo quicksort.
 *
 * \param T arr[] puntero a arreglo
 * \param int start primer índice del rango a ordenar.
 * \param int end último índice del rango a ordenar.
 * \return void
 */
template < class T>
void Quicksort(T arr[], int start, int end);

/**
 * \brief Devuelve la mediana de tres valores.
 * \details Se usa como auxiliar para escoger el pivote en el algoritmo quicksort.
 *
 * \param T i primer elemento de tipo génerico.
 * \param T j segundo elemento a considerar. De tipo genérico.
 * \param T k tercer elemento de tipo genérico a considerar.
 * \return int mediana de i, j y k.
 */
template < class T >
T Median_of_three(T i, T j, T k);

#include "Utileria.tpp"

#endif
