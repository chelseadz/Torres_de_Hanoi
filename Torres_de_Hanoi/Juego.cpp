/*****************************************************************//**
 * \file   Juego.cpp
 * \brief  Implementaciones de Juego.h
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/

#include "Juego.h"



void Juego(ALLEGRO_EVENT_QUEUE* queue) {

    int InitialDisks = 3;
    InitialDisks = DiskNumber(queue);


}

int DiskNumber(ALLEGRO_EVENT_QUEUE* queue) {

    ALLEGRO_FONT* font_title = al_load_font("ROBOTECH_GP.ttf", 48, 0);
    ALLEGRO_FONT* font = al_load_font("ROBOTECH_GP.ttf", 36, 0);

    initialize_al_component(font, "font");
    initialize_al_component(font_title, "font titulo");

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    int button_place = 0;
    int Disks = 3;

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
                button_place = _ADD;
                
                if (Disks < MAX_DISKS)
                    Disks++;
            }

            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {

                button_place = _SUBSTRACT;

                if (Disks > 3)
                    Disks--;
            }
          
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                done = true;

            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            
            NumberOfDisksDisplay(font_title, font, Disks);
            ChangeDiskNumberDisplay(button_place);

            al_flip_display();

            redraw = false;
        }
    }

    //Destruir fuentes creadas
    al_destroy_font(font);
    al_destroy_font(font_title);

    return Disks;
}

void NumberOfDisksDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, int Disks) {

    //Screen
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //Title
    al_draw_text(title, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, _WINDOW_HEIGTH / 5, ALLEGRO_ALIGN_CENTER, "Numero de Discos: ");

    //Disk Numbers
    std::string tmp = std::to_string(Disks);
    char const* num_char = tmp.c_str();

    al_draw_text(title, al_map_rgb(255, 255, 255), 2.5 * _WINDOW_WIDTH / 5, 2.25* _WINDOW_HEIGTH / 5, ALLEGRO_ALIGN_CENTER, num_char);

    //Add Button
    al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 2 * _WINDOW_HEIGTH / 5, 2.35 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGTH / 5, 2.65 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGTH / 5, al_map_rgba_f(239, 255, 0, 0.3));
    //Substract Button
    al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 3 * _WINDOW_HEIGTH / 5, 2.35 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGTH / 5, 2.65 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGTH / 5, al_map_rgba_f(239, 255, 0, 0.3));

    //Bottom Text
    al_draw_text(text, al_map_rgb(255, 255, 255), _WINDOW_WIDTH / 2, 3.5 * _WINDOW_HEIGTH / 5, ALLEGRO_ALIGN_CENTER, "Click ESPACIO o ENTER para continuar. ");

}

void ChangeDiskNumberDisplay(int Button) {

    switch (Button)
    {
    case _ADD:
        al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 2 * _WINDOW_HEIGTH / 5, 2.35 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGTH / 5, 2.65 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGTH / 5, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
        break;
    case _SUBSTRACT:
        al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 3 * _WINDOW_HEIGTH / 5, 2.35 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGTH / 5, 2.65 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGTH / 5, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
        break;
    }

}
