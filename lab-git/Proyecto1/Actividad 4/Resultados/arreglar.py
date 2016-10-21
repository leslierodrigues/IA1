i = 0
j = 0

with open("heuristicas.txt","r") as f:
	with open("resultados_15puzzle_korf_a_star_pdb.txt","w+") as new:
		with open("resultadosviejos1.txt","r") as g:
			a = f.readlines()
			b = g.readlines()
			i = 0
			j = 0
			while (i < len(a)):
				currA = a[i]
				currB = b[i]
				i+= 1
				new.write(currB.replace("__",currA.split()[0]))