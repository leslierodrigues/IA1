N=5
numeroColumnas = 5
M=5
numeroFilas = 5

# Ejemplo que dio Blai
mapaCeldaRestriccionNumeroBordes = {(0,1) : 2, (0,2) : 2, (0,4) : 3
                                   ,(1,1) : 2
                                   ,(2,0) : 3, (2,1) : 2
                                   ,(3,0) : 1, (3,4) : 3
                                   ,(4,1) : 2, (4,2) : 2, (4,3) : 3}


def negar(nombreVariable) :
    if nombreVariable == "" :
        return ""
    return "-"+nombreVariable 
 

'''
Cláusulas tipo 0
----------------

Cada segmento interno de la retícula es referenciado por dos celdas distintas.
Por ejemplo, el segmento vertical entre los puntos (1,1) y (1,2) corresponde
al segmento este de la celda c(1,2) y al segmento oeste de la celda c(2,2).

Para obtener una interpretación consistente debemos forzar que las dos
proposiciones q(c,d) que refieren al mismo segmento tengan la misma
interpretación:

Para toda celda c=(i,j) con 1 <= i < N y 1 <= j <= M,

q(i,j,e) <=> q(i+1,j,w)

Para toda celda c=(i,j) con 1 <= i <= N y 1 <= j < M,

q(i,j,n) <=> q(i,j+1,s)
'''


