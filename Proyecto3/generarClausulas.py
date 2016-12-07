


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
    
    
    variable = mapaBordes.get((i,j), "")
    arribaDerecha = mapaBordes.get((j-numeroColumnas-1,j), "")
    derecha = mapaBordes.get((j,j+1), "")
    abajoDerecha = mapaBordes.get((j,+numeroColumnas+1), "")
    arribaIzquierda = mapaBordes.get((i-numeroColumnas-1,i), "")
    izquierda = mapaBordes.get((i-1,i), "")
    abajoIzquierda = mapaBordes.get((i,i+numeroColumnas+1), "")
    
    #Solo hay una celda en el tablero
    if (izquierda == "") and (arribaIzquierda == "") and (derecha == "") and (arribaDerecha == ""):
        
        clausulas.append(" ".join([negar(variable)            # Si el borde se usa
                                 ,       abajoIzquierda       # entonces la izquierda no puede
                                 , negar(abajoDerecha)]))     # estar apagada
        
        clausulas.append(" ".join([negar(variable)            # Si el borde se usa
                                 , negar(abajoIzquierda)      # entonces la derecha no puede
                                 ,       abajoDerecha]))      # estar apagada
        
        clausulas.append(" ".join([negar(variable)            # Si el borde se usa
                                 ,       abajoIzquierda       # entonces los lados no 
                                 ,       abajoDerecha]))      # pueden estar apagados
        
        return
    
    #Esquina superior izquierda
    if (izquierda == "") and (arribaIzquierda == "") and (derecha != "") and (abajoIzquierda != ""):
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,negar(abajoIzquierda)     # entonces todas sus conexiones
                                  ,negar(abajoDerecha)       # no pueden estar prendidas
                                  ,negar(derecha)]))         # al mismo tiempo
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      abajoIzquierda      # entonces la izquierda inferior debe usarse
                                  ,negar(abajoDerecha)       # y las demas no pueden usarse
                                  ,negar(derecha)]))         # al mismo tiempo
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      abajoIzquierda      # entonces la izquierda inferior debe usarse
                                  ,      abajoDerecha        # siempre
                                  ,negar(derecha)]))         # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      abajoIzquierda      # entonces la izquierda inferior debe usarse
                                  ,negar(abajoDerecha)       # siempre
                                  ,      derecha ]))         # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      abajoIzquierda      # entonces los demas bordes no
                                  ,      abajoDerecha        # pueden estar apagados 
                                  ,      derecha ]))         # todos a la vez
        
        return
    
    #Esquina superior  derecha
    if (derecha == "") and (arribaDerecha == "") and (izquierda != "") :
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,negar(abajoIzquierda)     # entonces todas sus conexiones
                                  ,negar(abajoDerecha)       # no pueden estar prendidas
                                  ,negar(izquierda)]))       # al mismo tiempo
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      abajoDerecha        # entonces la derecha inferior debe usarse
                                  ,negar(abajoIzquierda)     # y las demas no pueden usarse
                                  ,negar(izquierda)]))       # al mismo tiempo
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      abajoIzquierda      # entonces la derecha inferior debe usarse
                                  ,      abajoDerecha        # siempre
                                  ,negar(izquierda)]))       # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      abajoDerecha        # entonces la derecha inferior debe usarse
                                  ,negar(abajoIzquierda)     # siempre
                                  ,      izquierda ]))       # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      abajoIzquierda      # entonces los demas bordes no
                                  ,      abajoDerecha        # pueden estar apagados 
                                  ,      izquierda ]))       # todos a la vez
        
        return
    
    
    #Primera Fila
    if (arribaIzquierda == "") and (arribaDerecha == "") and (izquierda != "") and (derecha != ""):
        
        clausulas.append(" ".join([negar(variable)          # Si el borde se usa, entonces
                                 , negar(abajoIzquierda)    # los dos bordes de la izquierda
                                 , negar(izquierda)]))      # no pueden usarse a la vez
        
        clausulas.append(" ".join([negar(variable)          # Si el borde se usa, entonces
                                 , negar(abajoDerecha)      # los dos bordes de la derecha
                                 , negar(derecha)]))        # no pueden usarse a la vez
        
        clausulas.append(" ".join([negar(variable)          # Si el borde se usa, entonces
                                 ,       abajoIzquierda     # debe haber alguna conexion 
                                 , negar(izquierda)         # a la derecha
                                 ,       derecha            #
                                 ,       abajoDerecha]))    # 
        
        clausulas.append(" ".join([negar(variable)          # Si el borde se usa, entonces
                                 , negar(abajoIzquierda)    # debe haber alguna conexion 
                                 ,       izquierda          # a la derecha
                                 ,       derecha            #
                                 ,       abajoDerecha]))    # 
        
        clausulas.append(" ".join([negar(variable)          # Si el borde se usa, entonces
                                 ,       abajoIzquierda     # debe haber alguna conexion 
                                 ,       izquierda          # a la izquierda
                                 , negar(derecha)           #
                                 ,       abajoDerecha]))    # 
        
        clausulas.append(" ".join([negar(variable)          # Si el borde se usa, entonces
                                 ,       abajoIzquierda     # debe haber alguna conexion 
                                 ,       izquierda          # a la izquierda
                                 ,       derecha            #
                                 , negar(abajoDerecha)]))   # 
        
        clausulas.append(" ".join([negar(variable)          # Si el borde se usa, entonces
                                 ,       abajoIzquierda     # los demas bordes no pueden
                                 ,       izquierda          # estar vacios
                                 ,       derecha            #
                                 ,       abajoDerecha ]))   # 
        
        return
    
    
    
    
    #Extremo Derecho toca el borde
    if ((arribaIzquierda != "") and (arribaDerecha != "") and (izquierda != "") 
        and (derecha == "")    and (abajoDerecha != "")) :
        
        clausulas.append(" ".join([negar(variable)             # Si el borde se usa, entonces
                                 , negar(arribaDerecha)        # los dos bordes de la derecha
                                 , negar(abajoDerecha)]))      # no pueden usarse a la vez
        
        clausulas.append(" ".join([negar(variable)             # Si el borde se usa, entonces
                                 ,       arribaDerecha         # los dos bordes de la derecha
                                 ,       abajoDerecha]))       # no pueden estar vacios a la vez
        
        clausulas.append(" ".join([negar(variable)             # Si el borde se usa, entonces
                                 ,       arribaIzquierda       # los tres bordes de la izquierda
                                 ,       abajoIzquierda        # no pueden estar vacios a la vez
                                 ,       izquierda ]))         # 
        
        clausulas.append(" ".join([negar(variable)             # Si el borde se usa, entonces
                                 , negar(arribaIzquierda)      # los tres bordes de la izquierda
                                 , negar(abajoIzquierda)       # no pueden usarse a la vez
                                 , negar(izquierda)]))         # 
        
        clausulas.append(" ".join([negar(variable)             # Si el borde se usa, entonces
                                 , negar(arribaIzquierda)      # no puede haber dos bordes 
                                 , negar(abajoIzquierda)       # prendidos a la izquierda
                                 ,       izquierda]))          # 
        
        clausulas.append(" ".join([negar(variable)             # Si el borde se usa, entonces
                                 , negar(arribaIzquierda)      # no puede haber dos bordes 
                                 ,       abajoIzquierda        # prendidos a la izquierda
                                 , negar(izquierda)]))         # 
        
        clausulas.append(" ".join([negar(variable)             # Si el borde se usa, entonces
                                 ,       arribaIzquierda       # no puede haber dos bordes 
                                 , negar(abajoIzquierda)       # prendidos a la izquierda
                                 , negar(izquierda)]))         # 
        
        clausulas.append(" ".join([negar(variable)          # Si el borde se usa, entonces
                                 ,       abajoIzquierda     # los demas bordes no pueden
                                 ,       izquierda          # estar vacios
                                 ,       arribaDerecha      #
                                 ,       abajoDerecha 
                                 ,       arribaIzquierda]))   # 
        
        return
    
    #Esquina inferior derecha
    if (izquierda != "") and (derecha == "") and (arribaDerecha != "") and (abajoDerecha == "") :
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,negar(arribaIzquierda)    # entonces todas sus conexiones
                                  ,negar(arribaDerecha)      # no pueden estar prendidas
                                  ,negar(izquierda)]))       # al mismo tiempo
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      arribaDerecha       # entonces la derecha inferior debe usarse
                                  ,negar(arribaIzquierda)    # y las demas no pueden usarse
                                  ,negar(izquierda)]))       # al mismo tiempo
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      arribaIzquierda     # entonces la derecha inferior debe usarse
                                  ,      arribaDerecha       # siempre
                                  ,negar(izquierda)]))       # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      arribaDerecha       # entonces la derecha inferior debe usarse
                                  ,negar(arribaIzquierda)    # siempre
                                  ,      izquierda ]))       # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      arribaIzquierda     # entonces los demas bordes no
                                  ,      arribaDerecha       # pueden estar apagados 
                                  ,      izquierda ]))       # todos a la vez
        
        return
    
    #Esquina inferior izquierda
    if (izquierda == "") and (arribaIzquierda != "") and (derecha != "") and (abajoIzquierda == "") :
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,negar(arribaIzquierda)    # entonces todas sus conexiones
                                  ,negar(arribaDerecha)      # no pueden estar prendidas
                                  ,negar(derecha)]))         # al mismo tiempo
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      arribaIzquierda     # entonces la izquierda inferior debe usarse
                                  ,negar(arribaDerecha)      # y las demas no pueden usarse
                                  ,negar(derecha)]))         # al mismo tiempo
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      arribaIzquierda     # entonces la izquierda inferior debe usarse
                                  ,      arribaDerecha       # siempre
                                  ,negar(derecha)]))         # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      arribaIzquierda     # entonces la izquierda inferior debe usarse
                                  ,negar(arribaDerecha)      # siempre
                                  ,      derecha ]))         # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa
                                  ,      arribaIzquierda     # entonces los demas bordes no
                                  ,      arribaDerecha       # pueden estar apagados 
                                  ,      derecha ]))         # todos a la vez
        
        return
    
    
    # Ultima fila
    if (abajoIzquierda == "") and (arribaDerecha != "") and (izquierda != "") and (derecha != "") :
        
        clausulas.append(" ".join([negar(variable)          # Si el borde se usa, entonces
                                 , negar(arribaIzquierda)   # los dos bordes de la izquierda
                                 , negar(izquierda)]))      # no pueden usarse a la vez
        
        clausulas.append(" ".join([negar(variable)          # Si el borde se usa, entonces
                                 , negar(arribaDerecha)     # los dos bordes de la derecha
                                 , negar(derecha)]))        # no pueden usarse a la vez
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa, entonces
                                 ,       arribaIzquierda     # debe haber alguna conexion 
                                 , negar(izquierda)          # a la derecha
                                 ,       derecha             #
                                 ,       arribaDerecha]))    # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa, entonces
                                 , negar(arribaIzquierda)    # debe haber alguna conexion 
                                 ,       izquierda           # a la derecha
                                 ,       derecha             #
                                 ,       arribaDerecha]))    # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa, entonces
                                 ,       arribaIzquierda     # debe haber alguna conexion 
                                 ,       izquierda           # a la izquierda
                                 , negar(derecha)            #
                                 ,       arribaDerecha]))    # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa, entonces
                                 ,       arribaIzquierda     # debe haber alguna conexion 
                                 ,       izquierda           # a la izquierda
                                 ,       derecha             #
                                 , negar(arribaDerecha)]))   # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa, entonces
                                 ,       arribaIzquierda     # los demas bordes no pueden
                                 ,       izquierda           # estar vacios
                                 ,       derecha             #
                                 ,       arribaDerecha ]))   # 
        
        return
    
    
    #Extremo Izquierda toca el borde
    if ((arribaIzquierda != "") and (arribaDerecha != "") and (izquierda == "") 
        and (derecha != "")    and (abajoDerecha == "")) :
        
        clausulas.append(" ".join([negar(variable)               # Si el borde se usa, entonces
                                 , negar(arribaIzquierda)        # los dos bordes de la izquierda
                                 , negar(abajoIzquierda)]))      # no pueden usarse a la vez
        
        clausulas.append(" ".join([negar(variable)               # Si el borde se usa, entonces
                                 ,       arribaIzquierda         # los dos bordes de la izquierda
                                 ,       abajoIzquierda]))       # no pueden estar vacios a la vez
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa, entonces
                                 ,       arribaDerecha       # los tres bordes de la derecha
                                 ,       abajoDerecha        # no pueden estar vacios a la vez
                                 ,       derecha ]))         # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa, entonces
                                 , negar(arribaDerecha)      # los tres bordes de la derecha
                                 , negar(abajoDerecha)       # no pueden usarse a la vez
                                 , negar(derecha)]))         # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa, entonces
                                 , negar(arribaDerecha)      # no puede haber dos bordes 
                                 , negar(abajoDerecha)       # prendidos a la derecha
                                 ,       derecha]))          # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa, entonces
                                 , negar(arribaDerecha)      # no puede haber dos bordes 
                                 ,       abajoDerecha        # prendidos a la derecha
                                 , negar(derecha)]))         # 
        
        clausulas.append(" ".join([negar(variable)           # Si el borde se usa, entonces
                                 ,       arribaDerecha       # no puede haber dos bordes 
                                 , negar(abajoDerecha)       # prendidos a la derecha
                                 , negar(derecha)]))         # 
        
        clausulas.append(" ".join([negar(variable)            # Si el borde se usa, entonces
                                 ,       abajoDerecha         # los demas bordes no pueden
                                 ,       derecha              # estar vacios
                                 ,       arribaIzquierda            #
                                 ,       abajoIzquierda
                                 ,       arribaDerecha ]))   # 
        
        return
    
    #Restricciones para el extremo derecho (No es caso especial)
    clausulas.append(" ".join([negar(variable)             # Si el borde se usa,
                              ,negar(arribaDerecha)        # entonces los demas no pueden
                              ,negar(derecha)              # usarse todos a la vez
                              ,negar(abajoDerecha)]))
    
    clausulas.append(" ".join([negar(variable)             # Si el borde se usa,
                              ,negar(arribaDerecha)        # entonces no puede haber dos
                              ,negar(derecha)              # bordes prendidos a la vez
                              ,abajoDerecha]))             # a la derecha
    
    clausulas.append(" ".join([negar(variable)             # Si el borde se usa,
                              ,negar(arribaDerecha)        # entonces no puede haber dos
                              ,derecha                     # bordes prendidos a la vez
                              ,negar(abajoDerecha)]))      # a la derecha
    
    clausulas.append(" ".join([negar(variable)             # Si el borde se usa,
                              ,arribaDerecha               # entonces no puede haber dos
                              ,negar(derecha)              # bordes prendidos a la vez
                              ,negar(abajoDerecha)]))      # a la derecha
    
    clausulas.append(" ".join([negar(variable)            # Si el borde se usa, entonces
                             ,       abajoDerecha         # los demas bordes no pueden
                             ,       derecha              # estar vacios
                             ,       arribaDerecha ]))    # 
    
    #Restricciones para el extremo izquierda (No es caso especial)
    clausulas.append(" ".join([negar(variable)               # Si el borde se usa,
                              ,negar(arribaIzquierda)        # entonces los demas no pueden
                              ,negar(izquierda)              # usarse todos a la vez
                              ,negar(abajoIzquierda)]))
    
    clausulas.append(" ".join([negar(variable)             # Si el borde se usa,
                              ,negar(arribaIzquierda)        # entonces no puede haber dos
                              ,negar(izquierda)              # bordes prendidos a la vez
                              ,      abajoDerecha]))             # a la izquierda
    
    clausulas.append(" ".join([negar(variable)             # Si el borde se usa,
                              ,negar(arribaIzquierda)        # entonces no puede haber dos
                              ,      izquierda                     # bordes prendidos a la vez
                              ,negar(abajoIzquierda)]))      # a la izquierda
    
    clausulas.append(" ".join([negar(variable)             # Si el borde se usa,
                              ,      arribaIzquierda               # entonces no puede haber dos
                              ,negar(izquierda)              # bordes prendidos a la vez
                              ,negar(abajoIzquierda)]))      # a la izquierda
    
    clausulas.append(" ".join([negar(variable)            # Si el borde se usa, entonces
                             ,       abajoIzquierda         # los demas bordes no pueden
                             ,       izquierda              # estar vacios
                             ,       arribaIzquierda ]))    # 
    
    return
    

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
