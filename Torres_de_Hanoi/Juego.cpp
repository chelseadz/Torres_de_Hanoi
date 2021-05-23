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
#include <string>
#include <allegro5/allegro_image.h>


enum EST_POS {
    INIT_X = 297,
    Y_ESTS = 497,
    AUX_X = 603,
    FIN_X = 917
};

enum {
    _INIT = 0,
    _AUX,
    _FIN
};

#define _STICK_SIZE 316

#define _ARROW_SPACE 65

#define _BASE_FILENAME "base_con_estacas_delgada.png"
#define _COLUMN_PORTION_FILENAME "estaca_larga.png"

#define _ERROR_SOUND_FILENAME "gnome_error.wav"

#define _TITLE_FONT_FILENAME "ROBOTECH_GP.ttf"


void Juego(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display) {

    try {
        initialize_al_component(al_init_image_addon(), "image component.");
        initialize_al_component(al_install_audio(), "audio addon.");
        initialize_al_component(al_init_acodec_addon(), "audio codecs.");
        initialize_al_component(al_reserve_samples(8), "audio samples.");     
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
        return;
    }

    ALLEGRO_BITMAP* base_and_stakes = al_load_bitmap(_BASE_FILENAME);
    ALLEGRO_BITMAP* column_portion = al_load_bitmap(_COLUMN_PORTION_FILENAME);
    ALLEGRO_SAMPLE* error_sound = al_load_sample(_ERROR_SOUND_FILENAME);
    ALLEGRO_SAMPLE* select_sound = al_load_sample(_SELECT_SOUND_FILENAME);
    ALLEGRO_SAMPLE* move_sound = al_load_sample(_MOVE_SOUND_FILENAME);
    ALLEGRO_FONT* font_title = al_load_font(_TITLE_FONT_FILENAME, 72, 0);
    ALLEGRO_FONT* move_count_font = al_load_font(_TITLE_FONT_FILENAME, 38, 0);

    try {
        initialize_al_component(base_and_stakes, "base image.");
        initialize_al_component(column_portion, "column portion image.");
        initialize_al_component(error_sound, "error sound.");
        initialize_al_component(font_title, "font titulo");
        initialize_al_component(select_sound, "Select sound");
        initialize_al_component(move_sound, "Move sound");

    } catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
        return;
    }

    int Game_discs;
    Game_discs = DiskNumber(queue, move_sound, select_sound);
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


    Arrow_selector::Set_y_pos(EST_POS::Y_ESTS - _STICK_SIZE - _ARROW_SPACE);

    Arrow_selector::Set_available_stakes(&init, &aux, &fin);

    Arrow_selector origin(_LEFT_S);
    Arrow_selector dest(_MIDDLE_S, 0);

    unsigned moves_done = 0;

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                if (move) {
                    if (origin.pointee()->move_to_stake(dest.pointee(), move, finish_movement)) {
                        
                        if (move) {
                            origin.show = false;
                            dest.show = false;
                        }
                        else {
                            origin.show = true;
                            origin.selected = false;
                            dest.selected = false;
                            origin.selected_stake = _LEFT_S;

                            ++moves_done;

                        }
                    } else {
                        //Movimiento inv\240lido.
                        move = 0;
                        dest.selected = false;
                        dest.show = false;
                        origin.selected = false;
                        al_play_sample(error_sound, 1.0f, 1.0f, 0.9f, ALLEGRO_PLAYMODE_ONCE, NULL);
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
                    al_play_sample(move_sound, 1.0f, 1.0f, 0.9f, ALLEGRO_PLAYMODE_ONCE, NULL);
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
                    al_play_sample(move_sound, 1.0f, 1.0f, 0.9f, ALLEGRO_PLAYMODE_ONCE, NULL);
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
                    al_play_sample(move_sound, 1.0f, 1.0f, 0.9f, ALLEGRO_PLAYMODE_ONCE, NULL);
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

            DrawLogo(font_title, 72, _WINDOW_WIDTH / 2, 0.2 * _WINDOW_HEIGHT / 12);

            al_draw_bitmap(base_and_stakes, 0, 0, 0);

            origin.draw();
            dest.draw();
            origin.pointee()->PrintRodDiscs(column_portion);

            if(origin.selected_stake != _LEFT_S) init.PrintRodDiscs(column_portion);
            if(origin.selected_stake != _MIDDLE_S) aux.PrintRodDiscs(column_portion);
            if(origin.selected_stake != _RIGHT_S) fin.PrintRodDiscs(column_portion);

            DisplayNMoves(moves_done, move_count_font);

            al_flip_display();

            redraw = false;
        }

    }

    al_destroy_bitmap(base_and_stakes);
    al_destroy_bitmap(column_portion);
    al_destroy_sample(error_sound);
    al_destroy_font(font_title);
    al_destroy_font(move_count_font);

    al_flush_event_queue(queue);
}

