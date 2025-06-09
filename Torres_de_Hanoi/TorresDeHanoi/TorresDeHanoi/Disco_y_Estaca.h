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

//#include "Utileria.h"

#define _MIN_DISC_CAPACITY 1 /*< Capacidad m�nima de discos para una estaca. */
#define _MAX_DISC_CAPACTITY 10 /*< Capacidad m�xima de discos para una estaca. */

#define _LARGEST_DISC_WIDTH 300 /*< Ancho del disco m�s grande para las estacas. */
#define _LARGEST_DISC_HEIGHT 100 /*< Alto del disco m�s grande para las estacas. */

#define _AN_TIME 0.5f /*< Tiempo en segundos que dura la animaci�n de movimiento de una estaca a otra. */

#define _ARC_HEIGHT 100  /*< Longitud de semieje vertical de trayectoria eliptica que sigue el disco al moverse. */

struct Disco {
	float width, height; /*< Altura y ancho del disco. */ 
	int x_pos, y_pos; /*< Coordenadas del centro del disco. */
	ALLEGRO_COLOR color; /*< Color del disco. */

	/**
	 * \brief Dibuja el disco de acuerdo a sus par�metros de posici�n, tama�o y color.
	 * 
	 */
	void draw();
};

class Estaca {
public:
	/**
	 * \brief Inicializa variables est�ticas de la clase. Se tiene que llamar a esta funci�n antes de inicializar 
	 * un objeto Estaca.
	 * 
	 * \param height Altura de los palos de cada estaca.
	 * \param max_discs M�xima cantidad de discos que una estaca puede recibir.
	 * \return True si la inicializaci�n fue exitosa. False si alg�n parametro fue invalido.
	 */
	bool static Initialize_stakes(int height, int max_discs);

	/**
	 * \brief Inicializa estaca con la posici�n desde donde se empiezan a colocar discos. 
	 * Crea un arreglo din�mico para la cantidad de discos especificada en variable est�tica max_discs.
	 * 
	 * \details	Tira excepci�n de tipo std::invalid_argument si la posici�n indicada est� fuera de la pantalla.
	 * Excepci�n de tipo std::runtime_error si no se pudo alocar memoria para los discos.
	 * Excepci�n de tipo std::logit_error si la clase no se ha inicializado con Initialize_stakes().
	 * 
	 * \param base_x_pos coordenada en x para la base.
	 * \param base_y_pos coordenada en y para la base.
	 */
	Estaca(unsigned short base_x_pos, unsigned short base_y_pos);

	/**
	 * \brief Introduce un nuevo disco en la parte superior de la estaca.
	 * 
	 * \details Cambia la posici�n del disco para quedar posicionado correctamente en la pila de discos. 
	 * 
	 * \param disc disco a introducrise.
	 * \return true si la operaci�n fue exitosa. Falso si no se pudo ingresar el disco a la estaca.
	 */
	bool push_back(const Disco& disc);

	/**
	 * \brief Obtiene disco en posici�n superior de la estaca.
	 * 
	 * \details Tira exepci�n de tipo std::logic_error si la estaca no tiene discos.
	 * 
	 * \return Referencia constante a �ltimo disco.
	 */
	const Disco& last();

	/**
	 * \brief Elimina el �ltimo disco de la estaca.
	 * 
	 * \return True si la operaci�n fue exitosa. False si la estaca estaba vac�a.
	 */
	bool pop_back();

	/**
	 * \brief Conocer si estaca est� en su capacidad m�xima.
	 * 
	 * \return True si la estaca est� llena. False si tiene espacio para m�s discos.
	 */
	bool full();

	/**
	 * \brief Imprime todos los discos que tiene la estaca, cada uno en su posici�n adecuada.
	 */
	void PrintRodDiscs(ALLEGRO_BITMAP* column_portion);

	/**
	 * \brief Inicializar estaca, llenandose hasta su capacidad m�xima con discos de color y tama�o apropiado.
	 * 
	 * \details	Si la estaca ya tiene alg�n disco, tira excepci�n de tipo std::logic_error.
	 */
	void InitDiscsAndRods();

	/**
	 * \brief Se usa para mover un disco de una estaca a otra.
	 * 
	 * \details	Cada vez que se llama a la funci�n, actualiza la posici�n del disco que en movimiento.
	 * Cuando el disco ya est� en su posici�n final, transfiere el objeto disco de una estaca a otra.
	 * El tiempo que tarda en llegar a la posici�n final depende de la constante _AN_TIME, en segundos.
	 * 
	 * \param dest Estaca destino para el disco superior de la estaca que llama a la funci�n.
	 * \param moving Si durante la funci�n se hace false, hace saber a la funci�n que llama que el movimiento
	 * ya se ha completado.
	 * \param Si finalize es true, se termine el movimiento abrubtamente y la funci�n queda en un estado
	 * v�lido para recibir la siguiente instrucci�n de traslado.
	 * \return True si el movimiento s� se puede hacer. False si el movimiento es inv�lido.
	 */
	bool move_to_stake(Estaca* dest, bool& moving, bool finalize);

	/**
	 * \brief Adquiridor de la coordenada en x de base de la estaca.
	 * 
	 * \return Coordenada en x de base de la estaca.
	 */
	unsigned short base_pos_x();

	/**
	 * \brief Adquiridor de coordenada en y de base de la estaca.
	 * 
	 * \return Coordenada en y de base de la estaca.
	 */
	unsigned short base_pos_y();

	/**
	 * \brief Destruye la estaca junto con su arreglo de discos.
	 * 
	 */
	~Estaca();

private:
	static int stick_height; 
	static int max_discs;

	unsigned short x_base_pos, y_base_pos;
	unsigned short curr_n_discs;
	unsigned int curr_disc_column_height;
	Disco* discs;
};


#endif