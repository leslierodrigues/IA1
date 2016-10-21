    
    Resultados
    
    Los resultados de haber ejecutado las listas de instancias con IDDFS
    y el árbol con menor factor de ramificación se encuentran en el 
    directorio "Resultados." El nombre de cada archivo es descriptivo del
    history_len usado y las dimensiones del problema.
    
    Ejemplo de generación de resultados
    
    EL siguiente es un ejemplo de cómo se computaron los resultados. En este
    caso, se usó un grupo de instancias para el hanoiPuzzle para dividir
    el trabajo entre varias máquinas
    
    while read in; do echo "$in" | timeout --signal=SIGTERM 10m ./hanoi_4_14.iter_deepening \
        >> resultados_tower14_4_h1_iter_deep_100_150.txt; done < tower14_4_100_150.txt
     
     en donde:
        
        tower14_4_100_150.txt
            contiene un grupo de instancias
            
        resultados_tower14_4_h1_iter_deep_100_150.txt  
            donde se guardan los resultados
        
        timeout --signal=SIGTERM 10m ./hanoi_4_14.iter_deepening
            orden que permite ejecutar IDDFS para hanoi con un límite de 
            tiempo de 10 minutos. Si se pasa de este tiempo, se envía la señal
            SIGTERM, especificada como argumento allí.
        
        while read in; do echo "$in"
            lee cada línea obtenida a partir de "done < tower14_4_100_150.txt"
            y se la pasa a la variable "in". Luego le pasa esta variable a la
            orden de arriba como argumento.
    
    
