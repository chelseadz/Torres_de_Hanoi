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
#include "Utileria.h"


#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <cstring>
#include <allegro5/allegro_image.h>


enum EST_POS {
    INIT_X = 297,
    Y_ESTS = 512,
    AUX_X = 603,
    FIN_X = 917
};

enum {
    _INIT = 0,
    _AUX,
    _FIN
};

enum {
    _KEEP = 0,
    _HOME
};

#define _STICK_SIZE 316

#define _ARROW_SPACE 65

#define _BASE_FILENAME "base_con_estacas_delgada.png"
#define _COLUMN_PORTION_FILENAME "estaca_larga.png"

#define _ERROR_SOUND_FILENAME "gnome_error.wav"
#define _WINNER_SOUND_FILENAME "winner.wav"

#define _TITLE_FONT_FILENAME "ROBOTECH_GP.ttf"
#define _HELVETICA_LIGHT_FILENAME "HelveticaLTStdLight.ttf"

#define _BASE_SCORES_FILENAME "highscores"


void Juego(ALLEGRO_EVENT_QUEUE* queue) {

    try {

        initialize_al_component(al_init_image_addon(), "image component");
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
        return;
    }

    ALLEGRO_BITMAP* base_and_stakes = al_load_bitmap(_BASE_FILENAME);
    ALLEGRO_BITMAP* column_portion = al_load_bitmap(_COLUMN_PORTION_FILENAME);
    ALLEGRO_SAMPLE* error_sound = al_load_sample(_ERROR_SOUND_FILENAME);
    ALLEGRO_SAMPLE* winner_sound = al_load_sample(_WINNER_SOUND_FILENAME);
    ALLEGRO_SAMPLE* select_sound = al_load_sample(_SELECT_SOUND_FILENAME);
    ALLEGRO_SAMPLE* move_sound = al_load_sample(_MOVE_SOUND_FILENAME);
    ALLEGRO_FONT* font_title = al_load_font(_TITLE_FONT_FILENAME, 72, 0);
    ALLEGRO_FONT* move_count_font = al_load_font(_TITLE_FONT_FILENAME, 38, 0);

    try {
        initialize_al_component(base_and_stakes, "base image");
        initialize_al_component(column_portion, "column portion image");
        initialize_al_component(error_sound, "error sound");
        initialize_al_component(winner_sound, "winner sound");
        initialize_al_component(font_title, "font titulo");
        initialize_al_component(select_sound, "Select sound");
        initialize_al_component(move_sound, "Move sound");
        initialize_al_component(move_count_font, "move count font");

    } catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
        return;
    }

    int Game_discs;
    Game_discs = DiskNumber(queue, move_sound, select_sound, error_sound);
    if (Game_discs < 2) return;

    int min_moves = MinNMoves(Game_discs);

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
                            dest.selected_stake = _LEFT_S;

                            ++moves_done;

                            if (fin.full()) {
                                al_play_sample(winner_sound, 1.0f, 1.0f, 0.9f, ALLEGRO_PLAYMODE_ONCE, NULL);

                                al_clear_to_color(al_map_rgb(0, 0, 0));

                                Ending(queue, moves_done, min_moves, Game_discs);
                                done = true;
                            }

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
                    al_play_sample(move_sound, 1.0f, 1.0f, 0.9f, ALLEGRO_PLAYMODE_ONCE, NULL);
                    if (move) finish_movement = true;
                    else if (origin.selected) {
                        origin.selected = false;
                        origin.show = true;
                        dest.show = false;
                    } else if (EscapeGame(queue, font_title, move_sound, move_sound) ){
                        done = true;
                    }
                        
                }

                else if (key == ALLEGRO_KEY_RIGHT || key == ALLEGRO_KEY_D) {

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
                  


                } else if (key == ALLEGRO_KEY_LEFT || key == ALLEGRO_KEY_A) {

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
            DisplayMinMoves(Game_discs, move_count_font);

            al_flip_display();

            redraw = false;
        }

    }

    al_destroy_bitmap(base_and_stakes);
    al_destroy_bitmap(column_portion);
    al_destroy_sample(error_sound);
    al_destroy_sample(move_sound);
    al_destroy_sample(select_sound);
    al_destroy_font(font_title);
    al_destroy_font(move_count_font);

    al_flush_event_queue(queue);
}

