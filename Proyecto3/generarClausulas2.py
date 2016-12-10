import itertools

#  bordesDeCeldas,es un arreglo de 3 dimensiones 
#  1era dimension: fila en la que se encuentra la celda 
#  2da dimension: columna en la que se encuentra la celda 
#  3era dimension: borde de la celda
#
#  bordesDeCeldas[i][j] es una arreglo de tamano 4 que corresponden a cada una
#                       de las lineas que bordean la celda, en el siguiente orden:
#                       norte, sur, este, oeste
bordesDeCeldas = []

N=0 #Filas
numeroColumnas = 0
M=0 #Columnas
numeroFilas = 0

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
	return [N,M,tablero]

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

q(i,j,n) <=> q(i+1,j,s)

Para toda celda c=(i,j) con 1 <= i <= N y 1 <= j < M,

q(i,j,e) <=> q(i,j+1,w)
'''

# generarVariablesBordesDeCeldas es una funcion que genera una variable
# por cada borde una celda. 
# Siendo generadas 4 x numero de celdas
#

def generarVariablesBordesDeCeldas():
    variable = 1
    
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
                clausulas.append(" ".join([negar(q(i,j,'e')),
                                           (q(i,j+1,'w'))]))

                clausulas.append(" ".join([(q(i,j,'e')),
                                           negar(q(i,j+1,'w'))]))
            # Si se tienen celdas a la derecha
            if i < M -1:
                clausulas.append(" ".join([negar(q(i,j,'s')),
                                           (q(i+1,j,'n'))]))    
                clausulas.append(" ".join([(q(i,j,'s')),
                                           negar(q(i+1,j,'n'))]))                         

    return clausulas

'''
Cláusulas tipo 1
----------------

Para cada celda c=(i,j) y etiqueta n en { 0, 1, 2, 3, 4 }, se deben
agregar fórmulas que fuerzen la presencia de n segmentos alrededor de
la celda c. Por ejemplo, si n = 0, se deben agregar las fórmulas:

-q(i,j,n)
-q(i,j,e)
-q(i,j,s)
-q(i,j,w)

y si n=1, se deben agregar las fórmulas:

