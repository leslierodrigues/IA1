#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int x_dim;
int y_dim;


void moverALaDerecha(int x_dim, int y_dim, int *numeroRegla, int letra){
    int numeroTotal = x_dim * y_dim -1;
    string ficha;
    if (letra == 1){ficha = "N ";}
    else{ficha = "B ";}
    
    // Mover el blanco a la derecha
    for(int posBlanca = 0; posBlanca < numeroTotal; posBlanca++){
        
        //Genero la fila si es válida
        if ((posBlanca+1) % y_dim == 0){continue;}
            
        for(int posCelda = 0; posCelda <= numeroTotal; posCelda++){
            
            if (posBlanca == posCelda){
                cout << ficha;
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
                cout << ficha;
            }
            else {
                cout << "- ";
            }
        
        }
        printf("LABEL Rev%d", *numeroRegla);
        if (letra == 1){cout << " COST 0";}
    
        cout << endl;
        (*numeroRegla)++;
    }
    
}


void moverALaIzquierda(int x_dim, int y_dim, int *numeroRegla, int letra){
    int numeroTotal = x_dim * y_dim -1;
    string ficha;
    if (letra == 1){ficha = "N ";}
    else{ficha = "B ";}
    
    // Mover el blanco a la izquierda
    for(int posBlanca = 0; posBlanca <= numeroTotal; posBlanca++){
        
        //Genero la fila si es válida
        if ((posBlanca) % y_dim == 0){continue;}
            
        for(int posCelda = 0; posCelda <= numeroTotal; posCelda++){
            
            if (posBlanca == posCelda){
                cout << ficha;
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
                cout << ficha;
            }
            else if (posBlanca - 1 == posCelda){
                cout << ficha;
            }
            else {
                cout << "- ";
            }
        
        }
        
        printf("LABEL Rev%d", *numeroRegla);
        if (letra == 1){cout << " COST 0";}
    
        cout << endl;
        (*numeroRegla)++;
       
    }
}


void moverArriba(int x_dim, int y_dim, int *numeroRegla, int letra){
    string ficha;
    int numeroTotal = x_dim * y_dim-1;
    
    if (letra == 1){ficha = "N ";}
    else{ficha = "B ";}
    
    // Mover el blanco arriba
    for(int posBlanca = 0; posBlanca <= numeroTotal; posBlanca++){
        
        //Genero la fila si es válida
        if ((posBlanca+1) - y_dim <= 0){continue;}
            
        for(int posCelda = 0; posCelda <= numeroTotal; posCelda++){
            
            if (posBlanca == posCelda){
                cout << ficha;
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
                cout << ficha;
            }
            else {
                cout << "- ";
            }
        
        }
        
        printf("LABEL Rev%d", *numeroRegla);
        if (letra == 1){cout << " COST 0";}
    
        cout << endl;
        (*numeroRegla)++;
        
    }
    
}


void moverAbajo(int x_dim, int y_dim, int *numeroRegla,int letra){
    int numeroTotal = x_dim * y_dim-1;
    string ficha;
    if (letra == 1){ficha = "N ";}
    else{ficha = "B ";}
    for(int posBlanca = 0; posBlanca <= numeroTotal; posBlanca++){
        
        //Genero la fila si es válida
        if ((posBlanca+1) + y_dim > numeroTotal+1){continue;}
            
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
        if (letra == 1){cout << " COST 0";}
   
        cout << endl;
        (*numeroRegla)++;
    }
    
    
    
    
}

void imprimirGoal(int x_dim, int y_dim){
    
    int numeroTotal = x_dim * y_dim;
    
    cout << "GOAL ";
    
    cout << "B ";
    for(int celda = 1 ; celda < numeroTotal; celda++){
        printf("%d ", celda);
    }
}

void imprimirDominio(int x_dim, int y_dim){
    
    int numeroTotal = x_dim * y_dim -1;
    
    printf("DOMAIN celda %d\n", numeroTotal+1);
    cout << "       ";
    
    cout << "B ";
    for(int celda = 1 ; celda <= numeroTotal; celda++){
        printf("%d ", celda);
    }
    cout << "N ";
    cout << endl;
    printf("\n%d\n\n", numeroTotal+1);
    
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
    moverALaDerecha(x_dim, y_dim, &numeroRegla,0);
    moverALaIzquierda(x_dim, y_dim, &numeroRegla,0);
    moverArriba(x_dim, y_dim, &numeroRegla,0);
    moverAbajo(x_dim, y_dim, &numeroRegla,0);
    moverALaDerecha(x_dim, y_dim, &numeroRegla,1);
    moverALaIzquierda(x_dim, y_dim, &numeroRegla,1);
    moverArriba(x_dim, y_dim, &numeroRegla,1);
    moverAbajo(x_dim, y_dim, &numeroRegla,1);
    cout << endl;
    imprimirGoal(x_dim, y_dim);
    cout << endl;
    
    return (EXIT_SUCCESS);
}
