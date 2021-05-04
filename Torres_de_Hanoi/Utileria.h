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

#include <stdexcept>

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

#endif