q(i,j,n) v q(i,j,e) v q(i,j,s) v q(i,j,w)
-q(i,j,n) v -q(i,j,e)
-q(i,j,n) v -q(i,j,s)
-q(i,j,n) v -q(i,j,w)
-q(i,j,e) v -q(i,j,s)
-q(i,j,e) v -q(i,j,w)
-q(i,j,s) v -q(i,j,w)
'''

def clausulasTipo1():

    for i in range(N):
        for j in range(M):
            
            # Si una celda tiene 0 bordes
            if tablero[i][j] == 0:
                # -q(i,j,n) /\ -q(i,j,e) /\ -q(i,j,s) /\ -q(i,j,w)
                for k in ['n','s','e','w']:
                    clausulas.append(" ".join([negar(q(i,j,k))]))
               
            elif tablero[i][j] == 1:
                
                # q(i,j,n) v q(i,j,e) v q(i,j,s) v q(i,j,w)
                clausulas.append(" ".join([(q(i,j,'n')),
                                           (q(i,j,'s')),
                                           (q(i,j,'e')),
                                           (q(i,j,'w'))]))
                
                
                # -q(i,j,n) v -q(i,j,w)
                # -q(i,j,n) v -q(i,j,s)
                # -q(i,j,n) v -q(i,j,e)
                # -q(i,j,e) v -q(i,j,w)
                # -q(i,j,e) v -q(i,j,s)
                # -q(i,j,s) v -q(i,j,w)
                bordes = ['w','s','e','n']
                while bordes != []:
                    k1 = bordes.pop()
                    for k2 in bordes:
                         clausulas.append(" ".join([negar(q(i,j,k1)),
                                                    negar(q(i,j,k2))]))   
                                                
            elif tablero[i][j] == 2:
                # q(i,j,n) v q(i,j,e) v q(i,j,s) v q(i,j,w)
                clausulas.append(" ".join([(q(i,j,'n')),
                                           (q(i,j,'s')),
                                           (q(i,j,'e')),
                                           (q(i,j,'w'))]))
                                           
                                           
                # -q(i,j,n) \/ -q(i,j,s) \/ -q(i,j,e)
                clausulas.append(" ".join([negar(q(i,j,'n')),
                                           negar(q(i,j,'s')),
                                           negar(q(i,j,'e'))]))
                
                
                # -q(i,j,n) \/ -q(i,j,s) \/ -q(i,j,w)
                clausulas.append(" ".join([negar(q(i,j,'n')),
                                           negar(q(i,j,'s')),
                                           negar(q(i,j,'w'))]))
                
                                            
                # q(i,j,n) \/ q(i,j,s) \/ q(i,j,e)
                clausulas.append(" ".join([(q(i,j,'n')),
                                           (q(i,j,'s')),
                                           (q(i,j,'e'))]))
                
                # q(i,j,n) \/ q(i,j,s) \/ q(i,j,w)
                clausulas.append(" ".join([(q(i,j,'n')),
                                           (q(i,j,'s')),
                                           (q(i,j,'w'))]))
               
                # -q(i,j,n) \/ q(i,j,s) \/  q(i,j,w) \/ q(i,j,e)
                clausulas.append(" ".join([negar(q(i,j,'n')),
                                           (q(i,j,'s')),
                                           (q(i,j,'e')),
                                           (q(i,j,'w'))]))
                                           
                # -q(i,j,n) \/ q(i,j,s) \/ -q(i,j,e) \/ -q(i,j,w)
                clausulas.append(" ".join([negar(q(i,j,'n')),
                                           (q(i,j,'s')),
                                           negar(q(i,j,'e')),
                                           negar(q(i,j,'w'))]))
               
                # q(i,j,n) \/ -q(i,j,s) \/  q(i,j,w) \/ q(i,j,e)
                clausulas.append(" ".join([(q(i,j,'n')),
                                           negar(q(i,j,'s')),
                                           (q(i,j,'e')),
                                           (q(i,j,'w'))]))
                
                # q(i,j,n) \/ -q(i,j,s) \/ -q(i,j,e) \/ -q(i,j,w)
                clausulas.append(" ".join([(q(i,j,'n')),
                                           negar(q(i,j,'s')),
                                           negar(q(i,j,'e')),
                                           negar(q(i,j,'w'))]))
                
               
            elif tablero[i][j] == 3:
                
                # -q(i,j,n) v -q(i,j,e) v -q(i,j,s) v -q(i,j,w)
                clausulas.append(" ".join([(negar(q(i,j,'n'))),
                                           (negar(q(i,j,'s'))),
                                           (negar(q(i,j,'e'))),
                                           (negar(q(i,j,'w')))]))
                
                # q(i,j,n) v q(i,j,w)
                # q(i,j,n) v q(i,j,s)
                # q(i,j,n) v q(i,j,e)
                # q(i,j,e) v q(i,j,w)
                # q(i,j,e) v q(i,j,s)
                # q(i,j,s) v q(i,j,w)
                bordes = ['w','s','e','n']
                while bordes != []:
                    k1 = bordes.pop()
                    for k2 in bordes:
                         clausulas.append(" ".join([(q(i,j,k1)),
                                                    (q(i,j,k2))])) 
            elif tablero[i][j] == 4:
                # q(i,j,n) /\ q(i,j,e) /\ q(i,j,s) /\ q(i,j,w)
                for k in ['n','s','e','w']:
                    clausulas.append(" ".join([(q(i,j,k))]))
    return clausulas


'''
Cláusulas tipo 2
----------------

Una solución particiona las celdas en dos grupos: el grupo de celdas
interiores al perímetro y el grupo de celdas exteriores. Debemos 
identificar el tipo de cada celda en una solución. Para esto definimos
símbolos z(c) para cada celda c=(i,j) que denotan cuando una celda es
exterior (z(c)=TRUE) o interior (z(c)=FALSE). Las siguientes fórmulas
fuerzan que los símbolos z(c) esten bien definidos en cada solución.

Para cada celda c=(1,j) con 1 <= j <= M en el borde izquierdo,

-q(1,j,w) <=> z(1,j)

Para cada celda c=(N,j) con 1 <= j <= M en el borde derecho,

-q(N,j,e) <=> z(N,j)

Para cada celda c=(i,1) con 1 <= i <= N en el borde inferior,

-q(i,1,s) <=> z(i,1)

Para cada celda c=(i,M) con 1 <= i <= N en el borde superior,

-q(i,M,n) <=> z(i,M)

Para las celdas c=(i,j) con 1 < i < N y 1 < j < M, que no están
en ningún borde, definimos:

z(i,j) <=> [-q(i,j,n) & z(i,j+1)] v [-q(i,j,e) & z(i+1,j)] v [-q(i,j,s) & z(i,j-1)] v [-q(i,j,w) & z(i-1,j)]

