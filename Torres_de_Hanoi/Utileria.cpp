/*****************************************************************//**
 * \file   Utileria.cpp
 * \brief  Implementaciones de Utileria.h
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/

#include "Utileria.h"

#include <string>

void initialize_al_component(bool flag, const char* comp_name) {
	if (flag) return;

	std::string except_msg("No se pudo inicializar ");
	except_msg.append(comp_name);
	
	throw std::runtime_error(except_msg.append("."));
}
