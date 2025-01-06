#!/bin/bash

EXECUTABLE="hanoi"
CXX="g++"
STD="-std=c++11"

SRC="main.cpp Juego.cpp Menu.cpp Instrucciones.cpp Creditos.cpp Scores.cpp Utileria.cpp Disco_y_Estaca.cpp Selector_flecha.cpp"

# Allegro libraries and macOS frameworks
LIBS="-lallegro_main -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec"
FRAMEWORKS="-framework OpenGL -framework IOKit -framework Cocoa"

# Clean previous builds
if [ -f "$EXECUTABLE" ]; then
    echo "Cleaning previous build..."
    rm -f $EXECUTABLE
fi

echo "Compiling..."
$CXX $STD -o $EXECUTABLE $SRC $LIBS $FRAMEWORKS

if [ $? -eq 0 ]; then
    echo "Compilation successful."

    echo "Running the program..."
    ./$EXECUTABLE
else
    echo "Compilation failed."
fi
