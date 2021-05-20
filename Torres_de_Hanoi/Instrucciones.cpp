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
    _SIGUIENTE
};

void Instrucciones(ALLEGRO_EVENT_QUEUE* queue) {


    ALLEGRO_FONT* font_title = al_load_font("ROBOTECH_GP.ttf", 36, 0);
    ALLEGRO_FONT* font = al_load_font("ROBOTECH_GP.ttf", 36, 0);
    ALLEGRO_FONT* font_paragraph = al_load_font("ROBOTECH_GP.ttf", 22, 0);

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
                    button_place = _SIGUIENTE;
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

                    case _SIGUIENTE:
                        Origen(queue);
                        break;
                    }
            }

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
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, 0.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "instrucciones");
    //Cuerpo instrucciones
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 1.2 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Las Torres de Hanoi es un rompecabezas o juego matemAtico inventado en 1883 por el matemAtico");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 1.7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "francEs Edouard Lucas. Este juego consiste en un numero de discos perforados de radio");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.2 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "creciente que se apilan insertAndose en uno de los tres postes fijados a un tablero. ");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "El objetivo del juego es trasladar la pila de discos a otro de los postes. ");

    //Titulo Reglas
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, 3.2 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "REGLAS");
    //Cuerpo reglas
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 3.9 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "1. No se puede colocar un disco mAs grande encima de un disco mAs pequeño.");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 4.4 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "2. El juego se gana cuando logras insertar todos los discos apilados de mayor a menor en el poste del");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 4.9 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "extremo derecho. ");

    //Titulo Controles
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, 5.4 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "Controles");
    //Cuerpo controles
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 6.1 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Usa ESPACIO o ENTER para seleccionar el disco.");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 6.6 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Usa las flechas para mover el disco o navegar en el juego.");

    //Boton Regresar
    al_draw_filled_rectangle(_WINDOW_WIDTH / 5, 7.5 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 5, 8.5 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.3));
    al_draw_text(text, al_map_rgb(255, 255, 255), 1.5 * _WINDOW_WIDTH / 5, 7.7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "REGRESAR");
    //Boton Origen
    al_draw_filled_rectangle(3 * _WINDOW_WIDTH / 5, 7.5 * _WINDOW_HEIGTH / 9, 4 * _WINDOW_WIDTH / 5, 8.5 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.5));
    al_draw_text(text, al_map_rgb(255, 255, 255), 3.5 * _WINDOW_WIDTH / 5, 7.7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "ORIGEN");

}

void MoverSeleccion_Instrucciones(int Button) {

    switch (Button)
    {
        case _REGRESAR:
            al_draw_filled_rectangle(_WINDOW_WIDTH / 5, 7.5 * _WINDOW_HEIGTH / 9, 2 * _WINDOW_WIDTH / 5, 8.5 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
            break;
        case _SIGUIENTE:
            al_draw_filled_rectangle(3 * _WINDOW_WIDTH / 5, 7.5 * _WINDOW_HEIGTH / 9, 4 * _WINDOW_WIDTH / 5, 8.5 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
            break;
    }
}


// Inicia la pantalla que muestra el origen del juego, muestra el botón para volver a 
// instrucciones o para ir a la solución del acertijo
void Origen(ALLEGRO_EVENT_QUEUE* queue) {

    ALLEGRO_FONT* font_title = al_load_font("ROBOTECH_GP.ttf", 36, 0);
    ALLEGRO_FONT* font = al_load_font("ROBOTECH_GP.ttf", 36, 0);
    ALLEGRO_FONT* font_paragraph = al_load_font("ROBOTECH_GP.ttf", 22, 0);

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
            // nada por ahora.
            redraw = true;
            break; 

        case ALLEGRO_EVENT_KEY_DOWN:
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) done = true;                

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
            OrigenDisplay(font_title, font, font_paragraph);

            al_flip_display();

            redraw = false;
        }
    }
    //Destruir fuentes creadas
    al_destroy_font(font);
    al_destroy_font(font_title);
    al_destroy_font(font_paragraph);

}

void OrigenDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph) {

    //Pantalla
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //Titulo Instrucciones
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, 0.5 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER, "Origen");
    //Cuerpo instrucciones
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 1.2 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "SegUn cuenta la leyenda, estos tres postes hacen referencia a tres agujas de diamante de");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 1.7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "un codo de altura y del grueso del cuerpo de una abeja, que yacen una base de bronce en");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.2 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "la que se encuentran fijadas. EstAn debajo de la cUpula del gran templo de BenarEs. ");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 2.7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "En una de estas agujas, Dios, en el comienzo de los siglos, colocO sesenta y cuatro discos ");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 3.2 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "de oro puro. DIa y noche los sacerdotes se turnan para mover los discos, sin desviarse");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 3.7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "de las reglas fijas e inmutables impuestas por Brahma.");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 4.2 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "El sacerdote no debe mover mas de un disco a la vez, y no debe colocar un disco mas que");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 4.7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "en una aguja libre, o sobre un disco mayor.");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 5.2 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Cuando los sacerdotes trasladen toda la columna de discos a la tercera torre, la torre");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 5.7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "y los brahmanes se convertirAn en polvo y serA el fin del mundo.");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 6.4 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "Si los sacerdotes fuesen capaces de realizar un movimiento cada segundo, cuAl serIa el");
    al_draw_text(paragraph, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 9, 6.9 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_LEFT,
        "tiempo necesario para trasladar la columna y, por tanto, ¿cuAndo acabaria el mundo?");

    //BOTON REGRESAR
    al_draw_filled_rectangle(_WINDOW_WIDTH / 5, 7.5 * _WINDOW_HEIGTH / 9, 4 * _WINDOW_WIDTH / 5, 8.5 * _WINDOW_HEIGTH / 9, al_map_rgba_f(0, 0, 0.5, 0.3));
    al_draw_text(text, al_map_rgb(255, 255, 255),  _WINDOW_WIDTH / 2, 7.7 * _WINDOW_HEIGTH / 9, ALLEGRO_ALIGN_CENTER,
        "Presiona ESC, Espacio o ENTER para regresar.");
 }


