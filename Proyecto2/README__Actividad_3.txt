Resultados
    
    Se corrieron los cinco algoritmos usando la siguiente orden:
    
        timeout --signal=SIGINT 10m ./main 0
    
    De esta manera se asegura una ejecución de diez minutos para cada uno.
    
    Sin la tabla de transposiciones
        
        Minimax-Maxmin: llega al nivel 18 y lo recorre en 426.556 segundos. 
        
        Negamax (Versión minimax): llega al nivel 18 y lo recorre en 394.535 segundos.
        
        Nagamax (Versión con alpha-beta pruning): llega al nivel 13 y lo
        recorre en 240.132 segundos
        
        Scout: llega al nivel 12 y lo recorre en 431.878 segundos.
        
        Negascout: llega al nivel 12 y lo recorre en 374.281 segundos.
    
    Considerando al último nivel alcanzado y el tiempo de recorrido de dicho nivel,
    se tiene el siguiente orden de los algoritmos (de mejor a peos):
        
        Negascout, Scout, Negamax(alpha-beta), Negamax(Minimax), Minimax-Maxmin

        Justificación
            
            El orden esta dado por la cantidad de poda que se le hace al arbol,
            es obvio que entre mas nodos se poden, mas rapida sera la busqueda.

            Además, aunque Negamax (Minimax) y Minimax-maxmin sean los mismos
            algoritmos, hay una pequeña ganancia en eficiencia en el primero
            gracias a que no utiliza doble recursión sino recursión simple.

            Formalmente las complejidades son:
                Para Negascout y Scout son similares O(b^(d/2))
                Para Negamax con alpha beta pruning es O(b^d) en el 
                peor caso y O(b^(d/2)) en el mejor.
                Para Negamax sin pruning y Minimax-Maxmin es O(b^d).
                
                con:
                b: factor de ramificación
                d: profundidad
