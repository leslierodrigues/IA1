
Resultados
    
    Las implementaciones de los cinco algoritmos pedidos se encuentran en el
    archivo "main.cc". También fue implementada la tabla de transposiciones.

    Se implemento la version clásica de cada algoritmo, para la tabla de
    transposiciones se probaron varias tecnicas pero no se logro una mejora
    significativa para ninguno de los algoritmos (Aunque se logró que el
    tiempo necesario para correr ciertos niveles decreciera, no se logro
    que ninguno de los algoritmos llegara a nuevos niveles).

    La tabla de transposiciones se implementó con un tamaño fijo, dado por
    2*tt_threshold (Ya que tt_threshold es el tamaño de cada tabla), y para
    el regimen de reemplazo se utilizó un mecanismo "NEW" donde una vez que
    se llenara la tabla, cada nueva entrada reemplazaría a una de las más
    viejas. No se implementó nada más avanzado por la falta de librerías en
    C++ que soportaran colas de prioridades con cambio de prioridad (estas
    son implementadas en Boost, pero no en la librería estandar) que son
    vitales para la mayoria de las otras estrategias.

    También se implementó una opción en la tabla de transposiciones para 
    fijar la profundidad máxima en la cual se guardaran nodos, pero esto
    tampoco llego a ninguna mejora significativa. Esta profundidad puede
    ser cambiada con la constante DEPTH_TO_STORE definida en el main.
