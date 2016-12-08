

#  bordesDeCeldas,es un arreglo de 3 dimensiones 
#  1era dimension: fila en la que se encuentra la celda 
#  2da dimension: columna en la que se encuentra la celda 
#  3era dimension: borde de la celda
#
#  bordesDeCeldas[i][j] es una arreglo de tamano 4 que corresponden a cada una
#                       de las lineas que bordean la celda, en el siguiente orden:
#                       norte, sur, este, oeste
bordesDeCeldas = []

N=5 #Filas
numeroColumnas = 5
M=5 #Columnas
numeroFilas = 5

tablero = [] #Definido para que sea una global
clausulas = [] # Variable global que almacena las clausulas

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

# Niega una variable
def negar(nombreVariable) :
    if nombreVariable == "" :
        return ""
    return "-" + nombreVariable 

# equivalente: Dadas dos variables var1 y var2, que representan booleanos,
# detemina si son equivalentes.
# 
# Si ambas comienzan con '-' o ninguna lo hace, entonces son equivalentes. 
 
def equivalente(var1,var2):
    return (var1[0]== '-' and var1[0] == var2[0]) or (var1[0] != '-'and var2[0] != var1[0])
        

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

# generarVariablesBordesDeCeldas es una funcion que genera una variable
# por cada borde una celda. 
# Siendo generadas 4 x numero de celdas
#

def generarVariablesBordesDeCeldas():
    variable = 1
    # -1 indica que no hay nada
    
    bordesDeCeldas = [[[0 for k in range(4)] for j in range(M)] for i in range(N)]              
    for i in range(N):
        for j in range(M):
            for k in range(4):
                bordesDeCeldas[i][j][k] = str(variable)
                variable+=1
                   
    return bordesDeCeldas

# q, funcion que retorna una variable correspondiente a la unformacion dada
#
# i : numero de fila en la que esta la celda
# j : numero de columna en la que esta la celda
# k : carater que representa uno de los bordes de la celda
#      'n': norte
#      's': sur
#      'e': este
#      'w': oeste

def q(i,j,k):
    if k == 'n':
        k = 0
    elif k == 's':
        k = 1
    elif k == 'e':
        k = 2
    elif k == 'w':
        k = 3
        
    return bordesDeCeldas[i][j][k]


# clausulasTipo1, genera las clausulas de tipo 0
#
# ejemplo de traduccion de una restriccion:
#       q(i,j+1,e) <=> q(i,j,w)
#       q(i,j+1,e) => q(i,j,w) /\ q(i,j+1,e) <= q(i,j,w)
#       (no q(i,j+1,e) \/ q(i,j,w)) /\ (q(i,j+1,e) \/ q(i,j,w))
#

def clausulasTipo0():
      
    for i in range(N):
        for j in range(M):
            # Si se tienen celdas a la izquierda
            if j < N - 1:
                clausulas.append(" ".join([negar(q(i,j+1,'e')),
                                           (q(i,j,'w'))]))
            # Si se tienen celdas a la derecha
            if i < M -1:
                clausulas.append(" ".join([negar(q(i+1,j,'n')),
                                       (q(i,j,'s'))]))                           

    return clausulas

################################################################################
# Para la ejecucion  ----------------------------------------------------------#

bordesDeCeldas = generarVariablesBordesDeCeldas() 
clausulas = clausulasTipo0()



