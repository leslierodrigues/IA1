        
    Resultados ----------------------------------------------------------------
    
    Los resultados de haber ejecutado:
        - Las instancias de 28 panquecas con WIDA usando la heurística gap.
        - Las instancias 15-puzzle de Rich Korf con WIDA usando 
          heuristica Manhattan y PDB 5+5+5.
    El nombre de cada archivo contiene el nombre del problema y 
    el history_len usado. 
    
    Generación de resultados
    
     Para compilar un programa, use:
        - con las heurísticas gap y manhattan
            make <nombre_psvn>.<nombre_cpp>.<gap/manhattan>        
        - con PDB 5 5 5
            make <nombre_psvn>.<nombre_cpp>

    en donde:
        <nombre_psvn> 
            nombre del archivo psvn 
        <nombre_cpp>
            nombre del archivo C++ correspondiente al algoritmo que 
            se desea utilizar.
                a_star     : para A*
                ida_star   : para IDA*
                a_star_pdb : para A* con PDB 5+5+5
                a_star_pdb : para IDA* con PDB 5+5+5

    (El history_len se debe cambiar a mano en el makefile)
    
    Se uso ulimit -Sv 2000000 para calcular cada resultado, esto limita
    la memoria virtual disponible para el proceso a 2GB (es decir, como
    maximo va a tomar 2 gb de ram y no va a hacer swap con el disco para
    conseguir mas.)

    Ejecutar:         
        while read in; do echo "$in" | timeout --signal=SIGTERM 10m 
        ./<nombre_del_ejecutable> >> <archivo_de_resultados>;
         done < <archivo_de_intancias>
     
     en donde:
        
        <archivo_de_intancias>
            nombre del archivo que contiene las instancias
            
        <archivo_de_resultados>
            nombre del archivo que almacena los resultados correspondientes
            a las instancias procesadas
    
        <nombre_del_ejecutable>
            nombre del ejecutable generado al compilar
        
        timeout --signal=SIGTERM 10m ./<nombre_del_ejecutable>
            orden que permite ejecutar el algoritmo en el ejecutable con un
            tiempo de 10 minutos. Si se pasa de este tiempo, se envía la señal
            SIGTERM, especificada como argumento allí.
        
        while read in; do echo "$in"
            lee cada línea obtenida a partir de "done < <archivo_de_instancias>"
            y se la pasa a la variable "in". Luego le pasa esta variable a la
            orden de arriba como argumento.
    
    Puesto que no se puede detectar la heuristica ni el dominio del problema
    (Al menos no sin recurrir a ifdefs de C) estas son colocadas en un valor
    default que se puede cambiar facilmente

    Abstracciones ------------------------------------------------------------
    
    Contiene las abtracciones utilizadas para generar los resultados 
    correspondientes a 15-puzzle con A* e IDA* con PDB 5+5+5.  

    Para generar los PDBs de esto, solo se debe usar el comando

    make <nombre_problema>/<nombretxt>.pdb

    En el caso del PDB 5+5+5 se deben generar

    make npuzzle4x4/grupo1.pdb
    make npuzzle4x4/grupo2.pdb
    make npuzzle4x4/grupo3.pdb

    para generar los 3 pdbs necesarios.

    make clean limpiara la carpeta y dejara solo los .txt