z(i,j) <=> [-q(i,j,n) & z(i-1,j)] v [-q(i,j,e) & z(i,j+1)] v [-q(i,j,s) & z(i+1,j)] v [-q(i,j,w) & z(i,j-1)]
'''
# generarVariablesTipoDeCelda(), genera una variable para cada celda,
# que representara su tipo. 
#
# retorna:      - True, si la celda es exterior
#               - False, si la celda es interior

def generarVariablesTipoDeCelda():
    # variable, la variable actual generada, se inicializa en N * M * 4 + 1 
    # dado que la ultima variable generada fue N * M * 4 (en generarVariablesBordesDeCeldas())
    variable = N * M * 4 + 1
    z = []             
    for i in range(N):
        z += [[]]
        for j in range(M):
            z[i] += [str(variable)]
            variable+=1               
    return z    
    
def clausulasTipo2():
    global clausulas
    
    # Para cada celda  en el borde izquierdo, -q(i,0,w) <=> z(i,0)
    # Es decir:     q(i,0,w) \/ z(i,0)
    #              -q(i,0,w) \/ -z(i,0)
    # Para cada celda en el borde derecho,-q(i,N,e) <=> z(i,N)
    # Es decir:    q(i,N-1,e) \/ z(i,N-1)
    #             -q(i,N-1,e) \/ -z(i,N-1)  
    
    for i in range(N):
        # q(i,0,w) \/ z(i,0), celda en el borde izquierdo
        clausulas.append(" ".join([q(i,0,'w'),
                                   z[i][0]]))
        # -q(i,0,w) \/ -z(i,0), celda en el borde izquierdo
        clausulas.append(" ".join([negar(q(i,0,'w')),
                                   negar(z[i][0])]))
        # q(i,N-1,e) \/ z(i,N-1), celda en el borde derecho
        clausulas.append(" ".join([q(i,N-1,'e'),
                                   z[i][N-1]]))
        # -q(i,N-1,e) \/ -z(N-1,j),  celda en el borde derecho
        clausulas.append(" ".join([negar(q(i,N-1,'e')),
                                   negar(z[i][N-1])]))
    
    # Para cada celda en el borde superior,-q(0,j,n) <=> z(0,j)
    # Para cada celda en el borde inferior, -q(M-1,j,s) <=> z(M-1,j)
    for j in range(M):
        # q(0,j,n) \/ z(0,j), celda en el borde superior
        clausulas.append(" ".join([q(0,j,'n'),
                                   z[0][j]]))
        # -q(0,j,n) \/ -z(0,j), celda en el borde superior
        clausulas.append(" ".join([negar(q(0,j,'n')),
                                   negar(z[0][j])]))
        # q(0,j,s) \/ z(0,j), celda en el borde inferior
        clausulas.append(" ".join([q(M-1,j,'s'),
                                   z[M-1][j]]))
        # -q(0,j,s) \/ -z(N-1,j),  celda en el borde inferior
        clausulas.append(" ".join([negar(q(M-1,j,'s')),
                                   negar(z[M-1][j])]))    
    temp = [] # almacena las variables de una clausula
    #Para toda celda que no este en el borde
    for i in range(1,N-1):
            for j in range(1,M-1):
                # La celda no es exterior o no tiene alguno de sus bordes                
                #-z(i,j) v -q(i,j,n) v -q(i,j,e) v -q(i,j,s) -q(i,j,w)    
                #temp = [negar(z[i][j])]
                #for k in ['n','e','s','w']:
                #    temp += [negar(q(i,j,k))]
                #clausulas.append(" ".join(temp))   
                
                
                # La celda no es exterior o alguna de sus adyancentes es exterior
                # [-z(i,j)v z(i-1,j) v z(i,j+1) v z(i+1,j) v z(i,j)]
                #clausulas.append(" ".join([negar(z[i][j]),
                #                           z[i-1][j],
                #                           z[i][j+1],
                #                           z[i+1][j],
                #                           z[i][j-1]]))
                
                c = itertools.combinations([negar(q(i,j,'n')),
                                           negar(q(i,j,'e')), 
                                           negar(q(i,j,'s')), 
                                           negar(q(i,j,'w')), 
                                           z[i-1][j], 
                                           z[i][j+1],
                                           z[i+1][j], 
                                           z[i][j-1]],    4)
                cd = [[negar(z[i][j])]+list(x) for x in c]
                clausulas += [" ".join(y) for y in cd]


    for i in range(0,N):
            for j in range(0,M):
                
                # La celda es exterior o no tiene borde superior o
                # la celda que es adyacente a ella por el norte no es exterior                           
                # z(i,j) v [q(i,j,n) v -z(i-1,j)]

                if (i > 0):
                    clausulas.append(" ".join([z[i][j],
                                           q(i,j,'n'),
                                           negar(z[i-1][j])]))
                

                #z(i,j) v [q(i,j,e) v -z(i,j+1)]
                if (j < M-1):
                    clausulas.append(" ".join([z[i][j],
                                           q(i,j,'e'),
                                           negar(z[i][j+1])]))
                                           
                #z(i,j) v [q(i,j,s) v -z(i+1,j)]
                if (i < N-1):
                    clausulas.append(" ".join([z[i][j],
                                           q(i,j,'s'),
                                           negar(z[i+1][j])]))
                
                #z(i,j) v [q(i,j,w) v -z(i,j-1)]
                if (j > 0):
                    clausulas.append(" ".join([z[i][j],
                                           q(i,j,'w'),
                                           negar(z[i][j-1])]))
                
                
                
        
    return clausulas    

'''

