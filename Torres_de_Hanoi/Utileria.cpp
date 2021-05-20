/*****************************************************************//**
 * \file   Utileria.cpp
 * \brief  Implementaciones de Utileria.h
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/

#include "Utileria.h"

#include <string>
#include <cmath>

void initialize_al_component(bool flag, const char* comp_name) {
	if (flag) return;

	std::string except_msg("No se pudo inicializar ");
	except_msg.append(comp_name);
	
	throw std::runtime_error(except_msg.append("."));
}

float Elipse(float a, float b, float p, float q, float x) {
	float temp;

	temp = pow((x - p) / a, 2.0f);
	temp = pow(b, 2.0f) * (1.0f - temp);
	temp = -sqrt(temp) + q;

	return temp;
}
