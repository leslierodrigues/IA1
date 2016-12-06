


"""
1   Elegir Tamano del tablero
2   mapaBordes = construirVariablesBordes(numeroFilas, numeroColumnas)
3   mapaCeldaRestriccionNumeroBordes (ahorita esta hecho a mano, pero se debe construir a partir del input)
4   clausulasNumBordes = construirTodasRestriccionesNumeroBordes()
5   clausulasLineaContinua =  generarRestriccionContinuidad() #Faltan los casos borde
6   clausulas = clausulasNumBordes + clausulasLineaContinua


Faltan los casos especiales de generarRestriccionesHorizonal y generarRestriccionesVertical

"""

def construirTodasRestriccionesNumeroBordes():
    clausulasNumBordes = ""
    for (i,j) in mapaCeldaRestriccionNumeroBordes : 
        clausulasNumBordes += generarRestriccionCeldaNM(i, j, mapaCeldaRestriccionNumeroBordes[(i,j)])
    return clausulasNumBordes

N=5
numeroColumnas = 5
M=5
numeroFilas = 5
#mapaCeldaABordes = {(1,1) : ["X","Y","Z","W"]}
mapaBordes = {(0,1) : "X1"}

def construirVariablesBordes(numeroFilas, numeroColumnas) :
    variablesBordes = {}
    ultimoValor = (numeroFilas+1)*(numeroColumnas+1)-1
    
    for i in range(0, ultimoValor) :
        
        if  ((i+1) % (numeroColumnas+1) != 0) :
            variablesBordes[(i,i+1)] = "".join(["X_",str(i),"_",str(i+1)])
        
        if not(i+numeroColumnas >= ultimoValor) :
            variablesBordes[(i,i+numeroColumnas+1)] = "".join(["X_",str(i),"_",str(i+numeroColumnas+1)])
    
    
    
    return variablesBordes

# Ejemplo que dio Blai
mapaCeldaRestriccionNumeroBordes = {(0,1) : 2, (0,2) : 2, (0,4) : 3
                                   ,(1,1) : 2
                                   ,(2,0) : 3, (2,1) : 2
                                   ,(3,0) : 1, (3,4) : 3
                                   ,(4,1) : 2, (4,2) : 2, (4,3) : 3}


def mapaCeldaABordes(coordenadaCeldaX, coordenadaCeldaY) :
    
    i = coordenadaCeldaX
    j = coordenadaCeldaY
    
    bordesCeldaActual = {"Arriba"    : mapaBordes[((numeroColumnas+1)*i+j, (numeroColumnas+1)*i+j+1)]
                        ,"Abajo"     : mapaBordes[((numeroColumnas+1)*i+j+(numeroColumnas+1), (numeroColumnas+1)*i+j+(numeroColumnas+2))]
                        ,"Izquierda" : mapaBordes[((numeroColumnas+1)*i+j, (numeroColumnas+1)*i+j+(numeroColumnas+1))]
                        ,"Derecha"   : mapaBordes[((numeroColumnas+1)*i+j+1, (numeroColumnas+1)*i+j+1+(numeroColumnas+1))]}
    
    return bordesCeldaActual


def generarRestriccionCuatroBordes(clausulas, bordes) :
    #No puede tener un borde
    clausulas.append(" ".join([negar(bordes[0])
                              ,negar(bordes[1])
                              ,negar(bordes[2])
                              ,negar(bordes[3])]))


def generarRestriccionTresBordes(clausulas, bordes) :
    #No puede tener tres bordes
    clausulas.append(" ".join([negar(bordes[0])
                              ,negar(bordes[1])
                              ,negar(bordes[2])
                              ,      bordes[3]]))
    
    clausulas.append(" ".join([negar(bordes[1])
                              ,negar(bordes[2])
                              ,negar(bordes[3])
                              ,      bordes[0]]))
    
    clausulas.append(" ".join([negar(bordes[0])
                              ,negar(bordes[2])
                              ,negar(bordes[3])
                              ,      bordes[1]]))
    
    clausulas.append(" ".join([negar(bordes[0])
                              ,negar(bordes[1])
                              ,negar(bordes[3])
                              ,      bordes[2]]))


def generarRestriccionUnBorde(clausulas, bordes) :
    #No puede tener un borde
    clausulas.append(" ".join([negar(bordes[0])
                              ,      bordes[1]
                              ,      bordes[2]
                              ,      bordes[3]]))
    
    clausulas.append(" ".join([negar(bordes[1])
                              ,      bordes[0]
                              ,      bordes[2]
                              ,      bordes[3]]))
    
    clausulas.append(" ".join([negar(bordes[2])
                              ,      bordes[0]
                              ,      bordes[1]
                              ,      bordes[3]]))
    
    clausulas.append(" ".join([negar(bordes[3])
                              ,      bordes[0]
                              ,      bordes[1]
                              ,      bordes[2]]))


