/*****************************************************************//**
 * \file   Selector_flecha.cpp
 * \brief  Implementación de funciones para "Selector_flecha.h".
 * 
 * \author Equipo Rocket
 * \date   21/05/2021
 *********************************************************************/

#include "Selector_flecha.h"

#include "Utileria.h"

float Arrow_selector::y_pos;

Estaca* Arrow_selector::available_stakes[_N_STAKES];

Arrow_selector::Arrow_selector(int selected_stake, bool show /*= 1 */) : selected_stake(selected_stake) {
	this->show = show;
}

void Arrow_selector::Set_y_pos(float y)
{
	y_pos = y;

}

void Arrow_selector::Set_available_stakes(Estaca* left, Estaca* middle, Estaca* right)
{
	available_stakes[0] = left;
	available_stakes[1] = middle;
	available_stakes[2] = right;
}

Estaca* Arrow_selector::pointee()
{
	return available_stakes[selected_stake];
}

void Arrow_selector::move_right() {
	selected_stake = (selected_stake + 1) % _N_STAKES;
}

void Arrow_selector::move_left() {
	--selected_stake;
	if (selected_stake < _LEFT_S) selected_stake = _RIGTH_S;
}

void Arrow_selector::draw() {
	if (show && selected_stake != _NULL_SELECTION) {

		int x_pos = available_stakes[selected_stake]->base_pos_x();

		ALLEGRO_COLOR color = ((selected) ? _SELECTED_COLOR : _NORMAL_COLOR);

		al_draw_filled_triangle(x_pos - _ARROW_WIDTH / 2.0f, y_pos - _ARROW_HEIGTH / 2.0f,
			x_pos + _ARROW_WIDTH / 2.0f, y_pos - _ARROW_HEIGTH / 2.0,
			x_pos, y_pos + _ARROW_HEIGTH / 2.0f, color);
	}

}
