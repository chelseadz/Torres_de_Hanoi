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

    //Inicializar tipo de letra.
    ALLEGRO_FONT* font = al_create_builtin_font();
    initialize_al_component(font, "font");

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
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");

            al_draw_filled_triangle(35, 350, 85, 375, 35, 400, al_map_rgb_f(0, 1, 0));
            al_draw_filled_rectangle(240, 260, 340, 340, al_map_rgba_f(0, 0, 0.5, 0.5));
            al_draw_circle(450, 370, 30, al_map_rgb_f(1, 0, 1), 2);
            al_draw_line(440, 110, 460, 210, al_map_rgb_f(1, 0, 0), 1);
            al_draw_line(500, 220, 570, 200, al_map_rgb_f(1, 1, 0), 1);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_font(font);
}
