

Requerimientos
    
    - Paquete de Minisat en Linux
    
        Para instalar Minisat en linux, se necesita ejecutar la siguiente orden:
            
            sudo apt-get install minisat
    
    - generarClausulas.py


Ejecución

    Para ejecutar el script "generarClausulas.py" se ha de usar la siguiente
    orden:
        
        python generarClausulas.py <Línea de Entrada>
    
    donde la línea de entrada tiene el siguiente formato
        
        <Número de Filas> <Número de Columnas> (([0-4.]{Número de Columnas})\s){Número de Filas}
        
        Ejemplo: "5 5 .2.2. .2.1. 30202 3.... ...2."
        
    
    La salida indica si el caso pasado como argumento es satisfacible.
    Ejemplo para el caso de arriba:
        
        "5 5 11011 101101 10000 011101 10100 100001 10101 011110 10001 101101 11011"
    
    De no ser satisfacible, se genera la siguiente salida:
        
        5 5 Insatisfacible.
    
Script Auxiliar
    
    Requerimientos 
        - Paquete de Minisat en Linux
        - Los siquientes Archivos en un mismo directorio:
            - generarClausulas.py
            - recorrerInput.sh
            - input.txt (archivo cuyas líneas son entradas válidas de generarClausulas.py)
    
    Ejecución
    
        ./recorrerInput.sh <Nombre de Archivo de Salida>
        
    Resultado
    
        Se obtienen pares de líneas con el input en la primera y en la segunda
        el resultado del solver.
        

    CLAUSULAS
        
        - Sólo se permiten puntos con cero o dos líneas
        - Sólo se permiten líneas cerradas
        - Si un lado de una celda se usa, entonces el lado correspondiente de la
            celda adyacente también se usa
        - Cada celda debe tener el número de bordes que le corresponden
        - Las celdas son internas o externas, y no ambas
        - Las celdas del mismo tipo (externa o unterna) son alcanzables entre sí:
          Cabe destacar que no pudimos asegurar que sólo haya un bucle.
        - Las celdas del borde que no tengan líneas en su frontera con el borde
             son externas.

        Descripción de los Métodos Asociados a las Clausulas:
            
            clausulasTipo0
                
                -Si una celda tiene un segmento, entonces la celda adyacente
                también tiene el segmento correspondiente
            
            clausulasTipo1
                
                -Se asegura que cada celda tenga el número de segmentos
                que indica la entrada del programa
            
            clausulasTipo2
                
                -Las celdas de la frontera que no tengan segmentos del lado del
                borde externo son de tipo exterior.
                
                -Las celdas alcanzables desde otras celdas exteriores son también
                exteriores
                
            clausulasTipo3 (No pudimos asegurar que sólo haya un único bucle)
            
                -Las celdas que no tengan segmentos entre sí son alcanzables
                
                -Para cada par de celdas alcanzables existe una tercera que es
                adyacente a la segunda y puede alcanzarla
            
            clausulasTipo4 (No pudimos asegurar que sólo haya un único bucle)
            
                -Las celdas del mismo tipo se pueden alcanzar entre sí
                -Las celdas de tipo distinto no se pueden alcanzar entre sí
            
            clausulasTipo5
            
                -Las esquinas no puede tener tres segmentos o más
            
            clausulasTipo6
            
                -Las esquinas no pueden tener un único segmento
            
            

    RESULTADOS
    
        Todos los casos de prueba provistos eran satisfacibles salvo por el 
        siguiente: "5 5 .202. .3.2. .2..3 ..... ....4"
        
        
        No se asegura que exista un único bucle.
    
    
