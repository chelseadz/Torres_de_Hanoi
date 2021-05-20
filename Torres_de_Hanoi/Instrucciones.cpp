/*****************************************************************//**
 * \file   Instrucciones.cpp
 * \brief  Implementaciones de Instrucciones.h
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/

#include "Instrucciones.h"

enum {
    _REGRESAR = 0,
    _ORIGEN = 1,
    _ACERTIJO = 1
};

void Instrucciones(ALLEGRO_EVENT_QUEUE* queue) {


    ALLEGRO_FONT* font_title = al_load_font("Starjedi.ttf", 48, 0);
    ALLEGRO_FONT* font = al_load_font("Starjedi.ttf", 36, 0);
    ALLEGRO_FONT* font_paragraph = al_load_font("Starjedi.ttf", 24, 0);

    initialize_al_component(font, "font");
    initialize_al_component(font_title, "font titulo");
    initialize_al_component(font_paragraph, "font parrafo");

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    int button_place = _REGRESAR;

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
            
            if (event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                button_place = (button_place - 1) % 2;
                if (button_place < 0)
                    button_place = _ORIGEN;
            }

            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                button_place = (button_place + 1) % 2;

            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;

            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                switch (button_place){
                    case _REGRESAR:
                        done = true;
                        break;

                    case _ORIGEN:
                        OriginOfTheGame(queue);
                        break;
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
            InstruccionesDisplay(font_title, font, font_paragraph);

            MoverSeleccion_Instrucciones(button_place);

            al_flip_display();

            redraw = false;
        }
    }

    //Destruir fuentes creadas
    al_destroy_font(font);
    al_destroy_font(font_title);
    al_destroy_font(font_paragraph);
}

void InstruccionesDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph) {

    //Pantalla
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //Titulo Instrucciones
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "INSTRUCCIONES");
    //Cuerpo instrucciones
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Descripci\242n: Las Torres de Han\242i es un rompecabezas o juego matem\240tico inventado en 1883");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "por el matem\240tico franc\202s \202douard Lucas. Este juego consiste en un número de discos perforados");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "de radio creciente que se apilan insert\240ndose en uno de los tres postes fijados a un tablero. ");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "El objetivo del juego es trasladar la pila de discos a otro de los postes. ");

    //Titulo Reglas
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "REGLAS");
    //Cuerpo reglas
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "1. No se puede colocar un disco más grande encima de un disco más pequeño.");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "2. El juego se gana cuando logras insertar todos los discos apilados de mayor a menor en el poste del");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "extremo derecho. ");

    //Titulo Controles
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "Controles");
    //Cuerpo controles
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Usa ESPACIO o ENTER para seleccionar el disco.");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Usa las flechas para mover el disco o navegar en el juego.");
   
    //Boton Regresar
    al_draw_filled_rectangle(_WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.3));
    al_draw_text(text, al_map_rgb(255, 255, 255), 1.5* _WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "REGRESAR");
    //Boton Origen
    al_draw_filled_rectangle(3*_WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 4 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.5));
    al_draw_text(text, al_map_rgb(255, 255, 255), 3.5 * _WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "ORIGEN");

}

void MoverSeleccion_Instrucciones(int Button) {

    switch (Button)
    {
        case _REGRESAR:
            al_draw_filled_rectangle(_WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
            break;
        case _ORIGEN:
            al_draw_filled_rectangle(3 * _WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 4 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
            break;
    }
}

// Inicia la pantalla que muestra el origen del juego, muestra el botón para volver a 
// instrucciones o para ir a la solución del acertijo
void OriginOfTheGame(ALLEGRO_EVENT_QUEUE* queue){

    ALLEGRO_FONT* font_title = al_load_font("Starjedi.ttf", 48, 0);
    ALLEGRO_FONT* font = al_load_font("Starjedi.ttf", 36, 0);
    ALLEGRO_FONT* font_paragraph = al_load_font("Starjedi.ttf", 24, 0);

    initialize_al_component(font, "font");
    initialize_al_component(font_title, "font titulo");
    initialize_al_component(font_paragraph, "font parrafo");

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    int button_place = _REGRESAR;

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

                if (event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    button_place = (button_place - 1) % 2;
                    if (button_place < 0)
                        button_place = _ACERTIJO;
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                    button_place = (button_place + 1) % 2;

                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    done = true;

                if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    switch (button_place) {
                        case _REGRESAR:
                            done = true;
                            break;

                        case _ACERTIJO:
                            OriginOfTheGame(queue);
                            break;
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
            OriginOfTheGameDisplay(font_title, font, font_paragraph);

            MoverSeleccion_Instrucciones(button_place);

            al_flip_display();

            redraw = false;
        }
    }
    //Destruir fuentes creadas
    al_destroy_font(font);
    al_destroy_font(font_title);
    al_destroy_font(font_paragraph);

}

void OriginOfTheGameDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph) {

    //Pantalla
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //Titulo
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "Origen del Juego");
    //Cuerpo
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Descripci\242n: Las Torres de Han\242i es un rompecabezas o juego matem\240tico inventado en 1883");


    //Boton Regresar
    al_draw_filled_rectangle(_WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.3));
    al_draw_text(text, al_map_rgb(255, 255, 255), 1.5 * _WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "REGRESAR");
    //Boton Origen
    al_draw_filled_rectangle(3 * _WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 4 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.5));
    al_draw_text(text, al_map_rgb(255, 255, 255), 3.5 * _WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "ORIGEN");

}

void MoveSelection_OriginOfTheGame(int Button) {

    switch (Button){
        case _REGRESAR:
            al_draw_filled_rectangle(_WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
            break;
        case _ACERTIJO:
            al_draw_filled_rectangle(3 * _WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGTH / 9, 4 * _WINDOW_WIDTH / 5, 8 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
            break;
    }
}