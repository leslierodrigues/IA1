    
    
    Resultados Resumidos (Factor de Ramificación)
    
    Los factores de ramificación resumidos por problema se pueden encontrar
    en este arhivo:
    
        branching_factor_empirico_por_problema.txt
    
    Resultados con detalle (Factor de Ramificación)
    
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


    Resultados (Primer Nivel donde el Número de estados < Número de Nodos)
        
        Debemos saber el número de estados. Para esto se usó la información
        contenida en el director io ProblemDomains y las láminas del curso.
        
        Este número luego es comparado con la información de las tablas.
        En caso de que la información de las tablas no sea suficiente, se
        usa la tabla "branching_factor_empirico_por_problema.txt" para encontrar
        el factor de ramificación empírico y estimar el primer nivel que tiene
        más nodos hasta allí que estados.
        
            Número de estados del 11puzzle4x3 es (12!) = 239500800
                
                history_len=0 y nivel 18 con 290080335 nodos
                
                Para los demás history_len la primera profundidad buscada
                es mayor que la profundidad máxima del enunciado. Se puede
                estimar con los factores de ramificación. Si b es el estimado
                del factor de ramificación, entonces el nivel buscado es el primer n
                tal que (b^n - 239500800 > 0). Se encuentra lo siguiente por
                inspección: ((1.95925235231624487335)^29 - 239500800) = 56042371.1955
                Por tanto, para history_len = 1 y 2, se tiene que el primer nivel
                en el que hay más nodos que estados es el 29.
                
            Número de estados del pancake24 es (24!) = 6.204484e+23
                
                En este caso también se han de usar estimados. Se sigue
                un procedimiento similar al de arriba.
                
                Para history_len=0, se tiene b=23.00000000000000000000
                Luego, el primer n tal que (b^n - 6.204484e+23 > 0) se 
                encuentra por inspección: (23^18 - 6.204484e+23) = 2.6237025e+24  > 0
                Por tanto, n=18.
                
                Para history_len=1, se tiene b=22.16666666666666666666.
                Luego (b^n - 6.204484e+23 > 0)
                 ==> ((22.16666666666666666666)^18 -6.204484e+23) = 1.0491308e+24 > 0
                 Por tanto, n = 18.
                
                Para history_len=2, se tiene b=22.16535032748525727961. En este
                caso también se tiene n=18
                
            Número de estados del pancake28 es (28!) = 3.0488834e+29
                
                Para history_len=0, se tiene b=27.00000000000000000000
                Usando el mismo método se obtiene n=21, pues
                ((27^21)-3.0488834e+29) = 8.3967293e+29 > 0.
                
                Para history_len=1, se tiene b=26.16666666666666666666.
                Luego, n=21, pues 
                (((26.16666666666666666666)^21)-3.0488834e+29) = 2.8764998e+29 > 0
                
                Para history_len=2, se tiene b=26.16571762352635467321
                y nuevamente n=21.
                
            Número de estados del topSpin22-4 es (22!) = 1.1240007e+21
                
                Como arriba quedó suficientemente claro qué procedimiento
                se usó, sólo indicamos el valor del nivel.
                
                Para history_len=0, b=22.00000000000000000000
                ==> (((22.00000000000000000000)^16)-1.1240007e+21) = 1.8873608e+21 > 0
                ==> n=16
                
                Para history_len=1, b=12.57622786978279071803
                ==> (((12.57622786978279071803)^20)-1.1240007e+21) = 8.6710786e+21 > 0
                ==> n=20
                
                Para history_len=2, b=11.97374282910893670812
                ==> (((11.97374282910893670812)^20)-1.1240007e+21) = 8.6710786e+21 > 0
                ==> n=20
                
            Número de estados del topSpin26-4 es (26!) = 4.0329146e+26
                
                Como arriba quedó suficientemente claro qué procedimiento
                se usó, sólo indicamos el valor del nivel.
                
                Para history_len=0, b=26.00000000000000000000
                ==> (((26.00000000000000000000)^19)-4.0329146e+26) = 3.6317581e+26 > 0
                ==> n=19
                
                Para history_len=1, b=14.10270274416817896594
                ==> (((14.10270274416817896594)^24)-4.0329146e+26) = 3.4272172e+27 > 0
                ==> n=24
                
                Para history_len=2, b=13.41670396992781027522
                ==> (((13.41670396992781027522)^24)-4.0329146e+26) = 7.5415284e+26 > 0
                ==> n=24
            
            Número de estados del hanoi14-4 es (4^14) = 268435456
                
                Como arriba quedó suficientemente claro qué procedimiento
                se usó, sólo indicamos el valor del nivel.
                
                Para history_len=0, b=5.22924699786109842539
                ==> (((5.22924699786109842539)^12)-268435456) = 149654629.559 > 0
                ==> n=12
                En este caso, se puede usar la tabla de la actividad 1. Se 
                encuentra que el número de nodos a esa profundidad es 360382215.
                
                Para history_len=0, b=4.81026815433761566117
                ==> (((4.81026815433761566117)^13)-268435456) = 469809919.759 > 0
                ==> n=13
                
            Número de estados del hanoi16-4 es (4^16) = 4294967296
                
                En este caso, si se observa la tabla "branching_factor_empirico_por_problema.txt",
                se notará que no hay diferencias entre hanoi14-4 y hanoi16-4. Esto se
                debe a que la profundidad máxima usada no permite alcanzar los estados
                que permiten distinquir a estos problemas. Por lo tanto, si se
                usa la misma profundidad, se obtienen resultados iguales a los 
                de arriba.
        
        
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
    

