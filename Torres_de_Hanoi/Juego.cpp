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
#include <allegro5/allegro_image.h>

void FirstRod(int numDiscs);


enum EST_POS {
    INIT_X = 294,
    Y_ESTS = 463 + 20,
    AUX_X = 600,
    FIN_X = 917
};

#define _STICK_SIZE 318

#define _BASE_FILENAME "base_con_estacas.png"


void Juego(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display) {

    try {
        initialize_al_component(al_init_image_addon(), "Componente de imagenes.");
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what();
        return;
    }

    int Game_discs;
    Game_discs = DiskNumber(queue);
    if (Game_discs == 0) return;

    Estaca::Initialize_stakes(_STICK_SIZE, 20, Game_discs);

    Estaca init(EST_POS::INIT_X, EST_POS::Y_ESTS);
    Estaca aux(EST_POS::AUX_X, EST_POS::Y_ESTS);
    Estaca fin(EST_POS::FIN_X, EST_POS::Y_ESTS);


    aux.InitDiscsAndRods();
    init.InitDiscsAndRods();


    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    bool move = false;
    bool right = false;
    bool finish_movement = false;

    //ALLEGRO_BITMAP* base_and_stakes = al_load_bitmap(_BASE_FILENAME);
    //try {
    //    initialize_al_component(al_load_bitmap, "Imagen de base.");
    //} catch (const std::runtime_error& e) {
    //    std::cout << e.what() << '\n';
    //}

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                
                if (move && right) {
                    if (!init.move_to_stake(fin, move))
                        return;
                    if (!move) right = false;
                } else if (move)
                    if (!aux.move_to_stake(init, move))
                        return;

                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    if (move) move = 0;
                    else done = true;

                else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    move = true;
                    right = true;
                } else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    move = true;
                }
                
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                exit(0);
                break;
        }

        if (done)
            break;

        if (redraw )
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            //al_draw_bitmap(base_and_stakes, 0, 0, 0);

            init.PrintRodDiscs();
            aux.PrintRodDiscs();
            fin.PrintRodDiscs();

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
    int Disks = (_MIN_DISCS + _MAX_DISCS) / 2;

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

                if (Disks < _MAX_DISCS)
                    Disks++;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {

                button_place = _SUBSTRACT;

                if (Disks > _MIN_DISCS)
                    Disks--;
            } else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                done = true;
            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                return 0;

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