def generarRestriccionDosBordes(clausulas, bordes) :
    #No puede tener dos bordes
    clausulas.append(" ".join([negar(bordes[0])
                              ,negar(bordes[1])
                              ,      bordes[2]
                              ,      bordes[3]])) 
    
    clausulas.append(" ".join([negar(bordes[0])
                              ,negar(bordes[2])
                              ,      bordes[1]
                              ,      bordes[3]])) 
    
    clausulas.append(" ".join([negar(bordes[1])
                              ,negar(bordes[2])
                              ,      bordes[0]
                              ,      bordes[3]])) 
    
    clausulas.append(" ".join([negar(bordes[1])
                              ,negar(bordes[3])
                              ,      bordes[0]
                              ,      bordes[2]])) 
    
    clausulas.append(" ".join([negar(bordes[2])
                              ,negar(bordes[3])
                              ,      bordes[0]
                              ,      bordes[1]])) 
    
    clausulas.append(" ".join([negar(bordes[0])
                              ,negar(bordes[3])
                              ,      bordes[2]
                              ,      bordes[1]])) 




def negar(nombreVariable) :
    if nombreVariable == "" :
        return ""
    return "-"+nombreVariable 


def generarRestriccionCeldaNM(CoordenadaX, CoordenadaY, numeroDeBordes) :
    
    #Esta celda debe tener "numeroDeBordes" bordes
    
    
    #bordes = mapaCeldaABordes[(CoordenadaX, CoordenadaY)]
    bordesDiccionario =  mapaCeldaABordes(CoordenadaX, CoordenadaY)
    bordes = list(bordesDiccionario.values())
    clausulas = []
    
    if numeroDeBordes == 1 :
        
        #No se permiten cuatro bordes
        generarRestriccionCuatroBordes(clausulas, bordes)
        
        #No se permiten tres bordes
        generarRestriccionTresBordes(clausulas, bordes)
        
        #No se permiten dos bordes
        generarRestriccionDosBordes(clausulas, bordes)
        
    elif numeroDeBordes == 2 :
        
        #No se permiten cuatro bordes
        generarRestriccionCuatroBordes(clausulas, bordes)
        
        #No se permiten tres bordes
        generarRestriccionTresBordes(clausulas, bordes)
        
        #No se permite un solo borde
        generarRestriccionUnBorde(clausulas, bordes)
        
    elif numeroDeBordes == 3 :
        
        #No se permiten cuatro bordes
        generarRestriccionCuatroBordes(clausulas, bordes)
        
        #No se permiten dos bordes
        generarRestriccionDosBordes(clausulas, bordes)
        
        #No se permite un solo borde
        generarRestriccionUnBorde(clausulas, bordes)
        
    elif numeroDeBordes == 4:
        
        #No se permiten tres bordes
        generarRestriccionTresBordes(clausulas, bordes)
        
        #No se permiten dos bordes
        generarRestriccionDosBordes(clausulas, bordes)
        
        #No se permite un solo borde
        generarRestriccionUnBorde(clausulas, bordes)
        
    
    return "\n".join(clausulas)

def esHorizontal(i,j) : return j==i+1

def esVertical(i,j) : return j==i+(numeroColumnas+1)