int DiskNumber(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_SAMPLE* move_sound,
    ALLEGRO_SAMPLE* select_sound, ALLEGRO_SAMPLE* error_sound) {

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

        case ALLEGRO_EVENT_KEY_DOWN: {
            int key = event.keyboard.keycode;

            if ((key == ALLEGRO_KEY_UP && Disks + 1 > _MAX_DISCS) ||
                (key == ALLEGRO_KEY_DOWN && Disks - 1 < _MIN_DISCS)) {
                al_play_sample(error_sound, 1.0f, 1.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
            else
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
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                done = true;
                al_play_sample(select_sound, 1.0f, 1.0f, 1.2f, ALLEGRO_PLAYMODE_ONCE, NULL);
            }

            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                return 0;

            break;

        }
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
        initialize_al_component(font, "move count font");

        std::string s("Moves made: ");
        s.append(std::to_string(n_moves));

        al_draw_text(font, UNITED_NATIONS_BLUE, 30, _WINDOW_HEIGHT - 50, 0, s.c_str());

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

void DisplayMinMoves(unsigned numDiscs, ALLEGRO_FONT* font) {
    try {
        initialize_al_component(font, "min move font");
        std::string s("Min Moves: ");
        unsigned min_moves = MinNMoves(numDiscs);
        s.append(std::to_string(min_moves));
        al_draw_text(font, UNITED_NATIONS_BLUE, 350, _WINDOW_HEIGHT - 50, 0, s.c_str());
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}


bool EscapeGame(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE* escape_sound,
                ALLEGRO_SAMPLE* move_sound) {

    bool redraw = true;
    ALLEGRO_EVENT event;

    int button_place = _KEEP;

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                
                al_play_sample(move_sound, 1.0f, 1.0f, 0.9f, ALLEGRO_PLAYMODE_ONCE, NULL);

                if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    button_place = (button_place - 1) % 2;
                    if (button_place < 0)
                        button_place = _HOME;
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                    button_place = (button_place + 1) % 2;

                if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    
                    switch (button_place)
                    {
                        case _KEEP: 
                           return false;
                        case _HOME: 
                            al_play_sample(escape_sound, 1.0f, 1.0f, 0.9f, ALLEGRO_PLAYMODE_ONCE, NULL);
                            return true;
                    }
                }

                else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    return false;

                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                exit(0);
                break;
        }

        if (redraw && al_is_event_queue_empty(queue))
        {
            DisplayEscapeGame(font);

            switch (button_place)
            {
                case _KEEP:
                    al_draw_filled_rectangle(_WINDOW_WIDTH / 10, 1.1 * _WINDOW_HEIGHT / 2, 5 * _WINDOW_WIDTH / 10,
                        1.5 * _WINDOW_HEIGHT / 2, al_map_rgba_f(0.3, 0.3, 0.3, 0.3));
                break;
                case _HOME:
                    al_draw_filled_rectangle(5 * _WINDOW_WIDTH / 8, 1.1 * _WINDOW_HEIGHT / 2, 7 * _WINDOW_WIDTH / 8,
                        1.5 * _WINDOW_HEIGHT / 2, al_map_rgba_f(0.3, 0.3, 0.3, 0.3));
                break;
            }

            al_flip_display();

            redraw = false;
        }
    }
}
void DisplayEscapeGame(ALLEGRO_FONT* font) {

    al_clear_to_color(HANBLUE);

    al_draw_text(font, WHITE, _WINDOW_WIDTH / 2, 0.5 * _WINDOW_HEIGHT / 2, ALLEGRO_ALIGN_CENTER,
        "Sure you want to leave?");

    //Boton seguir jugando
    DrawButton(_WINDOW_WIDTH / 10, 1.1 * _WINDOW_HEIGHT / 2, 5 * _WINDOW_WIDTH / 10,
        1.5 * _WINDOW_HEIGHT / 2, font, "Keep playing");
    //Boton home
    DrawButton(5 * _WINDOW_WIDTH / 8, 1.1 * _WINDOW_HEIGHT / 2, 7 * _WINDOW_WIDTH / 8,
        1.5 * _WINDOW_HEIGHT / 2, font, "Go home");
}


