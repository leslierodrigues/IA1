    
    
    Resultados Resumidos
    
    Los factores de ramificación resumidos por problema se pueden encontrar
    en este arhivo:
    
        branching_factor_empirico_por_problema.txt
    
    Resultados con detalle
    
    Los factores de ramificación detallados pueden encontrarse en los
    siguientes archivos:
    
        pancakePuzzle_Results/pancake16_history0_depth6.txt_branching_factor.txt
        pancakePuzzle_Results/pancake16_history1_depth6.txt_branching_factor.txt
        pancakePuzzle_Results/pancake16_history2_depth6.txt_branching_factor.txt
        pancakePuzzle_Results/pancake24_history0_depth6.txt_branching_factor.txt
        pancakePuzzle_Results/pancake24_history1_depth6.txt_branching_factor.txt
        pancakePuzzle_Results/pancake24_history2_depth6.txt_branching_factor.txt
        pancakePuzzle_Results/pancake28_history0_depth6.txt_branching_factor.txt
        pancakePuzzle_Results/pancake28_history1_depth6.txt_branching_factor.txt
        pancakePuzzle_Results/pancake28_history2_depth6.txt_branching_factor.txt

        topSpinCompactPuzzle_Results/topSpinCompactPuzzle16_4_history0_depth7.txt_branching_factor.txt
        topSpinCompactPuzzle_Results/topSpinCompactPuzzle16_4_history1_depth7.txt_branching_factor.txt
        topSpinCompactPuzzle_Results/topSpinCompactPuzzle16_4_history2_depth7.txt_branching_factor.txt
        topSpinCompactPuzzle_Results/topSpinCompactPuzzle22_4_history0_depth7.txt_branching_factor.txt
        topSpinCompactPuzzle_Results/topSpinCompactPuzzle22_4_history1_depth7.txt_branching_factor.txt
        topSpinCompactPuzzle_Results/topSpinCompactPuzzle22_4_history2_depth7.txt_branching_factor.txt
        topSpinCompactPuzzle_Results/topSpinCompactPuzzle26_4_history0_depth7.txt_branching_factor.txt
        topSpinCompactPuzzle_Results/topSpinCompactPuzzle26_4_history1_depth7.txt_branching_factor.txt
        topSpinCompactPuzzle_Results/topSpinCompactPuzzle26_4_history2_depth7.txt_branching_factor.txt

        npuzzle_Results/npuzzle4x3_history0_depth20.txt_branching_factor.txt
        npuzzle_Results/npuzzle4x3_history1_depth20.txt_branching_factor.txt
        npuzzle_Results/npuzzle4x3_history2_depth20.txt_branching_factor.txt
        npuzzle_Results/npuzzle4x4_history0_depth20.txt_branching_factor.txt
        npuzzle_Results/npuzzle4x4_history1_depth20.txt_branching_factor.txt
        npuzzle_Results/npuzzle4x4_history2_depth20.txt_branching_factor.txt

        hanoiPuzzle_Results/hanoiPuzzle_4P_14D_history0_depth12.txt_branching_factor.txt
        hanoiPuzzle_Results/hanoiPuzzle_4P_14D_history1_depth12.txt_branching_factor.txt
        hanoiPuzzle_Results/hanoiPuzzle_4P_16D_history0_depth12.txt_branching_factor.txt
        hanoiPuzzle_Results/hanoiPuzzle_4P_16D_history1_depth12.txt_branching_factor.txt

    Scripts
    
    calcular_todos_los_branching_factors.sh archivo_de_salida.txt
        
        Este script construye la tabla de resumen con los factores de
        ramificación promedio de cada problema. Puede verse un output
        inusual si hay otros archivos en los directorios de resultados
        de la actividad 1.
        
    
    branching_script.sh tabla_básica_de_actividad_1.txt
        
        Este script construye una tabla con el factor de ramificación por
        nivel y al final muestra el factor de ramificación promedio entre
        todos los niveles.
    
    calcular_branching_factors_por_nivel.sh
        
        Este script asume que se encuentran en el directorio de trabajo los
        directorios de resultados de la actividad 1 y corre para cada tabla
        básica el script "branching_script.sh".
    

