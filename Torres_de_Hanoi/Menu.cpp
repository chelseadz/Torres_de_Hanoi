/*****************************************************************//**
 * \file   Menu.cpp
 * \brief  Implementaciones de Menu.h
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/

#include <iostream>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Menu.h"
#include "Instrucciones.h"
#include "Juego.h"
#include "Creditos.h"


void Menu(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display) {
    //Esta función se tiene que encargar de mostrar un menú
    //y de tomar acción cuando el usuario de una entrada.

    try {
        initialize_al_component(al_init_font_addon(), "font component");
        initialize_al_component(al_init_ttf_addon(), "ttf font componenent");
        initialize_al_component(al_init_primitives_addon(), "primitives");
        initialize_al_component(al_install_audio(), "audio addon.");
        initialize_al_component(al_init_acodec_addon(), "audio codecs.");
        initialize_al_component(al_reserve_samples(8), "audio samples.");
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }

    
    ALLEGRO_FONT* font_title = al_load_font("ROBOTECH_GP.ttf", 72, 0);
    ALLEGRO_FONT* font = al_load_font("ROBOTECH_GP.ttf", 36, 0);
    ALLEGRO_SAMPLE* select_sound = al_load_sample(_SELECT_SOUND_FILENAME);
    ALLEGRO_SAMPLE* move_sound = al_load_sample(_MOVE_SOUND_FILENAME);

    try {
        initialize_al_component(font, "font");
        initialize_al_component(font_title, "font titulo");
        initialize_al_component(select_sound, "Select sound");
        initialize_al_component(move_sound, "Move sound");
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }
    

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    int button_place = _PLAY;

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            // nada por ahora.
            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;

            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
              
              al_play_sample(select_sound, 1.0f, 1.0f, 0.9f, ALLEGRO_PLAYMODE_ONCE, NULL);
              switch (button_place)
                {
                case _PLAY:
                {
                    Juego(queue, display);
                    break;
                }
                case _INSTRUCTIONS:
                {
                    Instructions(queue);
                    break;
                }
                case _CREDITS:
                {
                    Credits(queue);
                    break;
                }
                case _LEAVE:
                {
                    done = true;
                    break;
                }
                }
            }
            break;

        case ALLEGRO_EVENT_KEY_CHAR:

            al_play_sample(move_sound, 1.0f, 1.0f, 0.9f, ALLEGRO_PLAYMODE_ONCE, NULL);

            if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                button_place = (button_place - 1) % 4;
                if (button_place < 0)
                    button_place = _LEAVE;
            }
               
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                button_place = (button_place + 1) % 4;

            break;
 
           
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            MenuDisplay(font_title, font);

            MoveSelection(button_place);

            al_flip_display();

            redraw = false;
        }
    }

    //Destruir fuentes creadas
    al_destroy_font(font);
    al_destroy_font(font_title);
}

void MenuDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text) {

    //Pantalla
    al_clear_to_color(HANBLUE);
    //Titulo
    DrawLogo(title, 72, _WINDOW_WIDTH / 2, _WINDOW_HEIGHT / 9);
    
    //Boton Jugar
    DrawButton(_WINDOW_WIDTH / 3, 3 * _WINDOW_HEIGHT / 9, 2 * _WINDOW_WIDTH / 3,
        4 * _WINDOW_HEIGHT / 9, text, "PLAY");
   
    //Boton Instrucciones
    DrawButton(_WINDOW_WIDTH / 3, 4.5 * _WINDOW_HEIGHT / 9, 2 * _WINDOW_WIDTH / 3,
        5.5 * _WINDOW_HEIGHT / 9, text, "INSTRUCTIONS");

    //Boton Creditos
    DrawButton(_WINDOW_WIDTH / 3, 6 * _WINDOW_HEIGHT / 9, 2 * _WINDOW_WIDTH / 3,
        7 * _WINDOW_HEIGHT / 9, text, "CREDITS");

    //Boton Salir
    DrawButton(_WINDOW_WIDTH / 3, 7.5 * _WINDOW_HEIGHT / 9, 2 * _WINDOW_WIDTH / 3,
        8.5 * _WINDOW_HEIGHT / 9, text, "LEAVE");
    
}

void MoveSelection(int Button) {

    switch (Button)
    {
        case _PLAY:
            al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 3 * _WINDOW_HEIGHT / 9, 2 * _WINDOW_WIDTH / 3, 4 * _WINDOW_HEIGHT / 9, al_map_rgba_f(0.3, 0.3, 0.3, 0.3));
            break;
        case _INSTRUCTIONS:
            al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 4.5 * _WINDOW_HEIGHT / 9, 2 * _WINDOW_WIDTH / 3, 5.5 * _WINDOW_HEIGHT / 9, al_map_rgba_f(0.3, 0.3, 0.3, 0.3));
            break;
        case _CREDITS:
            al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 6 * _WINDOW_HEIGHT / 9, 2 * _WINDOW_WIDTH / 3, 7 * _WINDOW_HEIGHT / 9, al_map_rgba_f(0.3, 0.3, 0.3, 0.3));
            break;
        case _LEAVE:
            al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 7.5 * _WINDOW_HEIGHT / 9, 2 * _WINDOW_WIDTH / 3, 8.5 * _WINDOW_HEIGHT / 9, al_map_rgba_f(0.3, 0.3, 0.3, 0.3));
            break;
    }
}