Cláusulas tipo 3
----------------

Tenemos que describir cuando una celda es alcanzable desde otra
celda de forma inductiva. Utilizamos el símbolo r(c,c') para denotar
que la celda c' es alcanzable desde la celda c. Inicialmente, toda
celda c es alcanzable desde ella misma:

r(c,c)

Para el caso inductivo, definimos el alcance a partir de la adyacencia
de las celdas y la transitividad de la relación. Por ejemplo, si la celda
c' es alcanzable desde la celda c, y la celda c'' es adyancente a c'
por el lado norte, entonces:

r(c,c') & -q(c',n) => r(c,c'')

Esto es un si y solo si, por lo tanto necesitamos la otra implicacion:

r(c,c') & -q(c',n) <= r(c,c'')
!

ya que si c' es alcanzable desde c y no existe un segmento entre c' y c'',
entonces c'' también debe ser alcanzable desde c. Similarmente definimos
fórmulas para las otras direcciones e, s, y w.

'''

'''
def generarVariablesAlcances():
    variable = N * M * 4 + N * M + 1 
    r = dict()
    for i1 in range(N):
        for j1 in range(M):
            for i2 in range(N):
                for j2 in range(M):
                    r[((i1,j1),(i2,j2))] = str(variable)  
                    variable += 1
    return r
'''
def generarVariablesAlcances():
    variable = N * M * 4 + N * M + 1 
    r = dict()
    for i1 in range(N):
        for j1 in range(M):
            for i2 in range(N):
                for j2 in range(M):
                    c1 = (i1,j1)
                    c2 = (i2,j2)
                    # para evitar repeticiones
                    key = (min(c1,c2),max(c1,c2))
                    if key not in r:
                        r[key] = str(variable)  
                        variable += 1
        print("variables:",variable)
    return r

def r(c1,c2):
    if (c1,c2) in alcances:
        alcance = alcances[(c1,c2)]
    elif (c2,c1) in alcances:
        alcance = alcances[(c2,c1)]
    else:
        alcance = None
       
    return alcance

def clausulasTipo3():
    
    #r(c1,c2) & -q(c2,k) => r(c1,c3)
    #-r(c1,c2) v q(c2,k) v r(c1,c3)
    
    for i1 in range(N):
        for j1 in range(M):
            c1 = (i1,j1)
            for i2 in range(N):
                for j2 in range(M):
                    c2 = (i2,j2)                        
                    # si c2 no esta en el borde superior del tablero
                    if i2 > 0:               
                        c3 = (i2-1,j2) # Celda adyacente a c2 por el lado norte
                        clausulas.append(" ".join([negar(r(c1,c2)),
                                                  q(i2,j2,'n'), #segmento entre c2 y c3
                                                  r(c1,c3)]))

                    # si c2 no esta en el borde inferior del tablero
                    if i2 < N-1:
                        c3 = (i2+1,j2) # Celda adyacente a c2 por el lado sur
                        clausulas.append(" ".join([negar(r(c1,c2)),
                                                    q(i2,j2,'s'), #segmento entre c2 y c3
                                                    r(c1,c3)]))
                         
                    # si c2 no esta en el borde derecho del tablero
                    if j2 < M-1:
                         c3 = (i2,j2+1) # Celda adyacente a c2 por el lado este
                         clausulas.append(" ".join([negar(r(c1,c2)),
                                                  q(i2,j2,'e'), #segmento entre c2 y c3
                                                  r(c1,c3)]))
                                                 
                   # si c2 no esta en el borde izquierdo del tablero
                    if j2 > 0:               
                        c3 = (i2,j2-1) # Celda adyacente a c2 por el lado oeste
                        clausulas.append(" ".join([negar(r(c1,c2)),
                                                  q(i2,j2,'w'), #segmento entre c2 y c3
                                                  r(c1,c3)]))


                        
'''
Cláusulas tipo 4
----------------

Finalmente, debemos que indicar que cada par de celdas interiores tienen
que ser alcazables la una de la otra. Para cada par de celdas c y c':

recordemos -z(c) significa que c es interna

-z(c) & -z(c') => r(c,c')

'''

def clausulasTipo4():
    
    # -z(c1) & -z(c2) => r(c1,c2)
    # z(c1) v z(c2) v r(c1,c2)
    for i1 in range(N):
        for j1 in range(M):
            for i2 in range(N):
                for j2 in range(M):
                    for k in ['n','s','e','w']:  
                        clausulas.append(" ".join([z[i1][j1],
                                                  z[i2][j2], 
                                                  r((i1,j1),(i2,j2))]))               
                    
                                                      
    return clausulas

################################################################################
# Para la ejecucion  ----------------------------------------------------------#


N,M,tablero = leerLinea()

numeroFilas = N
numeroColumnas = M

# Generar variables
bordesDeCeldas = generarVariablesBordesDeCeldas() 
z = generarVariablesTipoDeCelda()
alcances = generarVariablesAlcances()


print(z)
temp = ""
for x in z:
    for y in x:
        temp += " " + negar(y)

clausulas.append(temp)


# Generar clausulas
clausulasTipo0()
clausulasTipo1()
clausulasTipo2()
clausulasTipo3()
clausulasTipo4()

print(r((4,4),(0,4)))



with open("inputSatSolver.txt", "w") as f :
    
    f.write("p cnf "+str(450)+" "+str(len(clausulas))+"\n")
    for clausula in clausulas:
        f.write(clausula+" 0\n")
f.close()

# Llamamos a un subproceso para resolver el sat con minisat
import subprocess
subprocess.call(["minisat","inputSatSolver.txt","outputSatSolver.txt","-verb=0"])

# Leemos los valores del output
valores = ["" for i in range(N*M*4*5)]

with open("outputSatSolver.txt","r") as f :

    contenidos = f.readlines()
    # La primera linea es la palabra SAT, la segunda es los valores que queremos.
    linea = contenidos[1]

    numeros = linea.split()

    # Colocamos los valores en strings porque los vamos a necesitar
    #  asi despues
    for i in range(len(numeros)):
        actual = int(numeros[i])
        if actual > 0:
            valores[actual] = "1"
        else:
            valores[-actual] = "0"



respuesta = ""

horizontales = ["" for i in range(numeroFilas+1)]
verticales = ["" for i in range(numeroFilas)]


# Llenamos las lineas horizontales viendo las casillas norte de cada fila
#  excepto la final, en la cual vemos la sur.
lado = "n"
for h in range(numeroFilas+1):
    if h == numeroFilas:
        lado = "s"
        for j in range(M):
            horizontales[h] += valores[int(q(numeroFilas-1,j,"s"))]
    else:
        for j in range(M):
            horizontales[h] += valores[int(q(h,j,"n"))]




# LLenamos las lineas verticales de manera parecida, llenando las casillas
#  oeste de cada columna excepto la final, en la cual se ve el borde este.
lado = "w"
for v in range(numeroFilas):
    for j in range(M+1):
        if j == M:
            verticales[v] += valores[int(q(v,M-1,"e"))]
        else:
            verticales[v] += valores[int(q(v,j,"w"))]


# Imprimimos las respuestas:
# Dimensiones
print(str(N) + " " + str(M), end = " ")

# Lineas horizontales y verticales
for i in range(numeroFilas):
    print(horizontales[i], end=" ")
    print(verticales[i], end = " ")
print(horizontales[numeroFilas])




'''
def imprimirTablero:
  sttr = ""
  for i in range(len(tablero)):
    sttr = ""
    for j in range(len(tablero[i])):
      sttr += " " + ("." if tablero[i][j] == -1 else str(tablero[i][j]))
    print(sttr)
'''
