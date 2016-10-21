        
    Resultados ----------------------------------------------------------------
    
    Los resultados de haber ejecutado:
        - Las instancias de 28 panquecas con WIDA usando la heurística gap.
        - Las instancias 15-puzzle de Rich Korf con WIDA usando 
          heuristica Manhattan y PDB 5+5+5.
    El nombre de cada archivo contiene el nombre del problema y 
    el history_len usado. 
    
    Generación de resultados
    
    Ejecutar:         
        while read in; do echo "$in" | timeout --signal=SIGTERM 10m 
        ./<nombre_del_ejecutable> \ >> <archivo_de_resultados>;
         done < <archivo_de_intancias>
     
     en donde:
        
        <archivo_de_intancias>
            nombre del archivo que contiene las instancias
            
        <archivo_de_resultados>
            nombre del archivo que almacena los resultados correspondientes
            a las instancias procesadas
    
        <nombre_del_ejecutable>
            nombre del ejecutable generado al compilar
        
        timeout --signal=SIGTERM 10m ./hanoi_4_14.iter_deepening
            orden que permite ejecutar IDDFS para hanoi con un límite de 
            tiempo de 10 minutos. Si se pasa de este tiempo, se envía la señal
            SIGTERM, especificada como argumento allí.
        
        while read in; do echo "$in"
            lee cada línea obtenida a partir de "done < tower14_4_100_150.txt"
            y se la pasa a la variable "in". Luego le pasa esta variable a la
            orden de arriba como argumento.
    
    
    Abstracciones ------------------------------------------------------------
    
    Contiene las abtracciones utilizadas para generar los resultados 
    correspondientes a 15-puzzle con A* e IDA* con PDB 5+5+5.  
