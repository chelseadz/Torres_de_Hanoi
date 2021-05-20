/*****************************************************************//**
 * \file   Juego.cpp
 * \brief  Implementaciones de Juego.h
 * 
 * \author Equipo Rocket
 * \date   3/05/2021
 *********************************************************************/

#include "Juego.h"
#include "Disco_y_Estaca.h"



void Juego(ALLEGRO_EVENT_QUEUE* queue) {

	//Solo para probar
    int num = 3;


    Estaca Prueba(_WINDOW_WIDTH / 2, 8 * _WINDOW_HEIGTH / 9);

    Prueba.Initialize_stakes(300, 20, 10);
    Prueba.numDisks(num);

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

            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            Prueba.PrintRod();

            al_flip_display();

            redraw = false;
        }
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
    int color_pruebas = 10;
    double ShrinkFactor = (disk_width / 2) * (0.1);
    for (int i = 1; i <= numDisks; i++) {
        al_draw_filled_rectangle(((-disk_width)/2) - (1-i)*ShrinkFactor + pos_x, -(i - 1) * disk_height + pos_y, ((disk_width) / 2) + (1 - i) * ShrinkFactor + pos_x, -i*disk_height + pos_y, al_map_rgba_f(0.1*i, 0.05*i, 0.5, 0.3));
    }
    

}
