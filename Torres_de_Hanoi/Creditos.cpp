/*****************************************************************//**
 * \file   Creditos.cpp
 * \brief  Implementaciones de Creditos.h
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/

#include "Creditos.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Utileria.h"


void Credits(ALLEGRO_EVENT_QUEUE* queue) {


    ALLEGRO_FONT* font_title = al_load_font("ROBOTECH_GP.ttf", 48, 0);
    ALLEGRO_FONT* font = al_load_font("ROBOTECH_GP.ttf", 36, 0);
    ALLEGRO_FONT* font_paragraph = al_load_font("HelveticaLTStdLight.ttf", 22, 0);

    initialize_al_component(font, "font");
    initialize_al_component(font_title, "font titulo");
    initialize_al_component(font_paragraph, "font parrafo");

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:

                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    done = true;

                if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER) done = true;
            
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                exit(0);
                break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            CreditsDisplay(font_title, font, font_paragraph);

            al_flip_display();

            redraw = false;
        }
    }

    //Destruir fuentes creadas
    al_destroy_font(font);
    al_destroy_font(font_title);
    al_destroy_font(font_paragraph);
}

void CreditsDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph) {

    //Pantalla
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //Titulo Créditos
    al_draw_text(title, ColorMap(INDIGO), _WINDOW_WIDTH / 2, 0.7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "Credits");
    //Cuerpo Créditos
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 1.4 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Final project made by the Team Rocket for the subject computer programming taught ");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 1.9 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "by the teacher Irene Rodriguez from the Universidad de Sonora.");
    al_draw_text(title, ColorMap(INDIGO), _WINDOW_WIDTH / 9, 2.4 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Members of the team: ");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 3.1 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Chelsea Durazo Duarte");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 3.6 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Enrique Alejandro Giottonini Herrera");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 4.1 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Diego Torres Gonzales");

    //BOTON REGRESAR
    DrawButton(_WINDOW_WIDTH / 5, 7.5 * _WINDOW_HEIGTH / 9, 4 * _WINDOW_WIDTH / 5,
        8.5 * _WINDOW_HEIGTH / 9, ColorMap(METALIC_BRONZE),
        text, "Press ESC, SPACE or ENTER to go back.", al_map_rgb(255, 255, 255));
}

