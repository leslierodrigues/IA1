

Requerimientos
    
    - Paquete de Minisat en Linux
    - generarClausulas.py


Ejecución

    Para ejecutar el script "generarClausulas.py" se ha de usar la siguiente
    orden:
        
        python generarClausulas.py <Línea de Entrada>
    
    donde la línea de entrada tiene el siguiente formato
        
        <Número de Filas> <Número de Columnas> (([0-3.]{Número de Columnas})\s){Número de Filas}
        
        Ejemplo: 5 5 .2.2. .2.1. 30202 3.... ...2.
        
    
    La salida indica si el caso pasado como argumento es satisfacible.
    Ejemplo para el caso de arriba:
        
        "SATISFIABLE
        5 5 11011 101101 10000 011101 10100 100001 10101 011110 10001 101101 11011"
    
Script Auxiliar
    
    Requerimientos 
        - Paquete de Minisat en Linux
        - Los siquientes Archivos en un mismo directorio:
            - generarClausulas.py
            - recorrerInput.sh
            - input.txt (archivo cuyas líneas son entradas válidas de generarClausulas.py)
    
    Ejecución
    
        . recorrerInput > <Nombre de Archivo de Salida>
        
    Resultado
    
        Se obtienen pares de líneas con el input en la primera y en la segunda
        el resultado del solver.
        

    CLAUSULAS
        
        - Sólo se permiten puntos con cero o dos líneas
        - Sólo se permiten líneas cerradas
        - Si un lado de una celda se usa, entonces el lado correspondiente de la
            celda adyacente también se usa
        

    RESULTADOS
    
        Todos los casos de prueba provistos eran satisfacibles salvo por el 
        siguiente: "5 5 .202. .3.2. .2..3 ..... ....4"
        
        Esto se debe a la presencia del 4 allí.
        
        No se asegura que exista un único bucle.
    
    
