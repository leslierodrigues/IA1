#include <stdlib.h>
#include <stdio.h>
#include <iostream>


using namespace std;

int x_dim;
int y_dim;


void moverALaDerecha(int x_dim, int y_dim, int *numeroRegla){
    int numeroTotal = x_dim * y_dim -1;
    // Mover el blanco a la derecha
    for(int posBlanca = 0; posBlanca < numeroTotal; posBlanca++){
        
        //Genero la fila si es válida
        if ((posBlanca+1) % y_dim == 0){continue;}
            
        for(int posCelda = 0; posCelda <= numeroTotal; posCelda++){
            
            if (posBlanca == posCelda){
                cout << "B ";
            }
            else if (posBlanca + 1 == posCelda){
                cout << "X ";
            }
            else {
                cout << "- ";
            }
        
        }
        
        cout << "=> ";
        
        //Después de mover a la derecha
        for(int posCelda = 0; posCelda <= numeroTotal; posCelda++){
            
            if (posBlanca == posCelda){
                cout << "X ";
            }
            else if (posBlanca + 1 == posCelda){
                cout << "B ";
            }
            else {
                cout << "- ";
            }
        
        }
        printf("LABEL Rev%d", *numeroRegla);
        cout << endl;
        (*numeroRegla)++;
    }
    
}


void moverALaIzquierda(int x_dim, int y_dim, int *numeroRegla){
    int numeroTotal = x_dim * y_dim -1;
    
    // Mover el blanco a la izquierda
    for(int posBlanca = 0; posBlanca <= numeroTotal; posBlanca++){
        
        //Genero la fila si es válida
        if ((posBlanca) % y_dim == 0){continue;}
            
        for(int posCelda = 0; posCelda <= numeroTotal; posCelda++){
            
            if (posBlanca == posCelda){
                cout << "B ";
            }
            else if (posBlanca - 1 == posCelda){
                cout << "X ";
            }
            else {
                cout << "- ";
            }
        
        }
        
        cout << "=> ";
        
        for(int posCelda = 0; posCelda <= numeroTotal; posCelda++){
            
            if (posBlanca == posCelda){
                cout << "X ";
            }
            else if (posBlanca - 1 == posCelda){
                cout << "B ";
            }
            else {
                cout << "- ";
            }
        
        }
        
        printf("LABEL Rev%d", *numeroRegla);
        cout << endl;
        (*numeroRegla)++;
       
    }
}


void moverArriba(int x_dim, int y_dim, int *numeroRegla){
    int numeroTotal = x_dim * y_dim-1;
    // Mover el blanco arriba
    for(int posBlanca = 0; posBlanca <= numeroTotal; posBlanca++){
        
        //Genero la fila si es válida
        if ((posBlanca+1) - y_dim <= 0){continue;}
            
        for(int posCelda = 0; posCelda <= numeroTotal; posCelda++){
            
            if (posBlanca == posCelda){
                cout << "B ";
            }
            else if (posBlanca - y_dim == posCelda){
                cout << "X ";
            }
            else {
                cout << "- ";
            }
        
        }
        
        cout << "=> ";
        
        for(int posCelda = 0; posCelda <= numeroTotal; posCelda++){
            
            if (posBlanca == posCelda){
                cout << "X ";
            }
            else if (posBlanca - y_dim == posCelda){
                cout << "B ";
            }
            else {
                cout << "- ";
            }
        
        }
        
        printf("LABEL Rev%d", *numeroRegla);
        cout << endl;
        (*numeroRegla)++;
        
    }
    
}


void moverAbajo(int x_dim, int y_dim, int *numeroRegla){
    int numeroTotal = x_dim * y_dim-1;
    // Mover el blanco arriba
    for(int posBlanca = 1; posBlanca <= numeroTotal; posBlanca++){
        
        //Genero la fila si es válida
        if ((posBlanca+1) + y_dim >= numeroTotal+1){continue;}
            
        for(int posCelda = 0; posCelda <= numeroTotal; posCelda++){
            
            if (posBlanca == posCelda){
                cout << "B ";
            }
            else if (posBlanca + y_dim == posCelda){
                cout << "X ";
            }
            else {
                cout << "- ";
            }
        
        }
        
        cout << "=> ";
        
        
        for(int posCelda = 0; posCelda <= numeroTotal; posCelda++){
            
            if (posBlanca == posCelda){
                cout << "X ";
            }
            else if (posBlanca + y_dim == posCelda){
                cout << "B ";
            }
            else {
                cout << "- ";
            }
        
        }
        
        printf("LABEL Rev%d", *numeroRegla);
        cout << endl;
        (*numeroRegla)++;
    }
    
}

void imprimirGoal(int x_dim, int y_dim){
    
    int numeroTotal = x_dim * y_dim;
    
    cout << "GOAL ";
    
    cout << "B ";
    for(int celda = 2 ; celda <= numeroTotal; celda++){
        printf("%d ", celda);
    }
}

void imprimirDominio(int x_dim, int y_dim){
    
    int numeroTotal = x_dim * y_dim -1;
    
    printf("DOMAIN celda %d\n", numeroTotal);
    cout << "       ";
    
    cout << "B ";
    for(int celda = 1 ; celda <= numeroTotal; celda++){
        printf("%d ", celda);
    }
    
    cout << endl;
    printf("\n%d\n\n", numeroTotal);
    
    for(int numCelda = 0 ; numCelda <= numeroTotal; numCelda++){
        printf("celda ");
    }
    
    cout << endl << endl;
    
}

int main(int argc, char *argv[]){
    
    
    if (argc != 3){
        cerr << "El número de argumentos es incorrecto" << endl;
        cerr << "Ejemplo: genNPuzzle x y, donde (x,y) son las dimensiones" << endl;
        exit(0);
    }
    
    
    if (!sscanf(argv[1], "%d", &x_dim) || x_dim < 1){
        cerr << "La dimensión x está mal escrita.";
        exit(0);
    }
    
    
    if (!sscanf(argv[2], "%d", &y_dim) || y_dim < 1){
        cerr << "La dimensión y está mal escrita.";
        exit(0);
    }
    
    int numeroRegla = 1;
    
    imprimirDominio(x_dim, y_dim);
    moverALaDerecha(x_dim, y_dim, &numeroRegla);
    moverALaIzquierda(x_dim, y_dim, &numeroRegla);
    moverArriba(x_dim, y_dim, &numeroRegla);
    moverAbajo(x_dim, y_dim, &numeroRegla);
    cout << endl;
    imprimirGoal(x_dim, y_dim);
    cout << endl;
    
    return (EXIT_SUCCESS);
}
