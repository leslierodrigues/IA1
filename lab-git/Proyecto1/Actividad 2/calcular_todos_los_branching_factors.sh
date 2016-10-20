#!/bin/bash

# Este script ejecuta branching_script.sh para cada problema
# y resume los resultados en una tabla. Se debe ejecutar en la
# carpeta Actividad 2

branching_factor=""
printf '%-60s %-20s\n' "Problema" "BranchingFactorEmpírico(Promedio)" > $1
cd "../Actividad 1/"
directorios=$(ls)
for dir in $directorios
do
    if [ -d "$dir" ]
    then
        echo $dir
        cd "$dir/"
        archivos=$(ls)
        for arch in $archivos
        do 
            if [ -f $arch ]
            then
                echo $arch
                branching_factor=$(. "../../Actividad 2/branching_script.sh" $arch | tail -n1)
                printf '%-60s %-20s\n' $arch $branching_factor >> "../../Actividad 2/$1"
            fi
        done
        cd ..
    fi
done
cd "../Actividad 2/"
