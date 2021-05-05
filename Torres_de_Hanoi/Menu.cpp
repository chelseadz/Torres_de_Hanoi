/*********************************************************************
 * \file   Menu.cpp
 * \brief  Implementaciones de Menu.h
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/

#include "Menu.h"

void Menu(ALLEGRO_EVENT_QUEUE* queue) {
    //Esta función se tiene que encargar de mostrar un menú
    //y de tomar acción cuando el usuario de una entrada.

    //Inicializar texto.
    al_init_font_addon();
    //Inicializar ttf (True Type Font)
    al_init_ttf_addon();

    ALLEGRO_FONT* font_title = al_load_ttf_font("ROBOTECH GP.ttf", 72, 0);
    ALLEGRO_FONT* font = al_load_ttf_font("ROBOTECH GP.ttf", 36, 0);

    initialize_al_component(font, "font");
    initialize_al_component(font_title, "font");
    initialize_al_component(al_init_primitives_addon(), "primitives");

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            // game logic goes here.
            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            MenuDisplay(font_title, font);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_font(font);
}

void MenuDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text) {

    //Pantalla
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //Titulo
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "TORRES DE HANOI");
    //Boton Jugar
    al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 3 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3, 4 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.5));
    al_draw_text(text, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, 3 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "JUGAR");
    //Boton Instrucciones
    al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 4.5 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3, 5.5 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.5));
    al_draw_text(text, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, 4.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "INSTRUCCIONES");
    //Boton Creditos
    al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 6 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3, 7 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.5));
    al_draw_text(text, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, 6 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "CREDITOS");
    //Boton Salir
    al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 7.5 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3, 8.5 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.5));
    al_draw_text(text, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, 7.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "SALIR");

    al_flip_display();
}
