

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
    

Descripción de generarClausulas.py

    REPRESENTACIÓN
    
        Para un ejemplo concreto de cómo se representa el tablero en el código
        se puede ver el documento llamado "tablero.pdf"
        
        Variables y Funciones más Importantes
        
            N : número de filas del tablero
            M : número de columnas del tablero
            
            tablero : matriz que guarda el número de segmentos (tablero[i][j])
                que debe tener cada celda (<i,j>)
            
            bordesDeCeldas : matriz que relaciona cada celda con sus cuatro
                segmentos. No se usa directamente.
            
            q(i,j,k) : función que retorna el nombre de la variable representante
                del segmento "k" de la celda <i,j>. El segmento "k" puede tener
                los valores: "n", "s", "e" y "w" (north, south, east and west)
            
            generarVariablesBordesDeCeldas() : genera los nombres de las variables
                que indican cuáles segmentos se usan
            
            z : matriz que guarda el nombre de la variable representante del
                tipo de celda. z[i][j] es la variable que indica si <i,j> es una
                celda externa o no.
            
            generarVariablesTipoDeCelda() : genera los nombres de las variables
                que indican el tipo de cada celda
            
            alcances : diccionario que devuelve el nombre de la variable que indica
                si el par de celdas que sirven como "key" al diccionario son
                alcanzables entre sí.
            
            generarVariablesAlcances() : genera los nombres de las variables
                que indican si dos celdas son alcanzables entre sí.
            
            r((i1,j1),(i2,j2)) : devuelve el nombre de la variable que indica
                si la celda <i2,j2> es alcanzable desde la celda <i1,j1>
            
            negar(nombreVariable) : devuelve el nombre de la variable, pero negado
            
            clausulas : lista cuyos elementos son las cláusulas que serán la entrada
                de minisat. Cada cláusula tiene forma de un string generado con
                ayuda de las variables y métodos mencionados arriba.
            
            Archivos Temporales: 
                
                inputSatSolver.txt : guarda la entrada que usará directamente 
                    minisat cuando sea invocado desde el script. Contiene
                    un header y las cláusulas construidas.
                
                outputSatSolver.txt : guarda la salida de minisat.
            
            
    CLÁUSULAS
        
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

        Descripción de los Métodos Asociados a las Cláusulas:
            
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
                
                -Para cada par de celdas alcanzables, si existe una tercera que es
                adyacente a la segunda, entonces ésta puede se alcanzada por 
                la primera y la segunda
                
                - Sin embargo, una definicion inductiva de alcanzable no nos 
                sirve para la codificacion logica, puesto solo se dan 
                implicaciones que no piden nada concreto del modelo.
            
            clausulasTipo4 (No pudimos asegurar que sólo haya un único bucle)
            
                -Las celdas internas se pueden alcanzar entre sí
                -Las celdas de tipo distinto no se pueden alcanzar entre sí
            
            clausulasTipo5
            
                -Las esquinas no puede tener tres segmentos o más
            
            clausulasTipo6
            
                -Las esquinas no pueden tener un único segmento
            
            


    RESULTADOS
        
        Se corrío el generarClausulas.py con todas la líneas del archivo "input.txt"
        y se guardaron los resultados en el archivo "output.txt"
        
        Todos los casos de prueba provistos eran satisfacibles salvo por el 
        siguiente: "5 5 .202. .3.2. .2..3 ..... ....4"

        No se asegura que exista un único bucle.
    


SCRIPTS ADICIONALES

Script Auxiliar (recorrerInput.sh)
    
    Requerimientos 
        - Paquete de Minisat en Linux
        - Los siquientes Archivos en un mismo directorio:
            - generarClausulas.py
            - recorrerInput.sh
            - input.txt (archivo cuyas líneas son entradas válidas de generarClausulas.py)
    
    Ejecución
    
        ./recorrerInput.sh > <Nombre de Archivo de Salida>
        
    Resultado
    
        Se obtienen pares de líneas con el input en la primera y en la segunda
        el resultado del solver.
        

Script Auxiliar (graficar.py)

    Descripción
    
        Pequeno programa auxiliar que usa matplotlib para graficar el tablero 
        a partir de un input y un resultado, por defecto, el archivo principal 
        guarda en testfile los datos necesarios para graficar el problema en 
        caso de ser satisfacible
    
    Requerimientos
    
        -Python3
        -Tener instaladas las librerías de python3:
            - matplotlib
            - numpy
        -Input del tablero. Ejemplo: "5 5 .2.2. .2.1. 30202 3.... ...2."
        -Output de Minisat para el input de arriba. 
            Ejemplo: "5 5 11011 101101 10000 011101 10100 100001 10101 011110 10001 101101 11011"
        
    Ejecución
        
        1- Se debe usar la siguiente orden:
            python3 graficar.py
        2- Se debe introducir la información del tablero sobre el número de
            segmentos por celda.
        3- Se debe introducir la información del tablero sobre los segmentos
            que satisfacen las clausulas.

    Resultados
        
        Se muestra una vista con el tablero dibujado con una asignación
        que satisface las restricciones.


