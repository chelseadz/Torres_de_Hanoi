/*****************************************************************//**
 * \file   Juego.cpp
 * \brief  Implementaciones de Juego.h
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/

#include "Juego.h"
#include "Disco_y_Estaca.h"
#include "Selector_flecha.h"

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <allegro5/allegro_image.h>


enum EST_POS {
    INIT_X = 294,
    Y_ESTS = 483,
    AUX_X = 600,
    FIN_X = 917
};

enum {
    _INIT = 0,
    _AUX,
    _FIN
};

#define _STICK_SIZE 336

#define _ARROW_SPACE 75

#define _BASE_FILENAME "base_con_estacas.png"


void Juego(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display) {

    try {
        initialize_al_component(al_init_image_addon(), "Componente de imagenes.");
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what();
        return;
    }

    ALLEGRO_FONT* font_title = al_load_font("ROBOTECH_GP.ttf", 72, 0);
    initialize_al_component(font_title, "font titulo");

    int Game_discs;
    Game_discs = DiskNumber(queue);
    if (Game_discs == 0) return;

    Estaca::Initialize_stakes(_STICK_SIZE, 20, Game_discs);

    Estaca init(EST_POS::INIT_X, EST_POS::Y_ESTS);
    Estaca aux(EST_POS::AUX_X, EST_POS::Y_ESTS);
    Estaca fin(EST_POS::FIN_X, EST_POS::Y_ESTS);


    init.InitDiscsAndRods();

    ALLEGRO_EVENT event;

    bool done = false;
    bool redraw = true;

    bool move = false;
    bool finish_movement = false;

    ALLEGRO_BITMAP* base_and_stakes = al_load_bitmap(_BASE_FILENAME);
    try {
        initialize_al_component(al_load_bitmap, "Imagen de base.");
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }

    Arrow_selector::Set_y_pos(EST_POS::Y_ESTS - _STICK_SIZE - _ARROW_SPACE);

    Arrow_selector::Set_available_stakes(&init, &aux, &fin);

    Arrow_selector origin(_LEFT_S);
    Arrow_selector dest(_MIDDLE_S, 0);


    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                if (move) {
                    origin.pointee()->move_to_stake(dest.pointee(), move, finish_movement);
                    if (move) {
                        origin.show = false;
                        dest.show = false;
                    } else {
                        origin.show = true;
                        origin.selected = false;
                        dest.selected = false;
                        origin.selected_stake = _LEFT_S;

                    }

                }


            case ALLEGRO_EVENT_KEY_DOWN: {
                int key = event.keyboard.keycode;

                if (key == ALLEGRO_KEY_ESCAPE) {
                    if (move) finish_movement = true;
                    else if (origin.selected) {
                        origin.selected = false;
                        origin.show = true;
                        dest.show = false;
                    } else
                        done = true;

                }
                else if (key == ALLEGRO_KEY_RIGHT) {
                    if (!move) {
                        if (!origin.selected) {
                            origin.move_right();
                        }
                        else {
                            dest.move_right();
                            if (dest.selected_stake == origin.selected_stake)
                                dest.move_right();
                        }
                    }
                  

                } else if (key == ALLEGRO_KEY_LEFT) {
                    if (!move) {
                        if (!origin.selected) {
                            origin.move_left();
                        }
                        else {
                            dest.move_left();
                            if (dest.selected_stake == origin.selected_stake)
                                dest.move_left();
                        }
                    }
                }
                else if (key == ALLEGRO_KEY_SPACE || key == ALLEGRO_KEY_ENTER) {

                    if (!origin.selected) {
                        origin.selected = true;
                        if (origin.selected_stake == dest.selected_stake)
                            dest.move_right();
                        dest.show = true;
                    } else {
                        dest.selected = true;
                        move = true;
                    }
                }

                redraw = true;
                break;
            }

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                exit(0);
                break;      
        }

        if (done)
            break;

        if (redraw)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            DrawLogo(font_title, 72, _WINDOW_WIDTH / 2, 0.2 * _WINDOW_HEIGTH / 12);

            al_draw_bitmap(base_and_stakes, 0, 0, 0);

            origin.draw();
            dest.draw();
            origin.pointee()->PrintRodDiscs();

            if(origin.selected_stake != _LEFT_S) init.PrintRodDiscs();
            if(origin.selected_stake != _MIDDLE_S) aux.PrintRodDiscs();
            if(origin.selected_stake != _RIGTH_S) fin.PrintRodDiscs();

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
    al_clear_to_color(HANBLUE);

    //logo del juego
    DrawLogo(text, 36, _WINDOW_WIDTH / 9, 0.1 * _WINDOW_HEIGTH / 9);

    //Title
    al_draw_text(title, WHITE, _WINDOW_WIDTH / 2, _WINDOW_HEIGTH / 5, ALLEGRO_ALIGN_CENTER, "Number of discs: ");

    //Disk Numbers
    std::string tmp = std::to_string(Disks);
    char const* num_char = tmp.c_str();

    al_draw_text(title, WHITE, 2.5 * _WINDOW_WIDTH / 5, 2.25* _WINDOW_HEIGTH / 5, ALLEGRO_ALIGN_CENTER, num_char);

    //Add Button
    al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 2 * _WINDOW_HEIGTH / 5, 2.35 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGTH / 5, 2.65 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGTH / 5, YELLOW);
    //Substract Button
    al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 3 * _WINDOW_HEIGTH / 5, 2.35 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGTH / 5, 2.65 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGTH / 5, YELLOW);

    //Bottom Text
    al_draw_text(text, WHITE, _WINDOW_WIDTH / 2, 3.5 * _WINDOW_HEIGTH / 5, ALLEGRO_ALIGN_CENTER, "Press SPACE or ENTER to continue. ");

}

void ChangeDiskNumberDisplay(int Button) {

    switch (Button)
    {
        case _ADD:
            al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 2 * _WINDOW_HEIGTH / 5, 2.35 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGTH / 5, 2.65 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGTH / 5, VERY_PALE_YELLOW);
            break;
        case _SUBSTRACT:
            al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 3 * _WINDOW_HEIGTH / 5, 2.35 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGTH / 5, 2.65 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGTH / 5, VERY_PALE_YELLOW);
            break;
    }
}

int Min_n_moves(int n_discs) {
    if (n_discs < 0) throw std::invalid_argument("Discos negativos.");

    return std::pow(2, n_discs) - 1;
}



//int What_to_Move(ALLEGRO_EVENT_QUEUE* queue, Estaca &init, Estaca &aux, Estaca &fin) {
//
//    bool done = false;
//    bool redraw = true;
//    ALLEGRO_EVENT event;
//
//    int button_place = 0;
//
//    while (1)
//    {
//        al_wait_for_event(queue, &event);
//
//        switch (event.type)
//        {
//        case ALLEGRO_EVENT_TIMER:
//            // nada por ahora.
//            redraw = true;
//            break;
//
//        case ALLEGRO_EVENT_KEY_DOWN:
//
//            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
//
//                if (button_place < _FIN)
//                    button_place++;
//            }
//            else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
//
//                if (button_place > _INIT)
//                    button_place--;
//            }
//            else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
//                return button_place;
//                done = true;
//            }
//                
//            
//
//            break;
//
//
//        case ALLEGRO_EVENT_DISPLAY_CLOSE:
//            done = true;
//            exit(0);
//            break;
//        }
//
//        if (done)
//            break;
//
//        if (redraw && al_is_event_queue_empty(queue))
//        {
//            al_clear_to_color(al_map_rgb(0, 0, 0));
//            init.PrintRodDiscs();
//            aux.PrintRodDiscs();
//            fin.PrintRodDiscs();
//            What_to_Move_Display(button_place);
//
//            al_flip_display();
//
//            redraw = false;
//        }
//    }
//}
//
//void What_to_Move_Display(int Button) {
//
//    switch (Button)
//    {
//    case _INIT:
//        al_draw_filled_triangle(EST_POS::INIT_X, 100, EST_POS::INIT_X - 30, 50 , EST_POS::INIT_X + 30, 50, al_map_rgba_f(239, 255, 0, 0.3));
//        break;
//    case _AUX:
//        al_draw_filled_triangle(EST_POS::AUX_X, 100, EST_POS::AUX_X - 30, 50, EST_POS::AUX_X + 30, 50, al_map_rgba_f(239, 255, 0, 0.3));
//        break;
//    case _FIN:
//        al_draw_filled_triangle(EST_POS::FIN_X, 100, EST_POS::FIN_X - 30, 50, EST_POS::FIN_X + 30, 50, al_map_rgba_f(239, 255, 0, 0.3));
//        break;
//
//    }
//}
//
//int Where_to_Move(ALLEGRO_EVENT_QUEUE* queue, int Origin, Estaca& init, Estaca& aux, Estaca& fin) {
//
//    bool done = false;
//    bool redraw = true;
//    ALLEGRO_EVENT event;
//
//    int button_place = Origin;
//
//    while (1)
//    {
//        al_wait_for_event(queue, &event);
//
//        switch (event.type)
//        {
//        case ALLEGRO_EVENT_TIMER:
//            // nada por ahora.
//            redraw = true;
//            break;
//
//        case ALLEGRO_EVENT_KEY_DOWN:
//
//            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
//
//                if (button_place < _FIN)
//                    button_place++;
//            }
//            else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
//
//                if (button_place > _INIT)
//                    button_place--;
//            }
//            else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
//                return button_place;
//                done = true;
//            }
//
//            break;
//
//
//        case ALLEGRO_EVENT_DISPLAY_CLOSE:
//            done = true;
//            exit(0);
//            break;
//        }
//
//        if (done)
//            break;
//
//        if (redraw && al_is_event_queue_empty(queue))
//        {
//            al_clear_to_color(al_map_rgb(0, 0, 0));
//            init.PrintRodDiscs();
//            aux.PrintRodDiscs();
//            fin.PrintRodDiscs();
//            Where_to_Move_Display(Origin, button_place);
//
//            al_flip_display();
//
//            redraw = false;
//        }
//    }
//}
//
//void Where_to_Move_Display(int Origin, int Dest) {
//
//    switch (Origin)
//    {
//    case _INIT:
//        al_draw_filled_triangle(EST_POS::INIT_X, 100, EST_POS::INIT_X - 30, 50, EST_POS::INIT_X + 30, 50, al_map_rgba_f(239, 255, 0, 0.8));
//        break;
//    case _AUX:
//        al_draw_filled_triangle(EST_POS::AUX_X, 100, EST_POS::AUX_X - 30, 50, EST_POS::AUX_X + 30, 50, al_map_rgba_f(239, 255, 0, 0.8));
//        break;
//    case _FIN:
//        al_draw_filled_triangle(EST_POS::FIN_X, 100, EST_POS::FIN_X - 30, 50, EST_POS::FIN_X + 30, 50, al_map_rgba_f(239, 255, 0, 0.8));
//        break;
//
//    }
//
//    switch (Dest)
//    {
//    case _INIT:
//        al_draw_filled_triangle(EST_POS::INIT_X, 100, EST_POS::INIT_X - 30, 50, EST_POS::INIT_X + 30, 50, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
//        break;
//    case _AUX:
//        al_draw_filled_triangle(EST_POS::AUX_X, 100, EST_POS::AUX_X - 30, 50, EST_POS::AUX_X + 30, 50, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
//        break;
//    case _FIN:
//        al_draw_filled_triangle(EST_POS::FIN_X, 100, EST_POS::FIN_X - 30, 50, EST_POS::FIN_X + 30, 50, al_map_rgba_f(0.5, 0.5, 0.5, 0.5));
//        break;
//
//    }
//}
