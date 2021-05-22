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

	std::string except_msg("Wasn't able to initialize the ");
	except_msg.append(comp_name);
	
	throw std::runtime_error(except_msg.append("."));
}

float Elipse(float a, float b, float p, float q, float x) {
	float temp;

	temp = pow((x - p) / a, 2.0f);

	if (temp > 1) throw std::invalid_argument("x no est\240 dentro del rango de la elipse.");

	temp = pow(b, 2.0f) * (1.0f - temp);
	temp = -sqrt(temp) + q;

	return temp;
}

void DrawButton(float x1, float y1, float x2, float y2, ALLEGRO_FONT* text, const char string[], 
	ALLEGRO_COLOR button_color, ALLEGRO_COLOR text_color){
	al_draw_filled_rectangle(x1 + 10, y1 - 10, x2 + 10, y2 - 10, text_color);
	al_draw_filled_triangle(x1 + 10, y1 - 10, x1, y1, x1 + 10, y1, text_color);
	al_draw_filled_triangle(x2 + 10, y2 - 10, x2, y2, x2, y2 - 10, text_color);
	al_draw_filled_rectangle(x1, y1, x2, y2, button_color);
	al_draw_text(text, text_color, (x2 + x1)/2, 0.8*y1 + 0.2*y2, ALLEGRO_ALIGN_CENTER, string);
}

void DrawLogo(const ALLEGRO_FONT* font, int font_size, float x, float y) {
	al_draw_text(font, BLACK, x + 0.14 * font_size, y, ALLEGRO_ALIGN_CENTER, "TOWER OF HANOI");
	al_draw_text(font, INDIGO, x + 0.08 * font_size, y, ALLEGRO_ALIGN_CENTER, "TOWER OF HANOI");
	al_draw_text(font, WHITE, x, y, ALLEGRO_ALIGN_CENTER, "TOWER OF HANOI");
}