int DiskNumber(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_SAMPLE* move_sound, ALLEGRO_SAMPLE* select_sound) {

    ALLEGRO_FONT* font_title = al_load_font("ROBOTECH_GP.ttf", 48, 0);
    ALLEGRO_FONT* font = al_load_font("ROBOTECH_GP.ttf", 36, 0);

    try {
        initialize_al_component(font, "font");
        initialize_al_component(font_title, "font titulo");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return 0;
    }
    
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

            al_play_sample(move_sound, 1.0f, 1.0f, 0.9f, ALLEGRO_PLAYMODE_ONCE, NULL);

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
    DrawLogo(text, 36, _WINDOW_WIDTH / 9, 0.1 * _WINDOW_HEIGHT / 9);

    //Title
    al_draw_text(title, WHITE, _WINDOW_WIDTH / 2, _WINDOW_HEIGHT / 5, ALLEGRO_ALIGN_CENTER, "Number of discs: ");

    //Disk Numbers
    std::string tmp = std::to_string(Disks);
    char const* num_char = tmp.c_str();

    al_draw_text(title, WHITE, 2.5 * _WINDOW_WIDTH / 5, 2.25* _WINDOW_HEIGHT / 5, ALLEGRO_ALIGN_CENTER, num_char);

    //Add Button
    al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 2 * _WINDOW_HEIGHT / 5, 2.35 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGHT / 5, 2.65 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGHT / 5, YELLOW);
    //Substract Button
    al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 3 * _WINDOW_HEIGHT / 5, 2.35 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGHT / 5, 2.65 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGHT / 5, YELLOW);

    //Bottom Text
    al_draw_text(text, WHITE, _WINDOW_WIDTH / 2, 3.5 * _WINDOW_HEIGHT / 5, ALLEGRO_ALIGN_CENTER, "Press SPACE or ENTER to continue. ");

}

void ChangeDiskNumberDisplay(int Button) {

    switch (Button)
    {
        case _ADD:
            al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 2 * _WINDOW_HEIGHT / 5, 2.35 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGHT / 5, 2.65 * _WINDOW_WIDTH / 5, 2.2 * _WINDOW_HEIGHT / 5, VERY_PALE_YELLOW);
            break;
        case _SUBSTRACT:
            al_draw_filled_triangle(2.5 * _WINDOW_WIDTH / 5, 3 * _WINDOW_HEIGHT / 5, 2.35 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGHT / 5, 2.65 * _WINDOW_WIDTH / 5, 2.8 * _WINDOW_HEIGHT / 5, VERY_PALE_YELLOW);
            break;
    }
}

int MinNMoves(int n_discs) {
    if (n_discs < 0) throw std::invalid_argument("Discos negativos.");

    return std::pow(2, n_discs) - 1;
}


void DisplayNMoves (unsigned n_moves, ALLEGRO_FONT* font) {
    try {
        initialize_al_component(font, "move count font.");

        std::string s("Moves made: ");
        s.append(std::to_string(n_moves));

        al_draw_text(font, UNITED_NATIONS_BLUE, 30, _WINDOW_HEIGHT - 50, 0, s.c_str());

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}
