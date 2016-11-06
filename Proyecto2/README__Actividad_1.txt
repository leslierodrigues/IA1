

Resultados
    
    Para completar la representación del juego, fue necesario incluir la 
    verificación de las diagonales "dia1" y "dia2" en el método "outflank".
    También se hizo esto en el método "move" con el fin de rellenar las diagonales
    para las que "outflank" haya arrojado "true" en una jugada.

Justificación
    
    Para poder decidir cómo completar la representación fue necesario 
    entender el funcionamiento de "rows". En primer lugar, cada
    sub arrreglo de rows corresponde a una celda del tablero si se
    excluye a las cuatro celdas que están ocupadas inicialmente. Como los
    jugadores nunca jugarán una pieza en ellas, simplemente no es necesario
    tomarlas en cuenta aquí. Esto significa que a todas las celdas
    --menos las cuatro iniciales-- están enumeradas con un índice de "rows".
    Este arreglo "rows" se puede ver como una función que le asigna a cada
    celda no inicial su respectiva fila en forma de un arreglo. Por esta razón,
    se repiten de seis en seis estos sub arreglos.
    
    De esto se desprende la representación del tablero:
    
        4	5	6	7	8	9
        10	11	12	13	14	15
        16	17	0	1	18	19
        20	21	2	3	22	23
        24	25	26	27	28	29
        30	31	32	33	34	35
            
            en donde se puede notar que las celdas iniciales están en
            el centro del tablero. Como se usa el arreglo "rows", es
            necesario restarle 4 a "pos" si este no representa una de 
            estas celdas iniciales. Los elmentos "-1" en los subarreglos
            de "rows" ayudan a detener los recorridos. Esto ocurre de 
            manera similar en "cols", "dia1" y "dia2".
    
    
    En segundo lugar, se tiene que entender cómo se guarda la información
    sobre el color de las celdas ocupadas en el tablero. Esto se logra con
    los campos del estado: t_, free_ y pos_. Nuevamente, como las cuatro celdas
    iniciales (0, 1, 2 y 3) ya están ocupadas, sólo es necesario trabajar con 
    las 32 restantes. Por eso, los primeros 32 bits de free_ indican si su respectiva 
    celda no inicial está ocupada. Si la celda x está ocupada y el bit x de pos_ está 
    prendido, entonces allí hay una ficha negra. Si el bit x de pos_ está 
    apagado y el sendo bit de free_ indica que está ocupado, 
    entonces allí hay una blanca. Si se quiere saber el color de
    las celdas iniciales, entonces es necesario consultar los bits de t_.
    En este caso no es menester consultar a free_ pues ya se sabe que
    estas celdas están ocupadas.
    
    Finalmente, cuando un jugador decide jugar su pieza en una celda, primero
    se usa "outflank" para determinar si esta jugada es válida. Esto
    se logra recorriendo primero desde "pos" hacia su derecha. Se termina 
    este recorrido cuando se encuentre una celda vacía o una celda del mismo
    color que representa al jugador actual. Si se encuentra una celda vacía,
    "outflank" determina que la jugada no es válida. Si se encuentra al menos
    una pieza del jugador contrario y luego otra del jugador actual, entonces
    outflank se detiene allí y determina que la jugada se puede realizar. 
    De fallar en el primer intento esto, "outflank" intenta recorrer hacia la 
    izquierda de "pos" siguiendo un comportamiento similar. Estos recorridos
    se hacen de manera similar para "cols", la cual representa permite verificar
    las columnas.
    
    El método "move" se comporta de manera similar a "outflank". Sin embargo,
    a diferencia de éste, "move" llama al método "set_color" cuando determina
    que la jugada es válida para cambiarles el color a las celdas atrapadas.
    
    Tomando en cuenta lo anterior, sólo faltaba hacer estos recorridos en 
    ambos sentidos para las diagonales en los métodos "move" y "outflank". 
    Adicionalmente, se indicaba dónde colocar este código a través del
    comentario "// [CHECK OVER DIAGONALS REMOVED]"
