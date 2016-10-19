#!/bin/bash

# Con este script se generan las tablas de la actividad 1

niveles=( $(cat "$1" | tail -n +2 | cut -f1) )
n1=( $(cat "$1" | tail -n +2 | cut -f2) )
n2=( $(cat "$2" | tail -n +2 | cut -f2) )
numelems=$(cat "$1" | wc -l)
if [ $# -eq 2 ]
then
printf '%-20s %-20s %-20s\n' "Nivel" "N=0" "N=1" 
i=0
while [ $i -lt $numelems ]
do
    printf '%-20s %-20s %-20s\n' ${niveles[$i]} ${n1[$i]} ${n2[$i]}
    i=$(($i+1))
done
fi

if [ $# -eq 3 ]
then
n3=( $(cat "$3" | tail -n +2 | cut -f2) )
printf '%-20s %-20s %-20s %-20s\n' "Nivel" "N=0" "N=1" "N=2"
i=0
while [ $i -lt $numelems ]
do
    printf '%-20s %-20s %-20s %-20s\n' ${niveles[$i]} ${n1[$i]} ${n2[$i]} ${n3[$i]}
    i=$(($i+1))
done
fi