void Ending(ALLEGRO_EVENT_QUEUE* queue, int moves, int min_moves, int discs) {

    ALLEGRO_FONT* font_title = al_load_font(_TITLE_FONT_FILENAME, 72, 0);
    ALLEGRO_FONT* font = al_load_font(_TITLE_FONT_FILENAME, 36, 0);
    ALLEGRO_FONT* font_paragraph = al_load_font(_HELVETICA_LIGHT_FILENAME, 36, 0);

    initialize_al_component(font, "font");
    initialize_al_component(font_title, "font titulo");
    initialize_al_component(font_paragraph, "font parrafo");

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    bool saving = false;
    bool done_saving = false;
    bool first_char = false;
    ALLEGRO_USTR* save_name = al_ustr_new("");

    int n_scores;
    Score* highscores = GetHighScores(discs, n_scores);

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_CHAR:
            if (saving && event.keyboard.repeat == false) {

                int c = event.keyboard.unichar;
                if (c > 31)
                    al_ustr_append_chr(save_name, c);
            }

            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) done = true;

            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                if (saving && !done_saving) {
                    done_saving = true;
                    saving = false;

                    std::string filename(_BASE_SCORES_FILENAME);
                    filename.append(std::to_string(discs));
                    filename.append(".txt");

                    std::string name(al_cstr(save_name));

                    Score user_score{ (short)moves };
                    
                    strncpy_s(user_score.name, _MAX_NAME_CHARS, name.c_str(), name.length());

                    AddScoresToFile(filename.c_str(), highscores, n_scores, user_score);

                    
                } else 
                    done = true;

            if (!saving && event.keyboard.keycode == ALLEGRO_KEY_TAB) {
                if (!done_saving) saving = true;
                first_char = true;
                al_flush_event_queue(queue);
            }

            if (saving && !done_saving && event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                int pos = al_ustr_size(save_name) - 1;
                if (pos < 0) break;

                al_ustr_remove_chr(save_name, pos);
            }

            break;


        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            exit(0);
            break;
        }

        if (done)
            break;

        if (redraw /*&& al_is_event_queue_empty(queue)*/)
        {
            al_clear_to_color(BLACK);

            DisplayNMoves(moves, font);
            DisplayMinMoves(discs, font);
            
            EndingDisplay(font_title, font, font_paragraph, moves, min_moves);

            DisplayHighScores(font_title, font_paragraph, highscores, n_scores);

            if (!saving && !done_saving) {
                al_draw_text(font_paragraph, WHITE, 1.5 * _WINDOW_WIDTH / 16, 6 * _WINDOW_HEIGHT / 9,
                    0, "Press TAB if you want to save your score...");
            } else if (saving && !done_saving) {
                al_draw_text(font_paragraph, VERY_PALE_YELLOW, 1.5 * _WINDOW_WIDTH / 16,
                    6 * _WINDOW_HEIGHT / 9, 0, "Name: ");
                al_draw_text(font_paragraph, VERY_PALE_YELLOW, 3 * _WINDOW_WIDTH / 16,
                    6 * _WINDOW_HEIGHT / 9, 0, al_cstr(save_name));
            }
            else if (done_saving) {
                al_draw_text(font_paragraph, VERY_PALE_YELLOW, 1.5 * _WINDOW_WIDTH / 16,
                    6 * _WINDOW_HEIGHT / 9, 0, "New score saved. Press ENTER or SPACE to quit to menu.");
            }

            al_flip_display();

            redraw = false;
        }
    }
    //Destruir fuentes creadas
    al_destroy_font(font);
    al_destroy_font(font_title);
    al_destroy_font(font_paragraph);
    al_ustr_free(save_name);

    delete[] highscores;

}

