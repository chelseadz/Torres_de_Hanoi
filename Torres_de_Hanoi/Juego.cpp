/*****************************************************************//**
 * \file   Juego.cpp
 * \brief  Implementaciones de Juego.h
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/

#include "Juego.h"
#include "Disco_y_Estaca.h"

#include <iostream>
#include <stdexcept>

void FirstRod(int numDiscs);

void Juego(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display) {


    int Game_discs;
    Game_discs = DiskNumber(queue);


    Estaca::Initialize_stakes(400, 20, Game_discs);

    Estaca Prueba(_WINDOW_WIDTH / 2 - 300, 8 * _WINDOW_HEIGTH / 9);

    Estaca Prueba_2(_WINDOW_WIDTH / 2 + 300, 8 * _WINDOW_HEIGTH / 9);

    Prueba.InitDiscsAndRods();


    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    bool move = false;

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            // nada por ahora.
            if (move) Prueba.move_to_stake(Prueba_2, move);

            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;
            else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                move = true;
                //Prueba.move_to_stake(Prueba_2, queue, display);
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
            al_clear_to_color(al_map_rgb(0, 0, 0));

            Prueba.PrintRod();
            Prueba_2.PrintRod();

            al_flip_display();

            redraw = false;
        }

    }


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
            exit(0);
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

void PrintRod(double pos_x, double pos_y, int numDisks) {
	//Palo Estaca
    //Pruebas
    double stick_width = 20;
    double stick_height;

    double disk_width = 200;
    double disk_height = 30;

    stick_height = 11 * disk_height;

    //Estaca
	al_draw_filled_rectangle((-stick_width)/2 + pos_x, pos_y, (stick_width)/2 + pos_x, stick_height, al_map_rgba_f(0, 0, 0.5, 0.3));

    //Discos
    //int color_pruebas = 10;
   // double ShrinkFactor = (disk_width / 2) * (0.1);
 /*   for (int i = 0; i < numDisks; i++) {
        al_draw_filled_rectangle(((-disk_width)/2) - (1.0-i)*ShrinkFactor + pos_x, -(i - 1.0) * disk_height + pos_y, ((disk_width) / 2) + (1.0 - i) * ShrinkFactor + pos_x, -i*disk_height + pos_y, al_map_rgba_f(0.1*i, 0.05*i, 0.5, 0.3));
        
    }*/
}

