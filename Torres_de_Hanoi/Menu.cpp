/*****************************************************************//**
 * \file   Menu.cpp
 * \brief  Implementaciones de Menu.h
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/

#include "Menu.h"
#include "Instrucciones.h"
#include "Juego.h"
#include "Creditos.h"

enum {
    _PLAY = 0,
    _INSTRUCTIONS,
    _CREDITS,
    _LEAVE
};

void Menu(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display) {
    //Esta función se tiene que encargar de mostrar un menú
    //y de tomar acción cuando el usuario de una entrada.

    //Inicializar texto.
    initialize_al_component(al_init_font_addon(), "font component");
    //Inicializar ttf (True Type Font)
    initialize_al_component(al_init_ttf_addon(), "ttf font componenent");

    ALLEGRO_FONT* font_title = al_load_font("ROBOTECH_GP.ttf", 72, 0);
    ALLEGRO_FONT* font = al_load_font("ROBOTECH_GP.ttf", 36, 0);

    initialize_al_component(font, "font");
    initialize_al_component(font_title, "font titulo");
    initialize_al_component(al_init_primitives_addon(), "primitives");

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

            if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                button_place = (button_place - 1) % 4;
                if (button_place < 0)
                    button_place = _LEAVE;
            }
               
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                button_place = (button_place + 1) % 4;

            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;

            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
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
    al_clear_to_color(ColorMap(INDIGO));
    //Titulo
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, _WINDOW_HEIGTH / 9,
        ALLEGRO_ALIGN_CENTER, "TOWER OF HANOI");
    
    //Boton Jugar
    DrawButton(_WINDOW_WIDTH / 3, 3 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3,
        4 * _WINDOW_HEIGTH / 9, ColorMap(METALIC_BRONZE), text, "SALIR", al_map_rgb(255, 255, 255));
   
    //Boton Instrucciones
    DrawButton(_WINDOW_WIDTH / 3, 4.5 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3,
        5.5 * _WINDOW_HEIGTH / 9, ColorMap(METALIC_BRONZE), text, "INSTRUCTIONS", al_map_rgb(255, 255, 255));

    //Boton Creditos
    DrawButton(_WINDOW_WIDTH / 3, 6 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3,
        7 * _WINDOW_HEIGTH / 9, ColorMap(METALIC_BRONZE), text, "CREDITS", al_map_rgb(255, 255, 255));

    //Boton Salir
    DrawButton(_WINDOW_WIDTH / 3, 7.5 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3,
        8.5 * _WINDOW_HEIGTH / 9, ColorMap(METALIC_BRONZE), text, "LEAVE", al_map_rgb(255, 255, 255));
    
    al_flip_display();
}

void MoveSelection(int Button) {

    switch (Button)
    {
    case _PLAY:
        al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 3 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3, 4 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.3, 0.3, 0.3, 0.3));
        break;
    case _INSTRUCTIONS:
        al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 4.5 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3, 5.5 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.3, 0.3, 0.3, 0.3));
        break;
    case _CREDITS:
        al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 6 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3, 7 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.3, 0.3, 0.3, 0.3));
        break;
    case _LEAVE:
        al_draw_filled_rectangle(_WINDOW_WIDTH / 3, 7.5 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 3, 8.5 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.3, 0.3, 0.3, 0.3));
        break;
    }

}