void EndingDisplay(ALLEGRO_FONT* title, ALLEGRO_FONT* text, ALLEGRO_FONT* paragraph, int moves, int min_moves) {

    //Pantalla
    al_clear_to_color(HANBLUE);

    DrawLogo(text, 36, _WINDOW_WIDTH / 9, 0.1 * _WINDOW_HEIGHT / 9);

    if (moves == min_moves) {
        //Titulo Origen
        al_draw_text(title, YELLOW_RED, _WINDOW_WIDTH / 2, 1 * _WINDOW_HEIGHT / 18, ALLEGRO_ALIGN_CENTER,
            "PERFECT!");
        //Cuerpo Origen

        al_draw_text(paragraph, WHITE, _WINDOW_WIDTH / 2, 3.2 * _WINDOW_HEIGHT / 18, ALLEGRO_ALIGN_CENTER,
            "You won the game with the least possible number of moves!");
    }
    else {
        //Titulo Origen
        al_draw_text(title, YELLOW_RED, _WINDOW_WIDTH / 2, 1 * _WINDOW_HEIGHT / 18, ALLEGRO_ALIGN_CENTER,
            "YOU WIN!");
        //Cuerpo Origen

        al_draw_text(paragraph, WHITE, _WINDOW_WIDTH / 2, 3.2 * _WINDOW_HEIGHT / 18, ALLEGRO_ALIGN_CENTER,
            "However, you have made too many moves ...");
    }

    //BOTON REGRESAR
    DrawButton(_WINDOW_WIDTH / 5, 7 * _WINDOW_HEIGHT / 9, 4 * _WINDOW_WIDTH / 5,
        8 * _WINDOW_HEIGHT / 9, text, "Press ESC, SPACE or ENTER to go home.");

}

void DisplayHighScores(ALLEGRO_FONT* header, ALLEGRO_FONT* text, Score* scores, int n_scores) {
    try {
        initialize_al_component(header, "header font");
        initialize_al_component(text, "text font");

        al_draw_text(header, UNITED_NATIONS_BLUE, 1 * _WINDOW_WIDTH / 16, 2 * _WINDOW_HEIGHT / 9,
            0, "Highscores: ");


        if (n_scores == 0) {
            al_draw_text(text, WHITE, 1.5 * _WINDOW_WIDTH / 16, 3.2 * _WINDOW_HEIGHT / 9, 0,
                "No saved scores yet...");
        } else {
            for (int i = 0; i < n_scores; ++i) {
                al_draw_text(text, VERY_PALE_YELLOW, 1.5 * _WINDOW_WIDTH / 16,
                    (3.2 + i / 2.0f) * _WINDOW_HEIGHT / 9, 0,
                    scores[i].name);
            
                al_draw_text(text, VERY_PALE_YELLOW, 12 * _WINDOW_WIDTH / 16,
                    (3.2 + i/ 2.0f) * _WINDOW_HEIGHT / 9, 0,
                    std::to_string(scores[i].moves).c_str());
            }
        }

    } catch (const std::runtime_error& e) {
        std::cerr << e.what();
    }
}

Score* GetHighScores(int n_discs, int& n_scores) {
    std::string filename(_BASE_SCORES_FILENAME);
    filename.append(std::to_string(n_discs));
    filename.append(".txt");

    return GetPreviousScores(filename.c_str(), n_scores);
}
