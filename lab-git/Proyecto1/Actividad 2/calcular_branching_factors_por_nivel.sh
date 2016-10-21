#!/bin/bash

# Nota: solo ejecutar si se encuentran en el directorio de trabajo los directorios
# con las tablas básicas de la actividad 1.

find hanoiPuzzle_Results/*.txt -exec bash -c '. branching_script.sh {} > {}_branching_factor.txt' \;

find npuzzle_Results/*.txt -exec bash -c '. branching_script.sh {} > {}_branching_factor.txt' \;

find pancakePuzzle_Results/*.txt -exec bash -c '. branching_script.sh {} > {}_branching_factor.txt' \;

find topSpinCompactPuzzle_Results/*.txt -exec bash -c '. branching_script.sh {} > {}_branching_factor.txt' \;

