Resultados
    
    Se corrieron los cinco algoritmos usando la siguiente orden:
    
        timeout --signal=SIGINT 10m ./main 0
    
    De esta manera se asegura una ejecución de diez minutos para cada uno.
    
    Sin la tabla de transposiciones
        
        Minimax-Maxmin: llega al nivel 18 y lo recorre en 426.556 segundos. 
        En él se alcanzó una tasa de 2.05429e+06 nodos por segundo.
        
        Negamax (Versión minimax): llega al nivel 19 y lo recorre en 40.344 segundos.
        En el último nivel alcanzado se logró una tasa de
        2.24687e+06 nodos por segundo
        
        Nagamax (Versión con alpha-beta pruning): llega al nivel 13 y lo
        recorre en 240.132 segundos. Se logró una tasa de 1.70707e+06 nodos
        por segundo en el último nivel alcanzado.
        
        Scout: llega al nivel 13 y lo recorre en 160.012 segundos.
        Logró una tasa de 1.73032e+06 nodos por segundo en el último nivel alcanzado.
        
        Negascout: llega al nivel 13 y lo recorre en 147.728 segundos. Logró una tasa de
        1.64211e+06 nodos por segundo en el último nivel alcanzado.
    
    Considerando al último nivel alcanzado y el tiempo de recorrido de dicho nivel,
    se tiene el siguiente orden de los algoritmos (de mejor a peos):
        
        Negascout, Scout, Negamax(alpha-beta), Minimax-Maxmin y Negamax(Minimax)

        Justificación
            
            b: factor de ramificación
            d: profundidad
            
            La complejidad formla de Nagascout y Scout son similares O(b^(d/2))
            La complejidad de Negamax con alpha beta pruning es O(b^d) en el 
            peor caso y O(b^(d/2)) en el mejor.
            La complejidad de Negamax sin pruning es O(b^d).
            Finalmente, la complejidad de Minimax-Maxmin es O(b^d)