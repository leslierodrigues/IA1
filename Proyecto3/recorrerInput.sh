#!/bin/bash

cat input.txt | while read linea
do
    echo "$linea"
    python3 "generarClausulas2.py" "$linea" | tail -n 1
done
