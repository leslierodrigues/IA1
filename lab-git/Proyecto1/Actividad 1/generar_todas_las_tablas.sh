#!/bin/bash

. generar_tablas.sh hanoiPuzzle_Results/hanoiPuzzle_4P_14D_history0_depth12.txt hanoiPuzzle_Results/hanoiPuzzle_4P_14D_history1_depth12.txt | head -n -1 > hanoiPuzzle_Results/hanoiPuzzle_4P_14D_depth12_TABLA.txt

. generar_tablas.sh hanoiPuzzle_Results/hanoiPuzzle_4P_16D_history0_depth12.txt hanoiPuzzle_Results/hanoiPuzzle_4P_16D_history1_depth12.txt | head -n -1 > hanoiPuzzle_Results/hanoiPuzzle_4P_16D_depth12_TABLA.txt

. generar_tablas.sh npuzzle_Results/npuzzle4x4_history0_depth20.txt npuzzle_Results/npuzzle4x4_history1_depth20.txt npuzzle_Results/npuzzle4x4_history2_depth20.txt | head -n -1 > npuzzle_Results/npuzzle4x4_depth20_TABLA.txt

. generar_tablas.sh topSpinCompactPuzzle_Results/topSpinCompactPuzzle22_4_history0_depth7.txt topSpinCompactPuzzle_Results/topSpinCompactPuzzle22_4_history1_depth7.txt topSpinCompactPuzzle_Results/topSpinCompactPuzzle22_4_history2_depth7.txt | head -n -1 > topSpinCompactPuzzle_Results/topSpinCompactPuzzle22_4_depth7_TABLA.txt

. generar_tablas.sh topSpinCompactPuzzle_Results/topSpinCompactPuzzle26_4_history0_depth7.txt topSpinCompactPuzzle_Results/topSpinCompactPuzzle26_4_history1_depth7.txt topSpinCompactPuzzle_Results/topSpinCompactPuzzle26_4_history2_depth7.txt | head -n -1 > topSpinCompactPuzzle_Results/topSpinCompactPuzzle26_4_depth7_TABLA.txt


. generar_tablas.sh pancakePuzzle_Results/pancake24_history0_depth6.txt pancakePuzzle_Results/pancake24_history1_depth6.txt pancakePuzzle_Results/pancake24_history2_depth6.txt | head -n -1 > pancakePuzzle_Results/pancake24_depth6_TABLA.txt

. generar_tablas.sh pancakePuzzle_Results/pancake28_history0_depth6.txt pancakePuzzle_Results/pancake28_history1_depth6.txt pancakePuzzle_Results/pancake28_history2_depth6.txt | head -n -1 > pancakePuzzle_Results/pancake26_depth6_TABLA.txt
