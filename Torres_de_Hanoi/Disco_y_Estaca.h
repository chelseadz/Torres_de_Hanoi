/*****************************************************************//**
 * \file   Disco_y_Estaca.h
 * \brief  Clase para un disco y estructura para una estaca.
 * 
 * \author Equipo Rocket
 * \date   19/05/2021
 *********************************************************************/
#pragma once
#ifndef _DISCO_Y_ESTACA_H
#define _DISCO_Y_ESTACA_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>

#include "Utileria.h"

#define _MIN_DISC_CAPACITY 1 /*< Capacidad mínima de discos para una estaca. */
#define _MAX_DISC_CAPACTITY 10 /*< Capacidad máxima de discos para una estaca. */

#define _LARGEST_DISC_WIDTH 300 /*< Ancho del disco más grande para las estacas. */
#define _LARGEST_DISC_HEIGTH 100 /*< Alto del disco más grande para las estacas. */

#define _AN_TIME 0.5f /*< Tiempo en segundos que dura la animación de movimiento de una estaca a otra. */

#define _ARC_HEIGHT 100  /*< Longitud de semieje vertical de trayectoria eliptica que sigue el disco al moverse. */

struct Disco {
	float width, height; /*< Altura y ancho del disco. */ 
	int x_pos, y_pos; /*< Coordenadas del centro del disco. */
	ALLEGRO_COLOR color; /*< Color del disco. */

	/**
	 * \brief Dibuja el disco de acuerdo a sus parámetros de posición, tamaño y color.
	 * 
	 */
	void draw();
};

class Estaca {
public:
	/**
	 * \brief Inicializa variables estáticas de la clase. Se tiene que llamar a esta función antes de inicializar 
	 * un objeto Estaca.
	 * 
	 * \param height Altura de los palos de cada estaca.
	 * \param width Ancho de los palos de cada estaca.
	 * \param max_discs Máxima cantidad de discos que una estaca puede recibir.
	 * \return True si la inicialización fue exitosa. False si algún parametro fue invalido.
	 */
	bool static Initialize_stakes(int height, int width, int max_discs);

	/**
	 * \brief Inicializa estaca con la posición desde donde se empiezan a colocar discos. 
	 * Crea un arreglo dinámico para la cantidad de discos especificada en variable estática max_discs.
	 * 
	 * \details	Tira excepción de tipo std::invalid_argument si la posición indicada está fuera de la pantalla.
	 * Excepción de tipo std::runtime_error si no se pudo alocar memoria para los discos.
	 * Excepción de tipo std::logit_error si la clase no se ha inicializado con Initialize_stakes().
	 * 
	 * \param base_x_pos coordenada en x para la base.
	 * \param base_y_pos coordenada en y para la base.
	 */
	Estaca(unsigned short base_x_pos, unsigned short base_y_pos);

	/**
	 * \brief Introduce un nuevo disco en la parte superior de la estaca.
	 * 
	 * \details Cambia la posición del disco para quedar posicionado correctamente en la pila de discos. 
	 * 
	 * \param disc disco a introducrise.
	 * \return true si la operación fue exitosa. Falso si no se pudo ingresar el disco a la estaca.
	 */
	bool push_back(const Disco& disc);

	/**
	 * \brief Obtiene disco en posición superior de la estaca.
	 * 
	 * \details Tira exepción de tipo std::logic_error si la estaca no tiene discos.
	 * 
	 * \return Referencia constante a último disco.
	 */
	const Disco& last();

	/**
	 * \brief Elimina el último disco de la estaca.
	 * 
	 * \return True si la operación fue exitosa. False si la estaca estaba vacía.
	 */
	bool pop_back();

	/**
	 * \brief Conocer si estaca está en su capacidad máxima.
	 * 
	 * \return True si la estaca está llena. False si tiene espacio para más discos.
	 */
	bool full();

	/**
	 * \brief Imprime todos los discos que tiene la estaca, cada uno en su posición adecuada.
	 */
	void PrintRodDiscs();

	/**
	 * \brief Inicializar estaca, llenandose hasta su capacidad máxima con discos de color y tamaño apropiado.
	 * 
	 * \details	Si la estaca ya tiene algún disco, tira excepción de tipo std::logic_error.
	 */
	void InitDiscsAndRods();

	/**
	 * \brief Se usa para mover un disco de una estaca a otra.
	 * 
	 * \details	Cada vez que se llama a la función, actualiza la posición del disco que en movimiento.
	 * Cuando el disco ya está en su posición final, transfiere el objeto disco de una estaca a otra.
	 * El tiempo que tarda en llegar a la posición final depende de la constante _AN_TIME, en segundos.
	 * 
	 * \param dest Estaca destino para el disco superior de la estaca que llama a la función.
	 * \param moving Si durante la función se hace false, hace saber a la función que llama que el movimiento
	 * ya se ha completado.
	 * \return True si el movimiento sí se puede hacer. False si el movimiento es inválido.
	 */
	bool move_to_stake(Estaca& dest, bool& moving);

	/**
	 * \brief Destruye la estaca junto con su arreglo de discos.
	 * 
	 */
	~Estaca();

private:
	static int stick_height; 
	static int stick_width;
	static int max_discs;

	unsigned short x_base_pos, y_base_pos;
	unsigned short curr_n_discs;
	unsigned int curr_disc_column_height;
	Disco* discs;
};


#endif