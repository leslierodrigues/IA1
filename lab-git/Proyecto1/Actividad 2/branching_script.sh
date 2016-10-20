#!/bin/bash

# Este script permite calcular el branching factor por cada nivel

columna1=($(cut -f 1 $1)) # Nivel
columna2=($(cut -f 2 $1)) # Cantidad de Nodos
numelems=$(cut -f 2 $1 | wc -l)

declare -a branching # Branching factor de este nivel
branching[0]="BranchingFactor"
printf '%-20s %-20s %-20s\n' ${columna1[0]} ${columna2[0]} ${branching[0]}
max=$(($numelems-1))
i=1
promedio=0
while [ $i -lt $max ]
do
    nume=${columna2[$(($i+1))]}
    deno=${columna2[$i]}
    branching[$i]=$(echo "$nume/$deno" | bc -l)
    promedio=$( echo "${branching[$i]} + $promedio" | bc )
    printf '%-20s %-20s %-20s\n' ${columna1[$i]} ${columna2[$i]} ${branching[$i]}
    i=$(($i+1))
done
branching[$max]=${branching[$(($max-1))]}
printf '%-20s %-20s %-20s\n' ${columna1[$max]} ${columna2[$max]} ${branching[$max]}
max=$(($max-1))
promedio=$(echo "$promedio/$max" | bc -l)
echo "Branching Factor Empírico (Promedio): $promedio"
echo $promedio

