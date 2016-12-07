N=5 #Filas
numeroColumnas = 5
M=5 #Columnas
numeroFilas = 5

tablero = [] #Definido para que sea una global


# Lee una linea.
def leerLinea():
	linea = input()
	datos = linea.split()
	N = int(datos[0])
	numeroFilas = N
	M = int(datos[1])
	numeroColumnas = M

	# -1 indica que no hay nada
	tablero = [[-1 for i in range(M)] for i in range(N)] 

	matriz = datos[2:]

	for i in range(len(matriz)):
		for j in range(len(matriz[i])):
			tablero[i][j] = -1 if matriz[i][j] == '.' else int(matriz[i][j])


# Ejemplo que dio Blai
mapaCeldaRestriccionNumeroBordes = {(0,1) : 2, (0,2) : 2, (0,4) : 3
                                   ,(1,1) : 2
                                   ,(2,0) : 3, (2,1) : 2
                                   ,(3,0) : 1, (3,3) : 0, (3,4) : 3
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

#  bordesDeCeldas es un arreglo de 3 dimensiones 
#  1era dimension: fila en la que se encuentra la celda 
#  2da dimension: columna en la que se encuentra la celda 
#  3era dimension: borde de la celda
#
#  bordesDeCeldas[i][j] es una arreglo de tamano 4 que corresponden a cada una
#                       de las lineas que bordean la celda, en el siguiente orden:
#                       norte, sur, este, oeste
            
bordesDeCeldas = [[[]]]