def generarRestriccionesHorizonal(clausulas, extremoIzquierdo, extremoDerecho) :
   
   # el extremoIzquierdo y el extremoDerecho representan un borde horizontal
   
    i = extremoIzquierdo
    j = extremoDerecho
    
    #"""
    #hayCasoBorde = any([(i % (numeroColumnas+1) == 0)
    #                  , (j+numeroColumnas+1 > (numeroColumnas+1)*(numeroFilas+1))
    #                  , ((i+1)%(numeroColumnas+1) == 0), ((j+1)%(numeroColumnas+1) == 0)
    #                  , (i <= numeroColumnas)
    #                  , (j <= numeroColumnas)])
    #"""
    
    
    
    variable = mapaBordes.get((i,j), "")
    arribaDerecha = mapaBordes.get((j-numeroColumnas-1,j), "")
    derecha = mapaBordes.get((j,j+1), "")
    abajoDerecha = mapaBordes.get((j,+numeroColumnas+1), "")
    arribaIzquierda = mapaBordes.get((i-numeroColumnas-1,i), "")
    izquierda = mapaBordes.get((i-1,i), "")
    abajoIzquierda = mapaBordes.get((i,i+numeroColumnas+1), "")
    
    #Una celda
    if (izquierda == "") and (arribaIzquierda == "") and (derecha == ""):
        clausulas.append(" ".join([abajoIzquierda, negar(variable), abajoDerecha]))
        return
    
    #Esquina superior izquierda
    if (izquierda == "") and (arribaIzquierda == "") :
        clausulas.append(" ".join([abajoIzquierda, negar(variable),abajoDerecha, negar(derecha)]))
        clausulas.append(" ".join([abajoIzquierda, negar(variable), negar(abajoDerecha), derecha]))
        return
    
    #Esquina superior  derecha
    if (derecha == "") and (arribaDerecha == "") :
        clausulas.append(" ".join([abajoIzquierda, negar(variable),abajoDerecha, negar(izquierda)]))
        clausulas.append(" ".join([abajoDerecha, negar(variable), negar(abajoIzquierda), izquierda]))
        return
    
    #Primera Fila
    if (arribaIzquierda == "") and (arribaDerecha == "") :
        clausulas.append(" ".join([abajoIzquierda, negar(variable),abajoDerecha, negar(derecha),negar(izquierda)]))
        clausulas.append(" ".join([negar(abajoIzquierda), negar(variable),abajoDerecha, negar(derecha),izquierda]))
        clausulas.append(" ".join([negar(abajoIzquierda), negar(variable),negar(abajoDerecha), derecha,izquierda]))
        clausulas.append(" ".join([abajoIzquierda, negar(variable),negar(abajoDerecha), derecha,negar(izquierda)]))
        return
    
    #Extremo Derecho toca borde
    
    
    #Restricciones para el extremo derecho
    clausulas.append(" ".join([negar(variable)
                              ,negar(arribaDerecha)
                              ,negar(derecha)
                              ,negar(abajoDerecha)]))
    
    clausulas.append(" ".join([negar(variable)
                              ,negar(arribaDerecha)
                              ,negar(derecha)
                              ,abajoDerecha]))
    
    clausulas.append(" ".join([negar(variable)
                              ,negar(arribaDerecha)
                              ,derecha
                              ,negar(abajoDerecha)]))
    
    clausulas.append(" ".join([negar(variable)
                              ,arribaDerecha
                              ,negar(derecha)
                              ,negar(abajoDerecha)]))
    
    #Restricciones para el extremo izuierdo
    clausulas.append(" ".join([negar(variable)
                              ,negar(arribaIzquierda)
                              ,negar(izquierda)
                              ,negar(abajoIzquierda)]))
    
    clausulas.append(" ".join([negar(variable)
                              ,negar(arribaIzquierda)
                              ,negar(izquierda)
                              ,abajoIzquierda]))
    
    clausulas.append(" ".join([negar(variable)
                              ,negar(arribaIzquierda)
                              ,izquierda
                              ,negar(abajoIzquierda)]))
    
    clausulas.append(" ".join([negar(variable)
                              ,arribaIzquierda
                              ,negar(izquierda)
                              ,negar(abajoIzquierda)]))
    
    
    

def generarRestriccionesVertical(clausulas, extremoSuperior, extremoInferior) :
    i = extremoSuperior
    j = extremoInferior
    
    variable = mapaBordes.get((i,j), "")
    arribaDerecha = mapaBordes.get((i,i+1), "")
    arriba = mapaBordes.get((i-numeroColumnas-1,i), "")
    arribaIzquierda = mapaBordes.get((i-1,i), "")
    abajoIzquierda = mapaBordes.get((j-1,j), "")
    abajo = mapaBordes.get((j,j+numeroColumnas+1), "")
    abajoDerecha = mapaBordes.get((j,j+1), "")
    
    #Restricciones para el extremo superior
    clausulas.append(" ".join([negar(variable)
                              ,negar(arribaDerecha)
                              ,negar(arriba)
                              ,negar(arribaIzquierda)]))
    
    clausulas.append(" ".join([negar(variable)
                              ,negar(arribaIzquierda)
                              ,negar(arriba)
                              ,arribaDerecha]))
    
    clausulas.append(" ".join([negar(variable)
                              ,negar(arribaIzquierda)
                              ,arriba
                              ,negar(arribaDerecha)]))
    
    clausulas.append(" ".join([negar(variable)
                              ,arribaIzquierda
                              ,negar(arriba)
                              ,negar(arribaDerecha)]))
    
    #Restricciones para el extremo inferior
    clausulas.append(" ".join([negar(variable)
                              ,negar(abajoDerecha)
                              ,negar(abajo)
                              ,negar(abajoIzquierda)]))
    
    clausulas.append(" ".join([negar(variable)
                              ,negar(abajoIzquierda)
                              ,negar(abajo)
                              ,abajoDerecha]))
    
    clausulas.append(" ".join([negar(variable)
                              ,negar(abajoIzquierda)
                              ,abajo
                              ,negar(abajoDerecha)]))
    
    clausulas.append(" ".join([negar(variable)
                              ,abajoIzquierda
                              ,negar(abajo)
                              ,negar(abajoDerecha)]))



def generarRestriccionContinuidad() :
    
    clausulas = []
    literal = []
    
    for (i,j) in mapaBordes :
        
        if esHorizontal(i,j) :
            generarRestriccionesHorizonal(clausulas, i, j)
            
        elif esVertical(i,j) :
            generarRestriccionesVertical(clausulas, i, j)
        
    
    return "\n".join(clausulas)
