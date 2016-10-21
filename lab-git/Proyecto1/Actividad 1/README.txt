
    Resultados
    
    Los resultados se pueden encontrar en los siguientes archivos:
    
        /topSpinCompactPuzzle_Results/topSpinCompactPuzzle22_4_depth7_TABLA.txt
        /topSpinCompactPuzzle_Results/topSpinCompactPuzzle26_4_depth7_TABLA.txt
        /npuzzle_Results/npuzzle4x3_depth20_TABLA.txt
        /npuzzle_Results/npuzzle4x4_depth20_TABLA.txt
        /hanoiPuz   zle_Results/hanoiPuzzle_4P_14D_depth12_TABLA.txt
        /hanoiPuzzle_Results/hanoiPuzzle_4P_16D_depth12_TABLA.txt
        /pancakePuzzle_Results/pancake24_depth6_TABLA.txt
        /pancakePuzzle_Results/pancake26_depth6_TABLA.txt

    
    Este directorio contiene el código fuente del algoritmo DFS y un Makefile.
    Todos los modelos de estados guardados en el primer nivel del directorio 
    "Proyecto1/Problemas" pueden compilarse con dicho algoritmo para generar 
    ejecutables específicos al problema seleccionado.
    
    Lista de Problemas Disponibles:
        
        hanoi_4_14.psvn
        hanoi_4_16.psvn
        hanoiPuzzle14_4.psvn
        hanoiPuzzle16_4.psvn
        npuzzle4x3.psvn
        npuzzle4x4.psvn
        pancakePuzzle16.psvn
        pancakePuzzle24.psvn
        pancakePuzzle28.psvn
        topSpinCompactPuzzle16_4.psvn
        topSpinCompactPuzzle22_4.psvn
        topSpinCompactPuzzle26_4.psvn
    
    Directorios de Resultados
        
    Estos directorios contienen los archivos de tipo txt con las tablas resultantes
    de correr dfs con cada modelo. Adicionalmente, éstos contienen archivos cuyo
    nombre tiene el sufijo "TABLA", lo que indica que es la tabla con el formato
    solicitado para el problema. Éstas últimas tienen en un mismo archivo el 
    número de nodos por nivel y por tamaño de sufijo de eliminación (history_len).
        
        hanoiPuzzle_Results/
        npuzzle_Results/
        pancakePuzzle_Results/
        topSpinCompactPuzzle_Results/
    
    
    Ejemplo de Ejecución
    
    En primer lugar, se ha de decidir el valor del parámetro "history_len" en
    el makefile para el modelo elegido. Luego se ejecutan las siguientes
    órdenes:
        
        make clean
        make npuzzle4x3.dfs
        ./npuzzle4x3.dfs
        
    En este momento el programa le solicita al usuario el número máximo de
    niveles a usar.
    
    Luego de terminar imprime una tabla con el número de nodos por nivel.
    Estas tablas fueron generadas por cada variación de los puzzles y fueron
    guardadas con nombres informativos en los directorios de resultados.
    
    
    Scripts
    
    Los scripts de bash contenidos en este directorio sólo fueron herramientas
    usadas para construir las tablas de resumen cuyo nombre tiene el sufijo
    "TABLA". No se espera que sean ejecutados sin tener todas las tablas
    generadas por el algoritmo por cada problema. Los scripts disponibles
    son:
        
        generar_tablas.sh tabla1 tabla2 [tabla3]
            
            Este script recibe como argumento a las tablas básicas generadas
            por sendas corridas de dfs para un mismo problema y distintos
            tamaños de sufijos (history_len). Se asume que el orden de las
            tablas representa el tamaño del history_len. Luego de ejecutarse,
            se genera la tabla de resumen con el formato pedido para esta
            actividad.
            
        generar_todas_las_tablas.sh
            
            Asume que se han generardo todas las tablas básicas para cada
            problema y están guardadas en su respectivo directorio de 
            resultados con un nombre preciso.
            Este script sólo ejecuta múltiples veces el script generar_tablas.sh
            hasta obtener todas las tablas de resumen (tienen TABLA.txt como 
            sufijo en sus nombres.)


