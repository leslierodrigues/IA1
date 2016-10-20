#!/bin/bash

while read in;
	do echo "$in" | timeout 2m ./npuzzle4x3.iter_deepening >> results_11puzzle3.txt;
done < 11puzzle.txt