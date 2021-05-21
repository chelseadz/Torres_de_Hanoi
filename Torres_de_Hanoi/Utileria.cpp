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

ALLEGRO_COLOR MapaDeColor (int nombre_color){
	
	switch (nombre_color)
	{
		case VERY_PALE_YELLOW:
			return al_map_rgb(253, 250, 195);

		case PALE_YELLOW:
			return al_map_rgb(252, 233, 165);

		case PALE_YELLOW_RED:
			return al_map_rgb(251, 216, 136);

		case YELLOW_RED:
			return al_map_rgb(249, 198, 106);

		case MAXIMUM_YELLOW_RED:
			return al_map_rgb(248, 181, 76);

		case ORANGE:
			return al_map_rgb(229, 167, 73);

		case BRORANGE:
			return al_map_rgb(210, 153, 71);

		case BRONZE:
			return al_map_rgb(190, 139, 68);

		case METALIC_BRONZE: 
			return al_map_rgb(171, 125, 65);

		case INDIGO:
			return al_map_rgb(56, 112, 189);

		case HANBLUE:
			return al_map_rgb(56, 112, 189);

		case UNITED_NATIONS_BLUE:
			return al_map_rgb(82, 158, 233);

		default:
			return al_map_rgb(255, 255, 255);
	}
}

void DrawButton(float x1, float y1, float x2, float y2, ALLEGRO_COLOR button_color, ALLEGRO_FONT* text, const char string[], ALLEGRO_COLOR text_color){
	al_draw_filled_rectangle(x1, y1, x2, y2, button_color);
	al_draw_text(text, text_color, (x2 + x1)/2, (y2 + y1)/2, ALLEGRO_ALIGN_CENTER, string);
}
